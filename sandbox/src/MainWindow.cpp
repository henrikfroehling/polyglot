#include "MainWindow.hpp"
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtCore/QTimer>
#include <QtGui/QScreen>

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
#include <QtGui/QAction>
#else
#include <QtWidgets/QAction>
#endif

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
#include "SyntaxVisualizationDockWidget.hpp"

namespace ui
{

MainWindow::MainWindow(QWidget* parent) noexcept
    : QMainWindow{parent},
      _settings{},
      _pTxtEditor{new QPlainTextEdit{this}},
      _pSyntaxVisualizerDockWidget{new SyntaxVisualizationDockWidget{this}}
{
    QScreen* pScreen = QApplication::primaryScreen();
    pScreen->size().width();

    int nScreenWidth = pScreen->size().width();
    int nScreenHeight = pScreen->size().height();
    int nWidth = nScreenWidth * 0.8f;
    int nHeight = nScreenHeight * 0.8f;
    int nPosX = (nScreenWidth - nWidth) / 2;
    int nPosY = (nScreenHeight - nHeight) / 2;

    resize(nWidth, nHeight);
    move(nPosX, nPosY);

    setWindowTitle(QStringLiteral("polyglot Sandbox - %1").arg(QString::fromStdString(polyglot::Version::LIBRARY_NAME_WITH_VERSION)));

    QMenu* menu = menuBar()->addMenu(QStringLiteral("File"));

    QAction* action = menu->addAction(QStringLiteral("Open File..."));
    action->setShortcut(QKeySequence{QStringLiteral("Ctrl+O")});
    connect(action, &QAction::triggered, this, &MainWindow::openFile);

    menu->addSeparator();

    action = menu->addAction(QStringLiteral("Quit"));
    action->setShortcut(QKeySequence{QStringLiteral("Ctrl+Q")});
    connect(action, &QAction::triggered, this, &MainWindow::quitApplication);

    menu = menuBar()->addMenu(QStringLiteral("polyglot"));

    action = menu->addAction(QStringLiteral("Analyze"));
    action->setShortcut(QKeySequence{QStringLiteral("Ctrl+Shift+A")});
    connect(action, &QAction::triggered, this, &MainWindow::analyzeSourceCode);

    setCentralWidget(_pTxtEditor);
    statusBar();

    addDockWidget(Qt::LeftDockWidgetArea, _pSyntaxVisualizerDockWidget);

    _pTxtEditor->setPlainText(_settings.value(QStringLiteral("editor-content")).toString());
}

void MainWindow::openFile() noexcept
{
    const QString filename = QFileDialog::getOpenFileName(this, QStringLiteral("Open File"), QLatin1String{},
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
    const pg_string sourceText = editorContent.toStdWString();
    SharedPtr<IDelphiSyntaxTree> ptrSyntaxtree = IDelphiSyntaxTree::parseSourceText(L"", sourceText);
    _pSyntaxVisualizerDockWidget->setSyntaxTree(ptrSyntaxtree);
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
