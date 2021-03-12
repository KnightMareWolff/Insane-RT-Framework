/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IAL_Sound.h"

CIALSound::CIALSound(const char *nome)
{
}

CIALSound::~CIALSound()
{
}

bool CIALSound::SetaParametros3D(CIMTVector pPos, CIMTVector pVel)
{
    I3DPosSom = pPos;
    I3DVelSom = pVel;
    return true;
}

void CIALSound::Play(bool pUpdate)
{
}
