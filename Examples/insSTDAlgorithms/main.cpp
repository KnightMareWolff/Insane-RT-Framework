#include "Ex_STDMainScreen.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CSTDMainScreen w;
    w.show();
    return a.exec();
}
