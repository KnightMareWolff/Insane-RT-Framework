#include "Ex_ALMainScreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CALMainScreen w;
    w.show();
    return a.exec();
}
