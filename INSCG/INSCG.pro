QT += core gui

TEMPLATE = lib
DEFINES += INSCG_LIBRARY

CONFIG += c++11

#Just To MaKe the tests more easy we copy the compiled Library to the examples bin folder
DESTDIR = $$PWD/../Examples/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ICG_BSPProcessor.cpp \
    ICG_CSGProcessor.cpp \
    ICG_HSRProcessor.cpp \
    ICG_MSHProcessor.cpp \
    ICG_PLYProcessor.cpp \
    ICG_PRTProcessor.cpp \
    ICG_PVSProcessor.cpp \
    ICG_RONProcessor.cpp \
    INSCG.cpp

HEADERS += \
    ICG_BSPProcessor.h \
    ICG_CSGProcessor.h \
    ICG_HSRProcessor.h \
    ICG_MSHProcessor.h \
    ICG_PLYProcessor.h \
    ICG_PRTProcessor.h \
    ICG_PVSProcessor.h \
    ICG_RONProcessor.h \
    INSCG_global.h \
    INSCG.h

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
