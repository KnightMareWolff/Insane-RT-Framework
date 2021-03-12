/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CIGLSPLASHSCREEN_H
#define CIGLSPLASHSCREEN_H

#include "INSGL_global.h"

class CIGLSplashScreen
{
public:
    CIGLSplashScreen();

public:
    void paint(QPainter *painter, QPaintEvent *event, int elapsed);

private:
    QBrush background;
    QBrush circleBrush;
    QFont  textFont;
    QPen   circlePen;
    QPen   textPen;
};

#endif // CIGLSPLASHSCREEN_H
