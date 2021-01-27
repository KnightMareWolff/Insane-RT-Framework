/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IGL_Light.h"

CIGLLight::CIGLLight( )
{
    IGL_Type    = LIGHTTYPE_POINT;
    IGL_Channel = IGL_LIGHT_CHANNEL_01;

    IGL_Pos  = CIMTVector4(0.0f, 0.0f,  0.0f ,1.0f);
    IGL_Dir  = CIMTVector4(0.0f, 0.0f, -1.0f ,1.0f);

    IGL_Ambient = CIMTVector4(0.4f, 0.4f, 0.4f, 1.0f);
    IGL_Diffuse   = CIMTVector4(0.0f, 0.0f, 0.0f, 1.0f);
    IGL_Specular = CIMTVector4(0.0f, 0.0f, 0.0f, 1.0f);

    IGL_ConstantAttenuation   = 0.5f;
    IGL_LinearAttenuation     = 0.001f;
    IGL_QuadraticAttenuation  = 0.0001f;

    IGL_Expoent = 0.5f;
    IGL_CutOff  = 180.0f;

    IGL_Enabled = true;
}

CIGLLight::CIGLLight(IGLLIGHTTYPE pIGL_Type   )
{
    IGL_Type    = pIGL_Type ;
    IGL_Channel = IGL_LIGHT_CHANNEL_01;

    IGL_Pos  = CIMTVector4(0.0f, 0.0f,  0.0f ,1.0f);
    IGL_Dir  = CIMTVector4(0.0f, 0.0f, -1.0f ,1.0f);

    IGL_Ambient = CIMTVector4(0.4f, 0.4f, 0.4f, 1.0f);
    IGL_Diffuse   = CIMTVector4(0.0f, 0.0f, 0.0f, 1.0f);
    IGL_Specular = CIMTVector4(0.0f, 0.0f, 0.0f, 1.0f);

    IGL_ConstantAttenuation   = 0.5f;
    IGL_LinearAttenuation     = 0.001f;
    IGL_QuadraticAttenuation  = 0.0001f;

    IGL_Expoent = 0.5f;
    IGL_CutOff  = 180.0f;

    IGL_Enabled = true;
}

CIGLLight::CIGLLight(int pIGL_Channel)
{
    IGL_Type    = LIGHTTYPE_POINT;
    IGL_Channel = pIGL_Channel;

    IGL_Pos  = CIMTVector4(0.0f, 0.0f,  0.0f ,1.0f);
    IGL_Dir  = CIMTVector4(0.0f, 0.0f, -1.0f ,1.0f);

    IGL_Ambient = CIMTVector4(0.4f, 0.4f, 0.4f, 1.0f);
    IGL_Diffuse   = CIMTVector4(0.0f, 0.0f, 0.0f, 1.0f);
    IGL_Specular = CIMTVector4(0.0f, 0.0f, 0.0f, 1.0f);

    IGL_ConstantAttenuation   = 0.5f;
    IGL_LinearAttenuation     = 0.001f;
    IGL_QuadraticAttenuation  = 0.0001f;

    IGL_Expoent = 0.5f;
    IGL_CutOff  = 180.0f;

    IGL_Enabled = true;
}

CIGLLight::CIGLLight(const CIGLLight & light  )
{
    IGL_Name                =light.IGL_Name ;
    IGL_Type                =light.IGL_Type ;
    IGL_Enabled             =light.IGL_Enabled ;
    IGL_Channel             =light.IGL_Channel ;
    IGL_Pos                 =light.IGL_Pos ;
    IGL_Dir                 =light.IGL_Dir ;
    IGL_Diffuse             =light.IGL_Diffuse ;
    IGL_Ambient             =light.IGL_Ambient ;
    IGL_Specular            =light.IGL_Specular ;
    IGL_Expoent             =light.IGL_Expoent ;
    IGL_CutOff              =light.IGL_CutOff ;
    IGL_ConstantAttenuation =light.IGL_ConstantAttenuation ;
    IGL_LinearAttenuation   =light.IGL_LinearAttenuation ;
    IGL_QuadraticAttenuation=light.IGL_QuadraticAttenuation ;
}

CIGLLight &CIGLLight::operator=(const CIGLLight& opr)
{
    IGL_Name                =opr.IGL_Name ;
    IGL_Type                =opr.IGL_Type ;
    IGL_Enabled             =opr.IGL_Enabled ;
    IGL_Channel             =opr.IGL_Channel ;
    IGL_Pos                 =opr.IGL_Pos ;
    IGL_Dir                 =opr.IGL_Dir ;
    IGL_Diffuse             =opr.IGL_Diffuse ;
    IGL_Ambient             =opr.IGL_Ambient ;
    IGL_Specular            =opr.IGL_Specular ;
    IGL_Expoent             =opr.IGL_Expoent ;
    IGL_CutOff              =opr.IGL_CutOff ;
    IGL_ConstantAttenuation =opr.IGL_ConstantAttenuation ;
    IGL_LinearAttenuation   =opr.IGL_LinearAttenuation ;
    IGL_QuadraticAttenuation=opr.IGL_QuadraticAttenuation ;

    return (*this);
}

void CIGLLight::SetAttenuation(float pIGL_ConstantAttenuation  ,
                               float pIGL_LinearAttenuation    ,
                               float pIGL_QuadraticAttenuation )
{
    IGL_ConstantAttenuation   = pIGL_ConstantAttenuation;
    IGL_LinearAttenuation     = pIGL_LinearAttenuation;
    IGL_QuadraticAttenuation  = pIGL_QuadraticAttenuation;
}
