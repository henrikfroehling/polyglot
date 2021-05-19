#ifndef POLYGLOT_SANDBOX_MAINWINDOW_H
#define POLYGLOT_SANDBOX_MAINWINDOW_H

#include <QtCore/QSettings>
#include <QtWidgets/QMainWindow>

class QPlainTextEdit;

namespace models
{

class SyntaxTreeModel;

} // end namespace models

namespace ui
{

class SyntaxVisualizationDockWidget;

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;

private slots:
    void openFile() noexcept;
    void analyzeSourceCode() noexcept;
    void quitApplication() noexcept;

private:
    void closeEvent(QCloseEvent* event);

private:
    QSettings _settings;
    QPlainTextEdit* _pTxtEditor;
    SyntaxVisualizationDockWidget* _pSyntaxVisualizerDockWidget;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_MAINWINDOW_H
