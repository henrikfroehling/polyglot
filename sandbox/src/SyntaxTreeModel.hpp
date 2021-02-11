#ifndef POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H
#define POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H

#include <QtCore/QAbstractItemModel>
#include <polyglot/Core/Types.hpp>
#include <polyglot/CodeAnalysis/ISyntaxTree.hpp>

namespace models
{

class SyntaxTreeModel : public QAbstractItemModel
{
public:
    explicit SyntaxTreeModel(QObject* parent = nullptr) noexcept;

    QModelIndex index(int row,
                      int column,
                      const QModelIndex& parent = QModelIndex()) const override;

    QModelIndex parent(const QModelIndex& index) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    QVariant data(const QModelIndex& index,
                  int role = Qt::DisplayRole) const override;

    bool hasChildren(const QModelIndex& parent = QModelIndex()) const override;

    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void setSyntaxTree(SharedPtr<polyglot::CodeAnalysis::ISyntaxTree> syntaxTree) noexcept;

private:
    SharedPtr<polyglot::CodeAnalysis::ISyntaxTree> _ptrSyntaxTree;
};

} // end namespace models

#endif // POLYGLOT_SANDBOX_SYNTAXTREEMODEL_H
