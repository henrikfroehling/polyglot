#ifndef POLYGLOT_SANDBOX_MAINWINDOW_H
#define POLYGLOT_SANDBOX_MAINWINDOW_H

#include <QtCore/QSettings>
#include <QtWidgets/QMainWindow>

class QDockWidget;
class QPlainTextEdit;
class QTreeView;

namespace models
{

class SyntaxTreeModel;

} // end namespace models

namespace ui
{

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;

private slots:
    void analyzeSourceCode() noexcept;
    void quitApplication() noexcept;

private:
    void closeEvent(QCloseEvent* event);

private:
    QSettings _settings;
    QPlainTextEdit* _pTxtEditor;
    QDockWidget* _pDockTreeView;
    QTreeView* _pTreeViewSyntaxVisualizer;
    models::SyntaxTreeModel* _pSyntaxTreeModel;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_MAINWINDOW_H
