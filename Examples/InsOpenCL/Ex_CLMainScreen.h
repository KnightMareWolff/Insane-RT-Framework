/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CCLMAINSCREEN_H
#define CCLMAINSCREEN_H

#include <QWidget>
#include "INSCL.h"
#include "INSGL.h"
#include "INSCG.h"

class CCLMainScreen : public QWidget
{
    Q_OBJECT

public:
    CCLMainScreen(QWidget *parent = nullptr);
    ~CCLMainScreen();
private:
    INSCL *pCLInterface;
    INSGL *pGLInterface;
    INSCG *pCGInterface;
};
#endif // CCLMAINSCREEN_H
