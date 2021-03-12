/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IGL_LIGHT_H
#define IGL_LIGHT_H

#include "INSGL_global.h"

class INSGL_EXPORT CIGLLight
{

private:

    QString       IGL_Name;
    IGLLIGHTTYPE  IGL_Type;
    bool  		  IGL_Enabled;
    int           IGL_Channel;

    CIMTVector4    IGL_Pos;
    CIMTVector4    IGL_Dir;

    CIMTVector4    IGL_Diffuse ;
    CIMTVector4    IGL_Ambient ;
    CIMTVector4    IGL_Specular;

    float IGL_Expoent;
    float IGL_CutOff;

    float IGL_ConstantAttenuation ;
    float IGL_LinearAttenuation   ;
    float IGL_QuadraticAttenuation;

public:

    CIGLLight(                         );
    CIGLLight(IGLLIGHTTYPE pIGL_Type   );
    CIGLLight(int          pIGL_Channel);
    CIGLLight(const CIGLLight & light  );

    CIGLLight &operator=(const CIGLLight& opr);

    QString     GetName(){return IGL_Name;}

    CIMTVector4 GetDiffuse     (){return IGL_Diffuse;}
    CIMTVector4 GetAmbient     (){return IGL_Ambient;}
    CIMTVector4 GetSpecular    (){return IGL_Specular;}
    float       GetQuadraticAtt(){return IGL_QuadraticAttenuation;}
    float       GetConstantAtt (){return IGL_ConstantAttenuation;}
    float       GetLinearAtt   (){return IGL_LinearAttenuation;}
    float       GetExpoent     (){return IGL_Expoent;}
    float       GetCutOff      (){return IGL_CutOff;}
    CIMTVector4 GetDir         (){return CIMTVector4(IGL_Dir.x,IGL_Dir.y,IGL_Dir.z,1.0f);}
    CIMTVector4 GetPos         (){return CIMTVector4(IGL_Pos.x,IGL_Pos.y,IGL_Pos.z,1.0f);}
    int         GetType        (){return IGL_Type;}


    void    SetDiffuse (CIMTVector4 pIGL_Diffuse ){IGL_Diffuse  = pIGL_Diffuse;}
    void    SetAmbient (CIMTVector4 pIGL_Ambient ){IGL_Ambient  = pIGL_Ambient;}
    void    SetSpecular(CIMTVector4 pIGL_Specular){IGL_Specular = pIGL_Specular;}

    void    SetPos     (CIMTVector4  pIGL_Pos){IGL_Pos  = CIMTVector4(pIGL_Pos.x,pIGL_Pos.y,pIGL_Pos.z , 1.0f);}
    void    SetDir     (CIMTVector4  pIGL_Dir){IGL_Dir  = CIMTVector4(pIGL_Dir.x,pIGL_Dir.y,pIGL_Dir.z , 1.0f);}

    void    SetType    (IGLLIGHTTYPE pIGL_Type){IGL_Type    = pIGL_Type ;}

    void    SetSpotConfig    (float pIGL_Exp , float pIGL_Cut){IGL_Expoent = pIGL_Exp; IGL_CutOff = pIGL_Cut;}

    void    SetAttenuation   (float pIGL_ConstantAttenuation  ,
                              float pIGL_LinearAttenuation    ,
                              float pIGL_QuadraticAttenuation);

    void    SetName      (QString    pIGL_Name        ){IGL_Name        =pIGL_Name;}

    //Migrate This to Global Functions in the Component
    //void    Prepara         (int pIGL_ProgramId,int   Indice   );
    //void    Atualiza        (int pIGL_ProgramId,int   Indice   );

    void    On       (){IGL_Enabled=true;}
    void    Off      (){IGL_Enabled=false;}
    bool    IsEnabled(){return IGL_Enabled;}

private:

    //Migrate This to Global Functions in the Component
    //void PreparaLuzPonto      (int pIGL_ProgramId,GLenum ThisGLLight);
    //void PreparaLuzSpot       (int pIGL_ProgramId,GLenum ThisGLLight);
    //void PreparaLuzDirectional(int pIGL_ProgramId,GLenum ThisGLLight);

};

#endif // IGL_LIGHT_H
