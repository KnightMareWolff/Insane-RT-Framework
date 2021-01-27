#ifndef IAL_CANALVIRTUAL_H
#define IAL_CANALVIRTUAL_H

#include "INSAL_global.h"

class CIALVirtualChannel : public QIODevice
{
public:
    CIALVirtualChannel(                      );

    CIALVirtualChannel(QAudioFormat IAL_Formato     ,
                       qint64       IAL_Duracao     ,
                       int          IAL_FrequenciaHz);

    CIALVirtualChannel(QByteArray   pIAL_Data);
    CIALVirtualChannel(QString      pIAL_File);
   ~CIALVirtualChannel(                      );
private:
    QAudioBuffer   IAL_AudioBuffer;
    QAudioDecoder *IAL_Decoder;

    QByteArray GeraBuffer(QAudioFormat IAL_Formato     ,
                          qint64       IAL_Duracao     ,
                          int          IAL_FrequenciaHz);
};

#endif // IAL_CANALVIRTUAL_H
