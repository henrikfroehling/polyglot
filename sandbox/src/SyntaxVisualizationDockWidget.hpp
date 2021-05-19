#ifndef POLYGLOT_SANDBOX_SYNTAXVISUALIZATIONDOCKWIDGET_H
#define POLYGLOT_SANDBOX_SYNTAXVISUALIZATIONDOCKWIDGET_H

#include <QtWidgets/QDockWidget>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>

class QSplitter;

namespace ui
{

class SyntaxPropertiesWidget;
class SyntaxTreeWidget;

class SyntaxVisualizationDockWidget : public QDockWidget
{
public:
    explicit SyntaxVisualizationDockWidget(QWidget* parent = nullptr) noexcept;
    void setSyntaxTree(SharedPtr<polyglot::Delphi::Syntax::IDelphiSyntaxTree> syntaxTree) noexcept;

private:
    QSplitter* _pSplitter;
    SyntaxTreeWidget* _pSyntaxTreeView;
    SyntaxPropertiesWidget* _pSyntaxPropertiesView;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_SYNTAXVISUALIZATIONDOCKWIDGET_H
