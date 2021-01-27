QT += core gui opengl multimedia openglextensions multimediawidgets

TEMPLATE = lib
DEFINES += INSGL_LIBRARY

CONFIG += c++11

#Just To Mame the tests more easy we copy the compiled Library to the examples bin folder
DESTDIR = $$PWD/../Examples/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IGL_Camera.cpp \
    IGL_ComputeShader.cpp \
    IGL_FragmentShader.cpp \
    IGL_Functions.cpp \
    IGL_FunctionsPCv45.cpp \
    IGL_GeometryShader.cpp \
    IGL_Light.cpp \
    IGL_Material.cpp \
    IGL_Program.cpp \
    IGL_SplashScreen.cpp \
    IGL_TessCtrlShader.cpp \
    IGL_TessEvalShader.cpp \
    IGL_Texture.cpp \
    IGL_VertexShader.cpp \
    IGL_Video.cpp \
    INSGL.cpp

HEADERS += \
    IGL_Camera.h \
    IGL_ComputeShader.h \
    IGL_FragmentShader.h \
    IGL_Functions.h \
    IGL_FunctionsPCv45.h \
    IGL_GeometryShader.h \
    IGL_Light.h \
    IGL_Material.h \
    IGL_Program.h \
    IGL_SplashScreen.h \
    IGL_TessCtrlShader.h \
    IGL_TessEvalShader.h \
    IGL_Texture.h \
    IGL_VertexShader.h \
    IGL_Video.h \
    INSGL_global.h \
    INSGL.h

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


