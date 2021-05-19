#ifndef POLYGLOT_SANDBOX_SYNTAXTREEWIDGET_H
#define POLYGLOT_SANDBOX_SYNTAXTREEWIDGET_H

#include <QtWidgets/QWidget>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>

class QItemSelection;
class QLabel;
class QModelIndex;
class QTreeView;
class QVBoxLayout;

namespace models
{

class SyntaxTreeModel;

} // end namespace models

namespace ui
{

class SyntaxTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SyntaxTreeWidget(QWidget* parent = nullptr) noexcept;
    void setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept;

signals:
    void itemSelected(const QModelIndex& selectedIndex);

private slots:
    void onSelectionChanged(const QItemSelection& selected,
                            const QItemSelection& deselected) noexcept;

private:
    QVBoxLayout* _pVLayout;
    QLabel* _pLblHeader;
    QTreeView* _pTreeViewSyntaxVisualizer;
    models::SyntaxTreeModel* _pSyntaxTreeModel;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_SYNTAXTREEWIDGET_H
