#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setApplicationName("Camera Viewer");
    app.setApplicationVersion("1.0");

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
