#ifndef CALMAINSCREEN_H
#define CALMAINSCREEN_H

#include <QWidget>
#include "INSAL.h"

class CALMainScreen : public QWidget
{
    Q_OBJECT

public:
     CALMainScreen(QWidget *parent = nullptr);
    ~CALMainScreen();
private:
     INSAL *pALInterface;
};
#endif // CALMAINSCREEN_H
