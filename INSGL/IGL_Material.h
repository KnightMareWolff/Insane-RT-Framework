/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de CriaÃ§Ã£o     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IGL_MATERIAL_H
#define IGL_MATERIAL_H

#include "INSGL_global.h"
#include "IGL_Texture.h"
#include "IGL_Video.h"

class INSGL_EXPORT CIGLMaterial
{

public:

    CIGLMaterial (                              );
    CIGLMaterial ( const CIGLMaterial & material);

    QString     GetName(){return IGL_Name;}

    CIMTVector4 GetDiffuse   (){return IGL_Diffuse;}
    CIMTVector4 GetAmbient   (){return IGL_Ambient;}
    CIMTVector4 GetEmissive  (){return IGL_Emissive;}
    CIMTVector4 GetSpecular  (){return IGL_Specular;}
    CIMTVector4 GetAlpha     (){return IGL_AlphaColor;}
    float       GetShininess (){return IGL_Shininess;}
    float       GetOpacy     (){return IGL_Opacy;}
    float       GetReflection(){return IGL_Reflection;}
    float       GetRefraction(){return IGL_Refraction;}
    uint        GetTexture   (){return IGL_MaterialTexture;}
    uint        GetMode      (){return IGL_MaterialMode;}
    bool        GetRejection (){return IGL_PixelReject;}

    void    SetDiffuse   (CIMTVector4    pIGL_Diffuse        ){IGL_Diffuse         =pIGL_Diffuse;}
    void    SetAmbient   (CIMTVector4    pIGL_Ambient        ){IGL_Ambient         =pIGL_Ambient;}
    void    SetEmissive  (CIMTVector4    pIGL_Emissive       ){IGL_Emissive        =pIGL_Emissive;}
    void    SetSpecular  (CIMTVector4    pIGL_Specular       ){IGL_Specular        =pIGL_Specular;}
    void    SetShininess (float          pIGL_Shininess      ){IGL_Shininess       =pIGL_Shininess;}
    void    SetOpacy     (float          pIGL_Opacy          ){IGL_Opacy           =pIGL_Opacy;}
    void    SetReflection(float          pIGL_Reflection     ){IGL_Reflection      =pIGL_Reflection;}
    void    SetRefraction(float          pIGL_Refraction     ){IGL_Refraction      =pIGL_Refraction;}
    void    SetName      (QString        pIGL_Name           ){IGL_Name            =pIGL_Name;}
    void    SetMode      (int            pIGL_MaterialMode   ){IGL_MaterialMode    =pIGL_MaterialMode;}
    void    SetTexture   (int            pIGL_MaterialTexture){IGL_MaterialTexture =pIGL_MaterialTexture;}

    void    SetRejection (bool pIGL_PixelReject , CIMTVector4 pIGL_AlphaColor);

    CIGLMaterial &operator=(const CIGLMaterial& opr);

private:

    QString      IGL_Name         ;
    CIMTVector4  IGL_Diffuse      ;
    CIMTVector4  IGL_Ambient      ;
    CIMTVector4  IGL_Emissive     ;
    CIMTVector4  IGL_Specular     ;
    CIMTVector4  IGL_AlphaColor   ;
    bool         IGL_PixelReject  ;//Remove pixel de mesma cor setada
    float        IGL_Opacy        ;
    float        IGL_Shininess    ;
    float        IGL_Reflection   ;//Fator de ReflexÃ£o do Material
    float        IGL_Refraction   ;//Indice de RefraÃ§Ã£o aplicado no Material
    uint         IGL_MaterialMode ;//Modo de Preparo do Material

    int          IGL_MaterialTexture;
};

#endif // IGL_MATERIAL_H
