#include <QApplication>
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Database::initialize();

    MainWindow w;
    w.show();

    return app.exec();
}