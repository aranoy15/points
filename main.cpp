#include <QApplication>
#include <QStyleFactory>
#include <QDebug>
#include <window/src/mainwindow.hpp>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle(QStyleFactory::create("Fusion"));

    MainWindow main;
    main.show();

    return a.exec();
}