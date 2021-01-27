QT += gui multimedia

TEMPLATE = lib
DEFINES += INSAL_LIBRARY

CONFIG += c++11

#Just To MaKe the tests more easy we copy the compiled Library to the examples bin folder
DESTDIR = $$PWD/../Examples/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IAL_AudioDevice.cpp \
    IAL_Sound.cpp \
    IAL_System.cpp \
    IAL_VirtualChannel.cpp \
    INSAL.cpp

HEADERS += \
    IAL_AudioDevice.h \
    IAL_Sound.h \
    IAL_System.h \
    IAL_VirtualChannel.h \
    INSAL_global.h \
    INSAL.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#INSMT
unix|win32: LIBS += -L$$PWD/../Examples/bin/ -lINSMT

INCLUDEPATH += $$PWD/../INSMT
DEPENDPATH += $$PWD/../INSMT

#OpenCV 4.5.1
unix|win32: LIBS += -L$$PWD/../libs/opencv/x64/mingw/lib/ -llibopencv_world451.dll

INCLUDEPATH += $$PWD/../libs/opencv/include
DEPENDPATH += $$PWD/../libs/opencv/include

