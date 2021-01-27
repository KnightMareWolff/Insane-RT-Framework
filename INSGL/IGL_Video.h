#ifndef CIGLVideo_H
#define CIGLVideo_H

#include "INSGL_global.h"

class INSGL_EXPORT CIGLVideo
{
public:
     CIGLVideo(QString pIGL_NomeArquivo);
     CIGLVideo(int     pIGL_CameraId   );
    ~CIGLVideo(                        );

    CIGLVideo &operator=(const CIGLVideo& opr);

    bool   GetProperties(uint &pIGL_Altura  ,
                         uint &pIGL_Largura ,
                         uint &pIGL_Formato );

    uchar*  GetFrame ();
    uint    GetStatus(){return IGL_VideoStatus;}
    QString GetName  (){return IGL_Name;}

private:
    QString      IGL_Name         ;
    CIMTGrid     IGL_VideoFrame   ;
    VideoCapture IGL_VideoCapture ;
    uint         IGL_VideoStatus  ;
    uint         IGL_ExecutionMode;
};

#endif // CIMDVIDEO_H
