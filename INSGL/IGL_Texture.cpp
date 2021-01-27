/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IGL_Texture.h"

CIGLTexture::CIGLTexture()
{
   IGL_Height=IGL_Width =  0;
   IGL_IdT              = -1;
   IGL_Image            = NULL;//Imagem carregada OpenCV
   IGL_ImageRight       = NULL;//Imagem Cubemap
   IGL_ImageLeft        = NULL;//Imagem Cubemap
   IGL_ImageTop         = NULL;//Imagem Cubemap
   IGL_ImageBottom      = NULL;//Imagem Cubemap
   IGL_ImageBack        = NULL;//Imagem Cubemap
   IGL_ImageFront       = NULL;//Imagem Cubemap
   IGL_Video            = NULL;
   IGL_TextureMode      = IGL_TEXTURE_LINEAR;
}

CIGLTexture::~CIGLTexture()
{
    IGL_Height=IGL_Width=0;

    IGL_IdT = -1;

    if(IGL_Video)IGL_Video=NULL;

    delete IGL_Image        ;//Imagem carregada OpenCV
    delete IGL_ImageRight   ;//Imagem Cubemap
    delete IGL_ImageLeft    ;//Imagem Cubemap
    delete IGL_ImageTop     ;//Imagem Cubemap
    delete IGL_ImageBottom  ;//Imagem Cubemap
    delete IGL_ImageBack    ;//Imagem Cubemap
    delete IGL_ImageFront   ;//Imagem Cubemap

    IGL_Image        = NULL;//Imagem carregada OpenCV
    IGL_ImageRight   = NULL;//Imagem Cubemap
    IGL_ImageLeft    = NULL;//Imagem Cubemap
    IGL_ImageTop     = NULL;//Imagem Cubemap
    IGL_ImageBottom  = NULL;//Imagem Cubemap
    IGL_ImageBack    = NULL;//Imagem Cubemap
    IGL_ImageFront   = NULL;//Imagem Cubemap

    //Como agora as texturas estão indexadas atraves de alocação de base unica a destruição da textura
    //Na placa de vídeo será realizada pelo Pool de texturas.
    //execGL(IGL_PF_DELTEXTURE,1,&IdT);
}

CIGLTexture::CIGLTexture(const CIGLTexture & texture  )
{
    //Native types copy
    IGL_Name         = texture.IGL_Name;
    IGL_IdT          = texture.IGL_IdT;
    IGL_Height       = texture.IGL_Height;
    IGL_Width        = texture.IGL_Width;
    IGL_Format       = texture.IGL_Format;
    IGL_Layers       = texture.IGL_Layers;
    IGL_Status       = texture.IGL_Status;
    IGL_TextureMode  = texture.IGL_TextureMode;

    //Image Pointers Copy
    if(texture.IGL_Image)      IGL_Image        = new CIMTGrid(*texture.IGL_Image);
    if(texture.IGL_ImageRight) IGL_ImageRight   = new CIMTGrid(*texture.IGL_ImageRight);
    if(texture.IGL_ImageLeft)  IGL_ImageLeft    = new CIMTGrid(*texture.IGL_ImageLeft);
    if(texture.IGL_ImageTop)   IGL_ImageTop     = new CIMTGrid(*texture.IGL_ImageTop);
    if(texture.IGL_ImageBottom)IGL_ImageBottom  = new CIMTGrid(*texture.IGL_ImageBottom);
    if(texture.IGL_ImageBack)  IGL_ImageBack    = new CIMTGrid(*texture.IGL_ImageBack);
    if(texture.IGL_ImageFront) IGL_ImageFront   = new CIMTGrid(*texture.IGL_ImageFront);

    //Video Copy
    IGL_Video = texture.IGL_Video;

}

