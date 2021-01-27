QT += core gui opengl openglextensions

TEMPLATE = lib
DEFINES += INSCL_LIBRARY

CONFIG += c++11

#Just To MaKe the tests more easy we copy the compiled Library to the examples bin folder
DESTDIR = $$PWD/../Examples/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ICL_Device.cpp \
    ICL_Kernel.cpp \
    ICL_Platform.cpp \
    ICL_Program.cpp \
    ICL_System.cpp \
    INSCL.cpp

HEADERS += \
    ICL_Device.h \
    ICL_Kernel.h \
    ICL_Platform.h \
    ICL_Program.h \
    ICL_System.h \
    INSCL_global.h \
    INSCL.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#OpenCL
unix|win32: LIBS += -L$$PWD/../libs/opencl/ -lOpenCL

INCLUDEPATH += $$PWD/../libs/opencl/include
DEPENDPATH += $$PWD/../libs/opencl/include


#INSMT
unix|win32: LIBS += -L$$PWD/../Examples/bin/ -lINSMT

INCLUDEPATH += $$PWD/../INSMT
DEPENDPATH += $$PWD/../INSMT

#OpenCV 4.5.1
win32: LIBS += -L$$PWD/../libs/opencv/x64/mingw/lib/ -llibopencv_world451.dll

INCLUDEPATH += $$PWD/../libs/opencv/include
DEPENDPATH += $$PWD/../libs/opencv/include

#Libs do windows adicionais
LIBS += -luser32 -lgdi32 -lopengl32

