#ifndef POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H
#define POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H

#include <memory>
#include <vector>
#include <QtCore/QAbstractItemModel>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Core/Syntax/SyntaxVariant.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>

namespace models
{

// ----------------------------------------
// SyntaxTreeItem
// ----------------------------------------

class SyntaxTreeItem
{
public:
    SyntaxTreeItem() noexcept;

    explicit SyntaxTreeItem(polyglot::Core::Syntax::SyntaxVariant value,
                            SyntaxTreeItem* parent = nullptr) noexcept;

    ~SyntaxTreeItem() noexcept {}

    inline SyntaxTreeItem* parentItem() const noexcept { return _pParentItem; }
    inline int childCount() const noexcept { return _children.size(); }
    inline int row() const noexcept { return _row; }
    inline const polyglot::Core::Syntax::SyntaxVariant& value() const noexcept { return _value; }
    SyntaxTreeItem* child(int row) const noexcept;
    QVariant data() const noexcept;
    void add(polyglot::Core::Syntax::SyntaxVariant value) noexcept;
    void clear() noexcept;

private:
    inline void setRow(int row) noexcept { _row = row; }

private:
    std::vector<std::unique_ptr<SyntaxTreeItem>> _children;
    polyglot::Core::Syntax::SyntaxVariant _value;
    int _row;
    SyntaxTreeItem* _pParentItem;
};

// ----------------------------------------
// SyntaxTreeModel
// ----------------------------------------

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

private:
    SyntaxTreeItem* invisibleRootItem() const noexcept;
    SyntaxTreeItem* itemFromIndex(const QModelIndex& index) const noexcept;
    QModelIndex indexFromItem(SyntaxTreeItem* item) const noexcept;

private:
    SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> _ptrSyntaxTree;
    std::unique_ptr<SyntaxTreeItem> _ptrRootItem;
};

} // end namespace models

#endif // POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H
