#ifndef CSTDMAINSCREEN_H
#define CSTDMAINSCREEN_H

#include <QWidget>
#include "INSMT.h"

class CSTDMainScreen : public QWidget
{
    Q_OBJECT

public:
    CSTDMainScreen(QWidget *parent = nullptr);
    ~CSTDMainScreen();
};
#endif // CSTDMAINSCREEN_H
