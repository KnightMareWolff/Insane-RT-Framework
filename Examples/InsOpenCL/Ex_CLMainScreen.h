#ifndef CCLMAINSCREEN_H
#define CCLMAINSCREEN_H

#include <QWidget>
#include "INSCL.h"

class CCLMainScreen : public QWidget
{
    Q_OBJECT

public:
    CCLMainScreen(QWidget *parent = nullptr);
    ~CCLMainScreen();
private:
    INSCL *pCLInterface;
};
#endif // CCLMAINSCREEN_H
