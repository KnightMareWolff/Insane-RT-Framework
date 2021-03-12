/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "Ex_CLMainScreen.h"

CCLMainScreen::CCLMainScreen(QWidget *parent)
    : QWidget(parent)
{
     pCLInterface = new INSCL();
}

CCLMainScreen::~CCLMainScreen()
{
}

