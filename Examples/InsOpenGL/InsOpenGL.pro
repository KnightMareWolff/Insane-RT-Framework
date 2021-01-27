QT += core gui opengl multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

#Define copia do executavel no diretorio /bin
DESTDIR = $$PWD/../bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    Ex_GLMainScreen.cpp

HEADERS += \
    Ex_GLMainScreen.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#INSGL
unix|win32: LIBS += -L$$PWD/../bin/ -lINSGL

INCLUDEPATH += $$PWD/../../INSGL
DEPENDPATH += $$PWD/../../INSGL


#INSMT
unix|win32: LIBS += -L$$PWD/../bin/ -lINSMT

INCLUDEPATH += $$PWD/../../INSMT
DEPENDPATH += $$PWD/../../INSMT

#OpenCV 4.5.1
unix|win32: LIBS += -L$$PWD/../../libs/opencv/x64/mingw/lib/ -llibopencv_world451.dll

INCLUDEPATH += $$PWD/../../libs/opencv/include
DEPENDPATH += $$PWD/../../libs/opencv/include


#INSCG
unix|win32: LIBS += -L$$PWD/../bin/ -lINSCG

INCLUDEPATH += $$PWD/../../INSCG
DEPENDPATH += $$PWD/../../INSCG
