/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
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
