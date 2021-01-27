#include "Ex_CLMainScreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CCLMainScreen w;
    w.show();
    return a.exec();
}
