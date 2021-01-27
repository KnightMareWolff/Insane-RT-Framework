#include "IAL_AudioDevice.h"

CIALAudioDevice::CIALAudioDevice()
{

}

CIALAudioDevice::CIALAudioDevice(QAudioDeviceInfo *pI3D_DeviceInfo, int pI3D_DeviceMode)
{
   I3D_DeviceName = pI3D_DeviceInfo->deviceName();
   I3D_DeviceMode = pI3D_DeviceMode;

   I3D_SupportedSampleRates   = pI3D_DeviceInfo->supportedSampleRates();
   I3D_SupportedChannelCounts = pI3D_DeviceInfo->supportedChannelCounts();
   I3D_SupportedCodecs        = pI3D_DeviceInfo->supportedCodecs();
   I3D_SupportedSampleSizes   = pI3D_DeviceInfo->supportedSampleSizes();
   I3D_SupportedSampleTypes   = pI3D_DeviceInfo->supportedSampleTypes();
   I3D_SupportedByteOrders    = pI3D_DeviceInfo->supportedByteOrders();

   qWarning() << "===========================================";
   qWarning() << "Nome Device       :" << I3D_DeviceName ;
   qWarning() << "Device Mode       :" << I3D_DeviceMode ;
   qWarning() << "Codecs Suportados :";
   for(int i=0; i<I3D_SupportedCodecs.size();i++ )
   {
       qWarning() << "Codec :" << I3D_SupportedCodecs[i];

       for(int j=0; j<I3D_SupportedSampleRates.size();j++ )
       {
           qWarning() << "Sample Rates Suportados :" << I3D_SupportedSampleRates[j];
       }

       for(int j=0; j<I3D_SupportedChannelCounts.size();j++ )
       {
           qWarning() << "Qtd Canais Suportados :" << I3D_SupportedChannelCounts[j];
       }

       for(int j=0; j<I3D_SupportedSampleSizes.size();j++ )
       {
           qWarning() << "Tamanho Samplers Suportados :" << I3D_SupportedSampleSizes[j];
       }

       for(int j=0; j<I3D_SupportedSampleTypes.size();j++ )
       {
           qWarning() << "Tipos de Samplers Suportados :" << I3D_SupportedSampleTypes[j];
       }

       for(int j=0; j<I3D_SupportedByteOrders.size();j++ )
       {
           qWarning() << "Ordem de Bytes Suportados :" << I3D_SupportedByteOrders[j];
       }
   }

   //Realiza o Setup do formato de dados Atual como o primeiro das listas de dados suportados
   //pelo dispositivo

   if(I3D_SupportedChannelCounts.size()>0)I3D_AudioFormat.setChannelCount(I3D_SupportedChannelCounts[0]);
   if(I3D_SupportedCodecs       .size()>0)I3D_AudioFormat.setCodec       (I3D_SupportedCodecs       [0]);
   if(I3D_SupportedSampleRates  .size()>0)I3D_AudioFormat.setSampleRate  (I3D_SupportedSampleRates  [0]);
   if(I3D_SupportedSampleSizes  .size()>0)I3D_AudioFormat.setSampleSize  (I3D_SupportedSampleSizes  [0]);
   if(I3D_SupportedSampleTypes  .size()>0)I3D_AudioFormat.setSampleType  (I3D_SupportedSampleTypes  [0]);
   if(I3D_SupportedByteOrders   .size()>0)I3D_AudioFormat.setByteOrder   (I3D_SupportedByteOrders   [0]);

}
