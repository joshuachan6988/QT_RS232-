#include "touchscreen.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TouchScreen w;
    w.show();

    return a.exec();
}
