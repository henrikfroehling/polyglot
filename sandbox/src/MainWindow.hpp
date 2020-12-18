#ifndef POLYGLOT_SANDBOX_MAINWINDOW_H
#define POLYGLOT_SANDBOX_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

class QDockWidget;
class QPlainTextEdit;
class QTreeView;

namespace ui
{

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;

private:
    QPlainTextEdit* _pTxtEditor;
    QDockWidget* _pDockTreeView;
    QTreeView* _pTreeViewSyntaxVisualizer;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_MAINWINDOW_H
