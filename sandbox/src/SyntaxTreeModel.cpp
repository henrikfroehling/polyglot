#include "SyntaxTreeModel.hpp"
#include <QtCore/QString>
#include <QtWidgets/QTreeView>
#include <polyglot/Core/Syntax/ISyntaxList.hpp>
#include <polyglot/Core/Syntax/ISyntaxNode.hpp>
#include <polyglot/Core/Syntax/ISyntaxToken.hpp>
#include <polyglot/Core/Syntax/ISyntaxTrivia.hpp>
#include <polyglot/Core/Syntax/ISyntaxTriviaList.hpp>

namespace models
{

using namespace polyglot::Core::Syntax;

// ----------------------------------------
// SyntaxTreeItem
// ----------------------------------------

SyntaxTreeItem::SyntaxTreeItem() noexcept
    : _children{},
      _value{SyntaxVariant::empty()},
      _row{},
      _pParentItem{nullptr}
{}

SyntaxTreeItem::SyntaxTreeItem(SyntaxVariant value,
                               SyntaxTreeItem* parent) noexcept
    : _children{},
      _value{std::move(value)},
      _row{},
      _pParentItem{parent}
{}

SyntaxTreeItem* SyntaxTreeItem::child(int row) const noexcept
{
    if (row >= 0 && row < _children.size())
        return _children[row].get();

    return nullptr;
}

QVariant SyntaxTreeItem::data() const noexcept
{
    if (_value.isEmpty())
        return QVariant{};

    if (_value.isNode())
        return QString::fromLatin1(_value.node->toString());
    else if (_value.isToken())
        return QString::fromLatin1(_value.token->toString());
    else if (_value.isList())
        return QString::fromLatin1(_value.list->toString());
    else if (_value.isTrivia())
    {
        QString valuePrefix{};

        if (_value.trivia->isLeading())
            valuePrefix = QStringLiteral("Lead: ");
        else if (_value.trivia->isTrailing())
            valuePrefix = QStringLiteral("Trail: ");

        const QString value = valuePrefix + QString::fromLatin1(_value.trivia->toString());
        return value;
    }

    return QVariant{};
}

void SyntaxTreeItem::add(SyntaxVariant value) noexcept
{
    std::unique_ptr<SyntaxTreeItem> item = std::make_unique<SyntaxTreeItem>(value, this);

    if (value.isNode())
    {
        for (int i = 0; i < value.node->childCount(); i++)
            item->add(value.node->child(i));

        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
    else if (value.isToken())
    {
        if (value.token->hasLeadingTrivia())
        {
            for (int i = 0; i < value.token->leadingTrivia()->count(); i++)
                item->add(SyntaxVariant::asTrivia(value.token->leadingTrivia()->child(i)));
        }

        if (value.token->hasTrailingTrivia())
        {
            for (int i = 0; i < value.token->trailingTrivia()->count(); i++)
                item->add(SyntaxVariant::asTrivia(value.token->trailingTrivia()->child(i)));
        }

        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
    else if (value.isList())
    {
        for (int i = 0; i < value.list->childCount(); i++)
            item->add(value.list->child(i));

        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
    else if (value.isTrivia())
    {
        _children.push_back(std::move(item));
        _children.back().get()->setRow(_children.size() - 1);
    }
}

void SyntaxTreeItem::clear() noexcept
{
    _children.clear();
    _value = SyntaxVariant::empty();
    _row = 0;
    _pParentItem = nullptr;
}

// ----------------------------------------
// SyntaxTreeModel
// ----------------------------------------

SyntaxTreeModel::SyntaxTreeModel(QObject* parent) noexcept
    : QAbstractItemModel{parent},
      _ptrSyntaxTree{nullptr},
      _ptrRootItem{std::make_unique<SyntaxTreeItem>()},
      _pView{nullptr}
{}

QModelIndex SyntaxTreeModel::index(int row,
                                   int column,
                                   const QModelIndex& parent) const
{
    Q_UNUSED(column);

    if (SyntaxTreeItem* pParentItem = itemFromIndex(parent))
    {
        if (SyntaxTreeItem* pChildItem = pParentItem->child(row))
            return createIndex(row, 0, pChildItem);
    }

    return QModelIndex{};
}

QModelIndex SyntaxTreeModel::parent(const QModelIndex& child) const
{
    if (!child.isValid())
        return QModelIndex{};

    if (SyntaxTreeItem* pChildItem = itemFromIndex(child))
    {
        if (SyntaxTreeItem* pParentItem = pChildItem->parentItem())
        {
            if (pParentItem == invisibleRootItem())
                return QModelIndex{};

            const int row = pParentItem->row();
            return createIndex(row, 0, pParentItem);
        }
    }

    return QModelIndex{};
}

int SyntaxTreeModel::rowCount(const QModelIndex& parent) const
{
    SyntaxTreeItem* pParentItem = itemFromIndex(parent);
    return pParentItem != nullptr ? pParentItem->childCount() : 0;
}

int SyntaxTreeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 1;
}

QVariant SyntaxTreeModel::data(const QModelIndex& index,
                               int role) const
{
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant{};

    SyntaxTreeItem* pItem = itemFromIndex(index);
    return pItem->data();
}

QVariant SyntaxTreeModel::headerData(int section,
                                     Qt::Orientation orientation,
                                     int role) const
{
    return QStringLiteral("");
}

bool SyntaxTreeModel::hasChildren(const QModelIndex& parent) const
{
    SyntaxTreeItem* pParentItem = itemFromIndex(parent);
    return pParentItem != nullptr && pParentItem->childCount() > 0;
}

SyntaxTreeItem* SyntaxTreeModel::invisibleRootItem() const noexcept
{
    return _ptrRootItem.get();
}

void SyntaxTreeModel::setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept
{
    _ptrSyntaxTree = std::move(syntaxTree);
    ISyntaxNode* pRootNode = _ptrSyntaxTree->root();

    const int rows = pRootNode->childCount();
    const QModelIndex parentIndex = indexFromItem(_ptrRootItem.get());

    beginInsertRows(parentIndex, 0, rows);
    _ptrRootItem->clear();
    _ptrRootItem->add(SyntaxVariant::asNode(pRootNode));
    endInsertRows();

    if (_pView != nullptr)
        _pView->expandAll();
}

SyntaxTreeItem* SyntaxTreeModel::itemFromIndex(const QModelIndex& index) const noexcept
{
    if (index.isValid())
    {
        if (SyntaxTreeItem* pItem = static_cast<SyntaxTreeItem*>(index.internalPointer()))
            return pItem;
    }

    return invisibleRootItem();
}

QModelIndex SyntaxTreeModel::indexFromItem(SyntaxTreeItem* item) const noexcept
{
    if (item == nullptr || item == invisibleRootItem())
        return QModelIndex{};

    const int row = item->row();
    return createIndex(row, 0, item);
}

} // end namespace models
