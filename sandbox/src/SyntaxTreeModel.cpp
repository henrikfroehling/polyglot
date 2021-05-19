#include "SyntaxTreeModel.hpp"
#include <QtWidgets/QTreeView>
#include <polyglot/Core/Syntax/ISyntaxNode.hpp>

namespace models
{

using namespace polyglot::Core::Syntax;

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

    if (_pView != nullptr && _ptrRootItem->childCount() > 0)
    {
        QModelIndex index = indexFromItem(_ptrRootItem->child(0));
        _pView->expand(index);
        _pView->setCurrentIndex(index);
    }
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
