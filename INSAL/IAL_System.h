/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IAL_SYSTEM_H
#define IAL_SYSTEM_H

#include "INSAL_global.h"
#include "IAL_AudioDevice.h"

class CIALSystem
{
public:
    CIALSystem();

private:
    QAudioDeviceInfo          IAL_InfoSistemaAudio;

    QList<QAudioDeviceInfo>   IAL_InputDevicesInfo;
    QList<QAudioDeviceInfo>   IAL_OutPutDevicesInfo;

    vector<CIALAudioDevice *> IAL_InputAudioDevices;
    vector<CIALAudioDevice *> IAL_OutPutAudioDevices;
};

#endif // IAL_SYSTEM_H
