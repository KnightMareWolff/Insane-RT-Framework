#ifndef INSAL_GLOBAL_H
#define INSAL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INSAL_LIBRARY)
#  define INSAL_EXPORT Q_DECL_EXPORT
#else
#  define INSAL_EXPORT Q_DECL_IMPORT
#endif

#include <QtGui>
#include <QtMultimedia>
#include <QAbstractAudioDeviceInfo>
#include <QVideoDeviceSelectorControl>

#include "INSMT.h"

#define IAL_AUDIO_MODE_INPUT  1
#define IAL_AUDIO_MODE_OUTPUT 2

#endif // INSAL_GLOBAL_H
