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
