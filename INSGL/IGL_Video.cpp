#include "IGL_Video.h"

CIGLVideo::CIGLVideo(QString pIGL_NomeArquivo)
{
    if(pIGL_NomeArquivo != "")
    {
        IGL_VideoCapture.open(pIGL_NomeArquivo.toStdString());
        if(!IGL_VideoCapture.isOpened())
        {
            IGL_VideoStatus = IGL_VIDEO_STATUS_OPENERROR;
        }
        else
        {
            IGL_VideoStatus = IGL_VIDEO_STATUS_OPENOK;
            IGL_Name        = pIGL_NomeArquivo;
        }
    }
    IGL_ExecutionMode = IGL_VIDEO_EXEC_LOOP;
}

CIGLVideo::CIGLVideo(int pIGL_CameraId)
{
    if(pIGL_CameraId >= 0)
    {
        IGL_VideoCapture.open(pIGL_CameraId);
        if(!IGL_VideoCapture.isOpened())
        {
            IGL_VideoStatus = IGL_VIDEO_STATUS_OPENERROR;
        }
        else
        {
            IGL_VideoStatus = IGL_VIDEO_STATUS_OPENOK;
            IGL_Name        = QString("Video Camera %1").arg(pIGL_CameraId);
        }
    }
    IGL_ExecutionMode = IGL_VIDEO_EXEC_FOREVER;
}

CIGLVideo::~CIGLVideo()
{
    IGL_VideoCapture.release();
    IGL_VideoStatus = IGL_VIDEO_STATUS_FINISH;
}

CIGLVideo &CIGLVideo::operator=(const CIGLVideo& opr)
{
    IGL_VideoFrame    = opr.IGL_VideoFrame;
    IGL_VideoCapture  = opr.IGL_VideoCapture;
    IGL_VideoStatus   = opr.IGL_VideoStatus;
    IGL_ExecutionMode = opr.IGL_ExecutionMode;
    IGL_Name          = opr.IGL_Name;

    return (*this);
}

bool   CIGLVideo::GetProperties(unsigned int &pIGL_Altura    ,
                                   unsigned int &pIGL_Largura   ,
                                   unsigned int &pIGL_Formato   )
{
    pIGL_Altura  = 256;
    pIGL_Largura = 256;
    pIGL_Formato = GL_RGB;

    return true;
}

uchar* CIGLVideo::GetFrame()
{
    if(IGL_VideoCapture.read(IGL_VideoFrame.IMT_GridData))
    {
       Size sz;
       sz.height = 256;
       sz.width  = 256;

       resize(IGL_VideoFrame.IMT_GridData,IGL_VideoFrame.IMT_GridData,sz,0,0);

       IGL_VideoStatus = IGL_VIDEO_STATUS_PROCESSING;

       return IGL_VideoFrame.IMT_GridData.ptr();
    }
    else
    {
        if(IGL_ExecutionMode == IGL_VIDEO_EXEC_LOOP)
        {
            IGL_VideoCapture.set(cv::CAP_PROP_POS_MSEC,0);
            if(IGL_VideoCapture.read(IGL_VideoFrame.IMT_GridData))
            {
                Size sz;
                sz.height = 256;
                sz.width  = 256;

                //como estamos em realtime uma textura 256 e o suficiente
                resize(IGL_VideoFrame.IMT_GridData,IGL_VideoFrame.IMT_GridData,sz,0,0);

                IGL_VideoStatus = IGL_VIDEO_STATUS_PROCESSING;

                return IGL_VideoFrame.IMT_GridData.ptr();
            }
        }
        if(IGL_ExecutionMode == IGL_VIDEO_EXEC_ONESHOT)
        {
           IGL_VideoStatus = IGL_VIDEO_STATUS_FINISH;
           return NULL;
        }
    }
}


