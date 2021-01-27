#include "Ex_GLMainScreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CGLMainScreen w;
    w.show();
    return a.exec();
}
