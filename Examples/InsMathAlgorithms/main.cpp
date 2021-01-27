#include "Ex_MTMainScreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CMTMainScreen w;
    w.show();
    return a.exec();
}
