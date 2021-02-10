#include "MainWindow.hpp"
#include "SyntaxTreeModel.hpp"
#include <QtCore/QString>
#include <QtCore/QTimer>
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
#include <polyglot/CodeAnalysis/Syntax/ISyntaxTree.hpp>
#include <polyglot/Version.hpp>

namespace ui
{

MainWindow::MainWindow(QWidget* parent) noexcept
    : QMainWindow{parent},
      _settings{},
      _pTxtEditor{new QPlainTextEdit{this}},
      _pDockTreeView{new QDockWidget{QStringLiteral("Syntax Visualizer"), this}},
      _pTreeViewSyntaxVisualizer{new QTreeView{this}},
      _pSyntaxTreeModel{new models::SyntaxTreeModel{this}}
{
    resize(1280, 720);
    setWindowTitle(QStringLiteral("polyglot Sandbox - %1").arg(QString::fromStdString(polyglot::Version::LIBRARY_NAME_WITH_VERSION)));

    QMenu* menu = menuBar()->addMenu(QStringLiteral("File"));
    QAction* action = menu->addAction(QStringLiteral("Open File..."));
    action->setShortcut(QKeySequence{Qt::CTRL | Qt::Key_O});
    menu->addSeparator();
    action = menu->addAction(QStringLiteral("Quit"));
    action->setShortcut(QKeySequence{Qt::CTRL | Qt::Key_Q});
    connect(action, &QAction::triggered, this, &MainWindow::quitApplication);

    menu = menuBar()->addMenu(QStringLiteral("polyglot"));
    action = menu->addAction(QStringLiteral("Analyze"));
    action->setShortcut(QKeySequence{Qt::CTRL | Qt::SHIFT | Qt::Key_A});
    connect(action, &QAction::triggered, this, &MainWindow::analyzeSourceCode);

    setCentralWidget(_pTxtEditor);
    statusBar();

    _pTreeViewSyntaxVisualizer->setModel(_pSyntaxTreeModel);
    _pDockTreeView->setWidget(_pTreeViewSyntaxVisualizer);
    addDockWidget(Qt::LeftDockWidgetArea, _pDockTreeView);

    _pTxtEditor->setPlainText(_settings.value(QStringLiteral("editor-content")).toString());
}

void MainWindow::analyzeSourceCode() noexcept
{
    const QString editorContent = _pTxtEditor->toPlainText();
    const std::string sourceText = editorContent.toStdString();
    SharedPtr<polyglot::CodeAnalysis::ISyntaxTree> ptrSyntaxtree = polyglot::CodeAnalysis::Delphi::parseSourceText("", sourceText);
    _pSyntaxTreeModel->setSyntaxTree(ptrSyntaxtree);
}

void MainWindow::quitApplication() noexcept
{
    QTimer::singleShot(0, this, SLOT(close()));
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    _settings.setValue(QStringLiteral("editor-content"), _pTxtEditor->toPlainText());
    QMainWindow::closeEvent(event);
}

} // end namespace ui
