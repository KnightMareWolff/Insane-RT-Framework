/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IAL_AUDIODEVICE_H
#define IAL_AUDIODEVICE_H

#include "INSAL_global.h"

class CIALAudioDevice
{
public:
    CIALAudioDevice(                                 );
    CIALAudioDevice(QAudioDeviceInfo *pI3D_DeviceInfo,int pI3D_DeviceMode);

private:
    QString                         I3D_DeviceName; //Nome do Device
    int                             I3D_DeviceMode; //Modo de IO (Input/OutPut)
    QAudioFormat                    I3D_AudioFormat;//Formato de Dados de Audio Atual
    QList<int>                      I3D_SupportedSampleRates;
    QList<int>                      I3D_SupportedChannelCounts;
    QStringList                     I3D_SupportedCodecs;
    QList<int>                      I3D_SupportedSampleSizes;
    QList<QAudioFormat::SampleType> I3D_SupportedSampleTypes;
    QList<QAudioFormat::Endian>     I3D_SupportedByteOrders;
};

#endif // IAL_AUDIODEVICE_H
