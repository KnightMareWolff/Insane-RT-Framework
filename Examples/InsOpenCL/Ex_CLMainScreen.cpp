#include "Ex_CLMainScreen.h"

CCLMainScreen::CCLMainScreen(QWidget *parent)
    : QWidget(parent)
{
     pCLInterface = new INSCL();
}

CCLMainScreen::~CCLMainScreen()
{
}

