#ifndef INSAL_H
#define INSAL_H

#include "INSAL_global.h"
#include "IAL_Sound.h"
#include "IAL_System.h"
#include "IAL_AudioDevice.h"
#include "IAL_VirtualChannel.h"

class INSAL_EXPORT INSAL
{
public:
     INSAL();
    ~INSAL();

    static bool SetaFatores3D (float pFatorDoppler  ,float pFatorDistancia,float pFatorRolloff);
    static bool SetaDistancias(float pDistMin       ,float pDistMax                           );
    static bool Atualiza      (                                                               );

private:
    static CIALSystem *pINSMDStaticInterface;
};

#endif // INSAL_H
