#include "MainWindow.hpp"
#include <QtCore/QString>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QTreeView>
#include <polyglot/Version.hpp>

namespace ui
{

MainWindow::MainWindow(QWidget* parent) noexcept
    : QMainWindow{parent},
      _pTxtEditor{new QPlainTextEdit{this}},
      _pDockTreeView{new QDockWidget{QStringLiteral("Syntax Visualizer"), this}},
      _pTreeViewSyntaxVisualizer{new QTreeView{this}}
{
    resize(1280, 720);
    setWindowTitle(QStringLiteral("polyglot Sandbox - %1").arg(QString::fromStdString(polyglot::Version::LIBRARY_NAME_WITH_VERSION)));

    QMenu* menu = menuBar()->addMenu(QStringLiteral("File"));
    menu->addAction(QStringLiteral("Open File..."));
    menu->addSeparator();
    QAction* action = menu->addAction(QStringLiteral("Quit"));
    connect(action, &QAction::triggered, qApp, &QApplication::quit);
    setCentralWidget(_pTxtEditor);
    statusBar();

    _pDockTreeView->setWidget(_pTreeViewSyntaxVisualizer);
    addDockWidget(Qt::LeftDockWidgetArea, _pDockTreeView);
}

} // end namespace ui
