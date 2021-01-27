/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IGL_Material.h"

/************************************************************/
/************************************************************/
CIGLMaterial::CIGLMaterial( )
{
    IGL_Opacy        = 1.0f ;
    IGL_Shininess    = 5.0f ;
    IGL_Reflection   = 0.1f;
    IGL_Refraction   = 0.94f;
    IGL_PixelReject  = false;

    IGL_Name = QString("Material Default");

    IGL_MaterialMode = IGL_MATERIAL_COLOR;

    //Laranjado Porreta!!!!
    //IGL_Ambient  = CIMTVector4(0.9f  , 0.5f  , 0.3f  , 1.0f);
    //IGL_Diffuse    = CIMTVector4(0.9f  , 0.5f  , 0.3f  , 1.0f);
    //IGL_Specular  = CIMTVector4(0.8f  , 0.8f  , 0.8f  , 1.0f);
    //IGL_Emissive  = CIMTVector4(0.0f  , 0.0f  , 1.0f  , 1.0f);
    //IGL_AlphaColor   = CIMTVector4(0.0f  , 0.0f  , 0.0f  , 1.0f);

    //Luz Branca
    IGL_Ambient   = CIMTVector4(0.0f  , 0.0f  , 0.0f  , 1.0f);
    IGL_Diffuse   = CIMTVector4(0.3f  , 0.3f  , 0.3f  , 1.0f);
    IGL_Specular  = CIMTVector4(0.5f  , 0.5f  , 0.5f  , 1.0f);
    IGL_Emissive  = CIMTVector4(0.0f  , 0.0f  , 1.0f  , 1.0f);
    IGL_AlphaColor= CIMTVector4(0.0f  , 0.0f  , 0.0f  , 1.0f);

}

CIGLMaterial::CIGLMaterial( const CIGLMaterial & material )
{
    IGL_Shininess    = material.IGL_Shininess;
    IGL_Ambient      = material.IGL_Ambient;
    IGL_Diffuse      = material.IGL_Diffuse;
    IGL_Emissive     = material.IGL_Emissive;
    IGL_Specular     = material.IGL_Specular;
    IGL_AlphaColor   = material.IGL_AlphaColor;
    IGL_Name         = material.IGL_Name;
    IGL_Opacy        = material.IGL_Opacy;
    IGL_Reflection   = material.IGL_Reflection;
    IGL_Refraction   = material.IGL_Refraction;
    IGL_PixelReject  = material.IGL_PixelReject;
}

CIGLMaterial &CIGLMaterial::operator=(const CIGLMaterial& opr)
{
    IGL_Shininess    = opr.IGL_Shininess;
    IGL_Ambient      = opr.IGL_Ambient;
    IGL_Diffuse      = opr.IGL_Diffuse;
    IGL_Emissive     = opr.IGL_Emissive;
    IGL_Specular     = opr.IGL_Specular;
    IGL_AlphaColor   = opr.IGL_AlphaColor;
    IGL_Name         = opr.IGL_Name;
    IGL_PixelReject  = opr.IGL_PixelReject;
    IGL_Opacy        = opr.IGL_Opacy;
    IGL_Reflection   = opr.IGL_Reflection;
    IGL_Refraction   = opr.IGL_Refraction;

    return (*this);
}

void CIGLMaterial::SetRejection (bool pIGL_PixelReject , CIMTVector4 pIGL_AlphaColor)
{
    IGL_PixelReject = pIGL_PixelReject;
    if(pIGL_PixelReject)
    {
       IGL_AlphaColor = pIGL_AlphaColor;
    }
}
