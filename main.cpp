#include "mainwindow.h"
#include "gamewindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.applicationDirPath();

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
