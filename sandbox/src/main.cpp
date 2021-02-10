#include <QtCore/QCoreApplication>
#include <QtCore/QString>
#include <QtWidgets/QApplication>
#include "MainWindow.hpp"

int main(int argc,
         char** argv)
{
    QApplication app{argc, argv};

    QCoreApplication::setOrganizationName(QStringLiteral("polyglot-sandbox"));
    QCoreApplication::setOrganizationDomain(QStringLiteral("polyglot-sandbox"));
    QCoreApplication::setApplicationName(QStringLiteral("polyglot-sandbox"));

    ui::MainWindow window{};
    window.show();

    return app.exec();
}
