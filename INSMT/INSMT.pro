QT += core gui

TEMPLATE = lib
DEFINES += INSMT_LIBRARY

CONFIG += c++11

#Just To Mame the tests more easy we copy the compiled Library to the examples bin folder
DESTDIR = $$PWD/../Examples/bin

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    IMT_3DObject.cpp \
    IMT_Bounds.cpp \
    IMT_Grid.cpp \
    IMT_List.cpp \
    IMT_Map.cpp \
    IMT_Matrix.cpp \
    IMT_Mesh.cpp \
    IMT_Node.cpp \
    IMT_Plane.cpp \
    IMT_Polygon.cpp \
    IMT_PriorityQueue.cpp \
    IMT_Quaternion.cpp \
    IMT_Star.cpp \
    IMT_Vector.cpp \
    IMT_Vertex.cpp \
    IMT_VertexBuffer.cpp \
    INSMT.cpp

HEADERS += \
    IMT_3DObject.h \
    IMT_Bounds.h \
    IMT_Graph.h \
    IMT_Grid.h \
    IMT_List.h \
    IMT_Map.h \
    IMT_Matrix.h \
    IMT_Mesh.h \
    IMT_Node.h \
    IMT_Plane.h \
    IMT_Polygon.h \
    IMT_PriorityQueue.h \
    IMT_Quaternion.h \
    IMT_Star.h \
    IMT_Tree.h \
    IMT_Vector.h \
    IMT_Vertex.h \
    IMT_VertexBuffer.h \
    INSMT_global.h \
    INSMT.h


# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

#OpenCV 4.5.1
win32: LIBS += -L$$PWD/../libs/opencv/x64/mingw/lib/ -llibopencv_world451.dll

INCLUDEPATH += $$PWD/../libs/opencv/include
DEPENDPATH += $$PWD/../libs/opencv/include
