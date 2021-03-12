/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
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
