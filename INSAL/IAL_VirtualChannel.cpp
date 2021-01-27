#include "IAL_VirtualChannel.h"

CIALVirtualChannel::~CIALVirtualChannel()
{
    close();
}

CIALVirtualChannel::CIALVirtualChannel()
{
   open(QIODevice::ReadWrite);
   IAL_Decoder = new QAudioDecoder(this);
}

CIALVirtualChannel::CIALVirtualChannel(QAudioFormat IAL_Formato     ,
                                   qint64       IAL_Duracao     ,
                                   int          IAL_FrequenciaHz)
{
   open(QIODevice::ReadWrite);

   write(GeraBuffer(IAL_Formato,IAL_Duracao,IAL_FrequenciaHz));

   IAL_Decoder = new QAudioDecoder(this);

   IAL_Decoder->start();
   while(IAL_Decoder->bufferAvailable())
   {
      IAL_AudioBuffer = IAL_Decoder->read();
      qWarning() << "Buffer size: " << IAL_AudioBuffer.byteCount();
   }
}

CIALVirtualChannel::CIALVirtualChannel(QByteArray pIAL_Data)
{
   open(QIODevice::ReadWrite);

   write(pIAL_Data);

   IAL_Decoder = new QAudioDecoder(this);

   IAL_Decoder->start();
   while(IAL_Decoder->bufferAvailable())
   {
      IAL_AudioBuffer = IAL_Decoder->read();
      qWarning() << "Buffer size: " << IAL_AudioBuffer.byteCount();
   }
}

CIALVirtualChannel::CIALVirtualChannel(QString pIAL_File)
{
   open(QIODevice::ReadWrite);
   IAL_Decoder = new QAudioDecoder(this);
   IAL_Decoder->setSourceFilename(pIAL_File);
   IAL_Decoder->start();
   while(IAL_Decoder->bufferAvailable())
   {
      IAL_AudioBuffer = IAL_Decoder->read();
      qWarning() << "Buffer size: " << IAL_AudioBuffer.byteCount();
   }
}

QByteArray CIALVirtualChannel::GeraBuffer(QAudioFormat IAL_Formato,
                                        qint64       IAL_Duracao,
                                        int          IAL_FrequenciaHz)
{
    QByteArray m_buffer;

    const int channelBytes = IAL_Formato.sampleSize() / 8;
    const int sampleBytes  = IAL_Formato.channelCount() * channelBytes;

    qint64 length = (IAL_Formato.sampleRate  ()       *
                     IAL_Formato.channelCount()       *
                     channelBytes                   ) *
                     IAL_Duracao / 100000;

    Q_ASSERT(length % sampleBytes == 0);
    Q_UNUSED(sampleBytes) // suppress warning in release builds

    m_buffer.resize(length);
    unsigned char *ptr = reinterpret_cast<unsigned char *>(m_buffer.data());
    int sampleIndex = 0;

    while (length)
    {
        const qreal x = qSin(2 * M_PI * IAL_FrequenciaHz * qreal(sampleIndex % IAL_Formato.sampleRate()) / IAL_Formato.sampleRate());

        for (int i=0; i<IAL_Formato.channelCount(); ++i)
        {
            if (IAL_Formato.sampleSize() == 8 && IAL_Formato.sampleType() == QAudioFormat::UnSignedInt)
            {
                const quint8 value = static_cast<quint8>((1.0 + x) / 2 * 255);
                *reinterpret_cast<quint8*>(ptr) = value;
            }
            else if (IAL_Formato.sampleSize() == 8 && IAL_Formato.sampleType() == QAudioFormat::SignedInt)
            {
                const qint8 value = static_cast<qint8>(x * 127);
                *reinterpret_cast<quint8*>(ptr) = value;
            }
            else if (IAL_Formato.sampleSize() == 16 && IAL_Formato.sampleType() == QAudioFormat::UnSignedInt)
            {
                quint16 value = static_cast<quint16>((1.0 + x) / 2 * 65535);
                if (IAL_Formato.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<quint16>(value, ptr);
                else
                    qToBigEndian<quint16>(value, ptr);
            }
            else if (IAL_Formato.sampleSize() == 16 && IAL_Formato.sampleType() == QAudioFormat::SignedInt)
            {
                qint16 value = static_cast<qint16>(x * 32767);
                if (IAL_Formato.byteOrder() == QAudioFormat::LittleEndian)
                    qToLittleEndian<qint16>(value, ptr);
                else
                    qToBigEndian<qint16>(value, ptr);
            }

            ptr    += channelBytes;
            length -= channelBytes;
        }

        ++sampleIndex;
    }

    return m_buffer;
}
