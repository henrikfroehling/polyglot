#include <QtWidgets/QApplication>
#include "MainWindow.hpp"

int main(int argc,
         char** argv)
{
    QApplication app{argc, argv};

    ui::MainWindow window{};
    window.show();

    return app.exec();
}
