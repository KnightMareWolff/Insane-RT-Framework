/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IAL_SOUND_H
#define IAL_SOUND_H

#include "INSAL_global.h"

class CIALSound
{
public:
     CIALSound(const char *nome);
    ~CIALSound(                );

    bool SetaParametros3D(CIMTVector pPos,CIMTVector pVel);
    void Play(bool pUpdate);

private:
    CIMTVector     I3DPosSom;
    CIMTVector     I3DVelSom;
    bool           I3DPausa ;
};

#endif // IAL_SOUND_H
