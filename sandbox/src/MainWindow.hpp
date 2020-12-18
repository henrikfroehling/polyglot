#ifndef POLYGLOT_SANDBOX_MAINWINDOW_H
#define POLYGLOT_SANDBOX_MAINWINDOW_H

#include <QtWidgets/QMainWindow>

namespace ui
{

class MainWindow : public QMainWindow
{
public:
    explicit MainWindow(QWidget* parent = nullptr) noexcept;
};

} // end namespace ui

#endif // POLYGLOT_SANDBOX_MAINWINDOW_H
