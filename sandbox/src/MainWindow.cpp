#include "MainWindow.hpp"
#include <QtCore/QString>
#include <polyglot/Version.hpp>

namespace ui
{

MainWindow::MainWindow(QWidget* parent) noexcept
    : QMainWindow{parent}
{
    resize(1280, 720);
    setWindowTitle(QStringLiteral("polyglot Sandbox - %1").arg(QString::fromStdString(polyglot::Version::LIBRARY_NAME_WITH_VERSION)));
}

} // end namespace ui
