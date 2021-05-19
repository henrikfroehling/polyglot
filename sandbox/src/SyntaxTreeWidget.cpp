#include "SyntaxTreeWidget.hpp"
#include <QtCore/QItemSelection>
#include <QtCore/QItemSelectionModel>
#include <QtCore/QModelIndex>
#include <QtCore/QString>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include "SyntaxTreeModel.hpp"

namespace ui
{

SyntaxTreeWidget::SyntaxTreeWidget(QWidget* parent) noexcept
    : QWidget{parent},
      _pVLayout{new QVBoxLayout{this}},
      _pLblHeader{new QLabel{QStringLiteral("Syntax Tree"), this}},
      _pTreeViewSyntaxVisualizer{new QTreeView{this}},
      _pSyntaxTreeModel{new models::SyntaxTreeModel{this}}
{
    _pSyntaxTreeModel->setView(_pTreeViewSyntaxVisualizer);
    _pTreeViewSyntaxVisualizer->setModel(_pSyntaxTreeModel);
    _pTreeViewSyntaxVisualizer->setUniformRowHeights(true);

    _pVLayout->addWidget(_pLblHeader);
    _pVLayout->addWidget(_pTreeViewSyntaxVisualizer);

    setLayout(_pVLayout);

    connect(_pTreeViewSyntaxVisualizer->selectionModel(), &QItemSelectionModel::selectionChanged,
            this, &SyntaxTreeWidget::onSelectionChanged);
}

void SyntaxTreeWidget::setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept
{
    _pSyntaxTreeModel->setSyntaxTree(std::move(syntaxTree));
}

void SyntaxTreeWidget::onSelectionChanged(const QItemSelection& selected,
                                          const QItemSelection& deselected) noexcept
{
    if (selected.indexes().count() > 0)
        emit itemSelected(selected.indexes().first());
}

} // end namespace ui
