#include "window/menuwindow.h"
#include "window/windowholder.h"

#include <QApplication>
#include <QtLogging>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    WindowHolder::instance(new MenuWindow())->show();
    qDebug("menu showing");

    return a.exec();
}
