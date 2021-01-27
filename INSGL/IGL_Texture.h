/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de CriaÃ§Ã£o     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IGL_TEXTURE_H
#define IGL_TEXTURE_H

#include "INSGL_global.h"
#include "IGL_Video.h"

class INSGL_EXPORT CIGLTexture
{
public:

    CIGLTexture();
   ~CIGLTexture();

    CIGLTexture(const CIGLTexture & texture  );

    CIGLTexture &operator=(const CIGLTexture& opr);

    void Clear                (                                                    );
    void CreateTexture        (QString      pIGL_NomeTextura , int pIGL_TextureMode);
    void CreateCubeMap        (QString      pIGL_NomeRight                         ,
                               QString      pIGL_NomeLeft                          ,
                               QString      pIGL_NomeTop                           ,
                               QString      pIGL_NomeBottom                        ,
                               QString      pIGL_NomeBack                          ,
                               QString      pIGL_NomeFront                         );

    void AddLayer             (int          pIGL_IdLayer     , int pIGL_LayerChannel );

    int     GetLayer          (int          pIGL_LayerChannel );
    QString GetName           (                               ){return IGL_Name;}
    void    SetName           (QString pIGL_Name              ){IGL_Name = pIGL_Name;}
    void    RenderToTexture   (CIGLVideo   *pIGL_Video        );

    QString                  IGL_Name         ;//O Nome da textura Ã© o path completo do arquivo.
    unsigned int             IGL_IdT          ;//Id na OpenGL da Textura
    int                      IGL_Height       ,//Altura da Textura
                             IGL_Width        ,//Largura da Textura
                             IGL_Format       ;//Formato da Textura
    vector<int>              IGL_Layers       ;//Vetor de Layers para Multitextura
    CIMTGrid*                IGL_Image        ;//Imagem carregada OpenCV
    CIMTGrid*                IGL_ImageRight   ;//Imagem Cubemap
    CIMTGrid*                IGL_ImageLeft    ;//Imagem Cubemap
    CIMTGrid*                IGL_ImageTop     ;//Imagem Cubemap
    CIMTGrid*                IGL_ImageBottom  ;//Imagem Cubemap
    CIMTGrid*                IGL_ImageBack    ;//Imagem Cubemap
    CIMTGrid*                IGL_ImageFront   ;//Imagem Cubemap
    bool                     IGL_Status       ;//Status de carregamento da textura
    CIGLVideo               *IGL_Video        ;//Ponteiro para Video
    int                      IGL_TextureMode  ;

};


#endif // IGL_TEXTURE_H