CIGLTexture &CIGLTexture::operator=(const CIGLTexture& opr)
{
    //Native types copy
    IGL_Name         = opr.IGL_Name;
    IGL_IdT          = opr.IGL_IdT;
    IGL_Height       = opr.IGL_Height;
    IGL_Width        = opr.IGL_Width;
    IGL_Format       = opr.IGL_Format;
    IGL_Layers       = opr.IGL_Layers;
    IGL_Status       = opr.IGL_Status;
    IGL_TextureMode  = opr.IGL_TextureMode;

    //Image Pointers Copy
    if(opr.IGL_Image)      IGL_Image        = new CIMTGrid(*opr.IGL_Image);
    if(opr.IGL_ImageRight) IGL_ImageRight   = new CIMTGrid(*opr.IGL_ImageRight);
    if(opr.IGL_ImageLeft)  IGL_ImageLeft    = new CIMTGrid(*opr.IGL_ImageLeft);
    if(opr.IGL_ImageTop)   IGL_ImageTop     = new CIMTGrid(*opr.IGL_ImageTop);
    if(opr.IGL_ImageBottom)IGL_ImageBottom  = new CIMTGrid(*opr.IGL_ImageBottom);
    if(opr.IGL_ImageBack)  IGL_ImageBack    = new CIMTGrid(*opr.IGL_ImageBack);
    if(opr.IGL_ImageFront) IGL_ImageFront   = new CIMTGrid(*opr.IGL_ImageFront);

    //Video Copy
    IGL_Video = opr.IGL_Video;

    return (*this);
}

void CIGLTexture::Clear()
{
    //Migrate to the a main process in the component
    //execGL(IGL_SH_DELTEXTURE,1,&IGL_IdT);

    IGL_Height=IGL_Width=0;

    IGL_IdT = -1;

    if(IGL_Video)IGL_Video=NULL;
}

void CIGLTexture::CreateTexture(QString pIGL_Name, int pIGL_TextureMode)
{

    IGL_TextureMode = pIGL_TextureMode;

    IGL_Image = new CIMTGrid(pIGL_Name);

    //flip(IGL_Image,IGL_Image,0);
    //cvtColor(IGL_Image,IGL_Image,CV_8UC3);

    IGL_Height    = IGL_Image->Rows();
    IGL_Width     = IGL_Image->Cols();
    IGL_Format    = GL_RGB;
}

void CIGLTexture::CreateCubeMap(QString      pIGL_NomeRight ,
                                QString      pIGL_NomeLeft  ,
                                QString      pIGL_NomeTop   ,
                                QString      pIGL_NomeBottom,
                                QString      pIGL_NomeBack  ,
                                QString      pIGL_NomeFront )
{

    IGL_TextureMode = IGL_TEXTURE_CUBEMAP;

    IGL_ImageRight  = new CIMTGrid(pIGL_NomeRight);
    IGL_ImageLeft   = new CIMTGrid(pIGL_NomeLeft);
    IGL_ImageTop    = new CIMTGrid(pIGL_NomeTop);
    IGL_ImageBottom = new CIMTGrid(pIGL_NomeBottom);
    IGL_ImageBack   = new CIMTGrid(pIGL_NomeBack);
    IGL_ImageFront  = new CIMTGrid(pIGL_NomeFront);

    //flip(IGL_Image,IGL_Image,0);
    //cvtColor(IGL_Image,IGL_Image,CV_8UC3);

    IGL_Height   = IGL_ImageRight->Rows();
    IGL_Width    = IGL_ImageRight->Cols();
    IGL_Format   = GL_RGB;
}

void CIGLTexture::AddLayer(int pIGL_IdLayer, int pIGL_LayerChannel)
{
    IGL_Layers[pIGL_LayerChannel] = pIGL_IdLayer;
}

int CIGLTexture::GetLayer(int pIGL_LayerChannel)
{
    return IGL_Layers[pIGL_LayerChannel];
}

void CIGLTexture::RenderToTexture(CIGLVideo *pIGL_Video)
{
    IGL_Video      = pIGL_Video;
    IGL_TextureMode= IGL_TEXTURE_RENDER;
}
