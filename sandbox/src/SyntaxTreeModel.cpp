#include "SyntaxTreeModel.hpp"

namespace models
{

SyntaxTreeModel::SyntaxTreeModel(QObject* parent) noexcept
    : QAbstractItemModel{parent},
      _ptrSyntaxTree{nullptr}
{}

QModelIndex SyntaxTreeModel::index(int row,
                                   int column,
                                   const QModelIndex& parent) const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex{};

    return QModelIndex{};
}

QModelIndex SyntaxTreeModel::parent(const QModelIndex& index) const
{
    if (!index.isValid())
        return QModelIndex{};

    return QModelIndex{};
}

int SyntaxTreeModel::columnCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return 1;
}

int SyntaxTreeModel::rowCount(const QModelIndex& parent) const
{
    return 0;
}

Qt::ItemFlags SyntaxTreeModel::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant SyntaxTreeModel::data(const QModelIndex& index,
                               int role) const
{
    if (!index.isValid())
        return QVariant{};

    if (role != Qt::DisplayRole)
        return QVariant{};

    return QVariant{};
}

bool SyntaxTreeModel::hasChildren(const QModelIndex& parent) const
{
    return false;
}

QVariant SyntaxTreeModel::headerData(int section,
                                     Qt::Orientation orientation,
                                     int role) const
{
    return QVariant{};
}

void SyntaxTreeModel::setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept
{
    _ptrSyntaxTree = std::move(syntaxTree);
}

} // end namespace models
