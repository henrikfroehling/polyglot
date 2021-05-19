#ifndef POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H
#define POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H

#include <QtCore/QAbstractItemModel>
#include <memory>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Core/Syntax/SyntaxVariant.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>
#include "SyntaxTreeItem.hpp"

class QTreeView;

namespace models
{

class SyntaxTreeModel : public QAbstractItemModel
{
public:
    explicit SyntaxTreeModel(QObject* parent = nullptr) noexcept;

    QModelIndex index(int row,
                      int column,
                      const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& child) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    bool hasChildren(const QModelIndex& parent) const override;

    void setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept;
    inline void setView(QTreeView* view) noexcept { _pView = view; }

private:
    SyntaxTreeItem* invisibleRootItem() const noexcept;
    SyntaxTreeItem* itemFromIndex(const QModelIndex& index) const noexcept;
    QModelIndex indexFromItem(SyntaxTreeItem* item) const noexcept;

private:
    SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> _ptrSyntaxTree;
    std::unique_ptr<SyntaxTreeItem> _ptrRootItem;
    QTreeView* _pView;
};

} // end namespace models

#endif // POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H
