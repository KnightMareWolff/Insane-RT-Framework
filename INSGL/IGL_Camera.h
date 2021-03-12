/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/

#ifndef IGL_CAMERA_H
#define IGL_CAMERA_H

#include "INSGL_global.h"

class INSGL_EXPORT CIGLCamera
{
public:

    CIGLCamera();
    CIGLCamera(const CIGLCamera & copy  );

    CIGLCamera &operator=(const CIGLCamera& opr);

    QString    IGL_Name          ;
    float      IGL_Speed         ;
    float      IGL_FrameInterval ;
    CIMTVector IGL_Pos           ;
    CIMTVector IGL_View          ;
    CIMTVector IGL_Up            ;
    CIMTVector IGL_Strafe        ;

    float      IGL_FPS           ;
    float      IGL_FOV           ;
    float      IGL_Near          ;
    float      IGL_Far           ;
    float      IGL_LastTimestamp ;
    float      IGL_FrameTimestamp;
    clock_t    IGL_Clock         ;

    int        IGL_ProgramId   ;

    int        IGL_ScreenHeight  ;
    int        IGL_ScreenWidth   ;
    int        IGL_ProjectionType;

    bool       IGL_MainCamera    ;

    void Initialize();

    void SetName      (QString    pIGL_Name          ){IGL_Name          =pIGL_Name;}
    void SetPos       (CIMTVector pIGL_Pos           ){IGL_Pos           =pIGL_Pos;}
    void SetView      (CIMTVector pIGL_View          ){IGL_View          =pIGL_View;}
    void SetUp        (CIMTVector pIGL_Up            ){IGL_Up            =pIGL_Up;}
    void SetStrafe    (CIMTVector pIGL_Strafe        ){IGL_Strafe        =pIGL_Strafe;}
    void SetProjection(int        pIGL_ProjectionType){IGL_ProjectionType=pIGL_ProjectionType;}
    void SetHeight    (int        pIGL_ScreenHeight  ){IGL_ScreenHeight  =pIGL_ScreenHeight;}
    void SetWidth     (int        pIGL_ScreenWidth   ){IGL_ScreenWidth   =pIGL_ScreenWidth;}
    void SetNear      (float      pIGL_Near          ){IGL_Near          =pIGL_Near;}
    void SetFar       (float      pIGL_Far           ){IGL_Far           =pIGL_Far;}
    void SetFOV       (float      pIGL_FOV           ){IGL_FOV           =pIGL_FOV;}
    void SetFPS       (float      pIGL_FPS           ){IGL_FPS           =pIGL_FPS;}

    QString    GetName      (){return IGL_Name;}
    CIMTVector GetPos       (){return IGL_Pos;}
    CIMTVector GetView      (){return IGL_View;}
    CIMTVector GetUp        (){return IGL_Up;}
    CIMTVector GetStrafe    (){return IGL_Strafe;}
    int        GetProjection(){return IGL_ProjectionType;}
    int        GetHeight    (){return IGL_ScreenHeight;}
    int        GetWidth     (){return IGL_ScreenWidth;}
    float      GetNear      (){return IGL_Near;}
    float      GetFar       (){return IGL_Far;}
    float      GetFOV       (){return IGL_FOV;}
    float      GetFPS       (){return IGL_FPS;}

    void SetCamera     (CIMTVector pIGL_Pos ,CIMTVector pIGL_View,CIMTVector  pIGL_Up                    );
    void SetPerspective(float      pIGL_Near,float      pIGL_Far ,int         pIGL_Projection, float pFOV);

    CIMTVector GetDirection();

    void Move    (float       pIGL_AxisDir                           );
    void Update  (CIMTVector  pIGL_Direction, float      pIGL_AxisDir);
    void Rotate  (float       pIGL_DirAngle , CIMTVector pIGL_Axis   );
    void Strafe  (float       pIGL_Strafe                            );
    void Follow  (CIMTVector2 pIGL_Point                             );

    void  CalcTime       (                           );
    void  Reset          (                           );
};



#endif // CCAMERA_H
