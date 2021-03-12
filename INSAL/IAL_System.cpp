/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IAL_System.h"

CIALSystem::CIALSystem()
{

    IAL_InputDevicesInfo  = QAudioDeviceInfo::availableDevices(QAudio::AudioInput);
    IAL_OutPutDevicesInfo = QAudioDeviceInfo::availableDevices(QAudio::AudioOutput);

    qWarning() << "===========================================";
    qWarning() << "Configuracao Plataforma Multimidia         ";
    qWarning() << "===========================================";
    qWarning() << "Criando os Devices de Entrada:             ";
    for(int i=0; i<IAL_InputDevicesInfo.size();i++ )
    {
        IAL_InputAudioDevices.push_back(new CIALAudioDevice(&IAL_InputDevicesInfo[i],
                                                             IAL_AUDIO_MODE_INPUT    ));
    }

    qWarning() << "Criando os Devices de Saida  :             ";
    for(int i=0; i<IAL_OutPutDevicesInfo.size();i++ )
    {
        IAL_OutPutAudioDevices.push_back(new CIALAudioDevice(&IAL_OutPutDevicesInfo[i],
                                                              IAL_AUDIO_MODE_OUTPUT     ));
    }

}
