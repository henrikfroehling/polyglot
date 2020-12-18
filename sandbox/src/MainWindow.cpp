#include "MainWindow.hpp"
#include "SyntaxTreeModel.hpp"
#include <QtCore/QString>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTreeView>
#include <string>
#include <polyglot/Core/Types.hpp>
#include <polyglot/CodeAnalysis/CodeAnalysis.hpp>
#include <polyglot/CodeAnalysis/Core/Syntax/SyntaxTree.hpp>
#include <polyglot/Version.hpp>

namespace ui
{

MainWindow::MainWindow(QWidget* parent) noexcept
    : QMainWindow{parent},
      _pTxtEditor{new QPlainTextEdit{this}},
      _pDockTreeView{new QDockWidget{QStringLiteral("Syntax Visualizer"), this}},
      _pTreeViewSyntaxVisualizer{new QTreeView{this}},
      _pSyntaxTreeModel{new models::SyntaxTreeModel{this}}
{
    resize(1280, 720);
    setWindowTitle(QStringLiteral("polyglot Sandbox - %1").arg(QString::fromStdString(polyglot::Version::LIBRARY_NAME_WITH_VERSION)));

    QMenu* menu = menuBar()->addMenu(QStringLiteral("File"));
    menu->addAction(QStringLiteral("Open File..."));
    menu->addSeparator();
    QAction* action = menu->addAction(QStringLiteral("Quit"));
    connect(action, &QAction::triggered, qApp, &QApplication::quit);

    menu = menuBar()->addMenu(QStringLiteral("polyglot"));
    action = menu->addAction(QStringLiteral("Analyze"));
    connect(action, &QAction::triggered, this, &MainWindow::analyzeSourceCode);

    setCentralWidget(_pTxtEditor);
    statusBar();

    _pTreeViewSyntaxVisualizer->setModel(_pSyntaxTreeModel);
    _pDockTreeView->setWidget(_pTreeViewSyntaxVisualizer);
    addDockWidget(Qt::LeftDockWidgetArea, _pDockTreeView);
}

void MainWindow::analyzeSourceCode() noexcept
{
    const QString editorContent = _pTxtEditor->toPlainText();
    const std::string sourceText = editorContent.toStdString();
    SharedPtr<polyglot::CodeAnalysis::SyntaxTree> ptrSyntaxtree = polyglot::CodeAnalysis::Delphi::parseSourceText("", sourceText);
    _pSyntaxTreeModel->setSyntaxTree(ptrSyntaxtree);
}

} // end namespace ui
