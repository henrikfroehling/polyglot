#include "SyntaxVisualizationDockWidget.hpp"
#include <QtWidgets/QSplitter>
#include "SyntaxPropertiesWidget.hpp"
#include "SyntaxTreeWidget.hpp"

namespace ui
{

SyntaxVisualizationDockWidget::SyntaxVisualizationDockWidget(QWidget* parent) noexcept
    : QDockWidget{QStringLiteral("Syntax Visualizer"), parent},
      _pSplitter{new QSplitter{Qt::Vertical, this}},
      _pSyntaxTreeView{new SyntaxTreeWidget{this}},
      _pSyntaxPropertiesView{new SyntaxPropertiesWidget{this}}
{
    _pSplitter->addWidget(_pSyntaxTreeView);
    _pSplitter->addWidget(_pSyntaxPropertiesView);
    setWidget(_pSplitter);
    setMinimumWidth(400);

    connect(_pSyntaxTreeView, &SyntaxTreeWidget::itemSelected,
            _pSyntaxPropertiesView, &SyntaxPropertiesWidget::onSyntaxSelected);
}

void SyntaxVisualizationDockWidget::setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept
{
    _pSyntaxTreeView->setSyntaxTree(std::move(syntaxTree));
}

} // end namespace ui
