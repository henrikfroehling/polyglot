#include "MainWindow.hpp"
#include "SyntaxTreeModel.hpp"
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QTimer>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTreeView>
#include <string>
#include <polyglot/Core/Types.hpp>
#include <polyglot/Delphi/Syntax/IDelphiSyntaxTree.hpp>
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
    connect(action, &QAction::triggered, this, &MainWindow::openFile);

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

void MainWindow::openFile() noexcept
{
    const QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"), QStringLiteral(""),
                                                          QStringLiteral("Delphi Files (*.pas)"));

    QFile file{filename};

    if (!file.open(QIODevice::ReadOnly))
        return;

    QTextStream in{&file};
    QString fileContent = in.readAll();
    _pTxtEditor->setPlainText(fileContent);
}

void MainWindow::analyzeSourceCode() noexcept
{
    using namespace polyglot::Delphi::Syntax;
    const QString editorContent = _pTxtEditor->toPlainText();
    const std::string sourceText = editorContent.toStdString();
    SharedPtr<IDelphiSyntaxTree> ptrSyntaxtree = IDelphiSyntaxTree::parseSourceText("", sourceText);
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
