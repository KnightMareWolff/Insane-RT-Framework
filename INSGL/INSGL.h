/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef INSGL_H
#define INSGL_H

#include "INSGL_global.h"
#include "IGL_Functions.h"
#include "IGL_Program.h"
#include "IGL_Material.h"
#include "IGL_Texture.h"
#include "IGL_Light.h"
#include "IGL_Video.h"
#include "IGL_Camera.h"
#include "IGL_SplashScreen.h"


#ifdef Q_OS_WIN
   #include "IGL_FunctionsPCv45.h"
#endif

#ifdef Q_OS_MAC
   #include "IGL_FunctionsMacOS.h"
#endif

#ifdef Q_OS_ANDROID
   #include "IGL_FunctionsAndroid.h"
#endif

#ifdef Q_OS_IOS
   #include "IGL_FunctionsIOS.h"
#endif

class INSGL_EXPORT INSGL
{
public:
    INSGL(                        );
    INSGL(bool pOffScreenRendering);
    INSGL(QOpenGLContext *pContext);

    bool execGL   (int iOglFcn);
    bool execGL   (int iOglFcn, GLuint ProgramId, uint  estado                );
    bool execGL   (int iOglFcn, GLuint ProgramId, const GLchar *nome , int vlr);

    bool execGL   (int iOglFcn, GLuint ProgramId,
                               float   ValorProx,
                               float   ValorDist,
                               int     ValorAltura,
                               int     ValorLargura,
                               float   FOV);

    bool execGL   (int iOglFcn, GLuint ProgramId, CIMTVector Pos, CIMTVector View, CIMTVector Up);

    bool execGL   (int iOglFcn,GLuint          ProgramId        ,
                               CIMTVector4     CorDifusa        ,
                               CIMTVector4     CorAmbiente      ,
                               CIMTVector4     CorEmissiva      ,
                               CIMTVector4     CorSpecular      ,
                               CIMTVector4     CorAlpha         ,
                               bool            bAlphaReject     ,
                               float           opacidade        ,
                               float           brilho           ,
                               float           reflexao         ,
                               float           IndiceRefracao);


    bool execGL   (int iOglFcn,GLuint ProgramId                 ,
                               unsigned int  Id                 ,
                               CIMTVector4   pos                ,
                               CIMTVector4   dir                ,
                               CIMTVector4   CorDifusa          ,
                               CIMTVector4   CorAmbiente        ,
                               CIMTVector4   CorSpecular        ,
                               float         Expoente           ,
                               float         CutOff             ,
                               float         AtenuacaoConstante ,
                               float         AtenuacaoLinear    ,
                               float         AtenuacaoQuadratica);


    bool execGL   (int iOglFcn, GLuint         IGL_TextureId     ,
                                GLuint         IGL_TextureMode   ,
                                GLboolean      IGL_TextureUpdate ,
                                GLubyte       *IGL_TextureData   ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat );

     bool GLEnableStates ();
     bool GLDisableStates();
     bool GLFinish();
     bool GLDeleteTextures(uint pIGL_NumberOfTextures,uint *pIGL_TextureIds);
     bool GLDeleteBuffers (uint pIGL_NumberOfBuffers ,uint *pIGL_BufferIds );

     bool GLReadPixel(int  x, int y ,  GLchar *res);

     bool GLDrawBuffer        (int            IGL_GeometryMode,
                               long           QtdVertices   ,
                               long           QtdIndices    ,
                               GLuint         ProgramId     ,
                               GLuint        *Id            ,
                               bool           FeedBack      ,
                               FeedBackData  *FeedbackBuffer);

     bool GLCreateVertexBuffer(vector<CIMTVertex> IGL_VertexBuffer   ,
                               vector<uint      > IGL_VertexIndices  ,
                               long               IGL_QtdVertices    ,
                               long               IGL_QtdIndices     ,
                               GLuint             IGL_VboIds[2]      );

     bool GLCreateSingleTexture(GLuint        &IGL_TextureId     ,
                                GLubyte       *IGL_TextureData   ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat ,
                                GLuint         IGL_TextureMipmaps);

     bool GLCreateCubeMap      (GLuint        &IGL_TextureId     ,
                                GLubyte       *IGL_TextureRight  ,
                                GLubyte       *IGL_TextureLeft   ,
                                GLubyte       *IGL_TextureTop    ,
                                GLubyte       *IGL_TextureBottom ,
                                GLubyte       *IGL_TextureBack   ,
                                GLubyte       *IGL_TextureFront  ,
                                GLuint         IGL_TextureWidth  ,
                                GLuint         IGL_TextureHeight ,
                                GLuint         IGL_TextureFormat ,
                                GLuint         IGL_TextureMipmaps);

     bool GLSetModelMatrix     (CIMTMatrix mtx  );
     bool GLSetShadingMode     (uint pIGLShading);

     bool SetFrontFace          (uint pIGL_State,uint pIGL_Direction);
     bool SetMaterialMode       (uint pIGL_State,uint pIGL_Mode     );
     bool SetActiveTexture      (uint pIGL_Texture                  );
     bool GLEnable              (uint pIGL_State                    );
     bool GLDisable             (uint pIGL_State                    );

     bool CalculatePVMMatrix    (CIMTMatrix  pIGLModelMatrix            ,
                                 CIMTMatrix &pIGLPVMMatrix              ,
                                 bool        bReset                     );
     int  GetVersion            (                                       );
     bool FenceSync             (GLsync &pIGL_Sync                      );
     bool WaitSync              (GLsync  pIGL_Sync                      );
     bool AddTransformFeedback  (GLuint  ProgramId                      );

     bool TransformBuffer       (GLuint             IGL_VboId        ,
                                 GLuint             IGL_QtdVert      ,
                                 CIMTMatrix         IGL_ModelMatrix  ,
                                 CIMTVertex        *IGL_VertexBuffer );

     CIMTVertex      *MapBuffer  (GLuint             IGL_VboId        );
     bool             UnMapBuffer(                                    );

     //Get the main GPU Vendor(It´s not possible swith between main vendor...)
     QString         GetVendor();
     QOpenGLContext* GetContext(){return pGLContext;}

     //Shader Management Functions
     int  AddProgram     (QString pIGL_NomeProgram);
     void AddShader      (QString pIGL_NomeProgram,QString pIGL_NomeShader,int pIGL_TpShader);
     void AddShader      (int     pIGL_Indice     ,QString pIGL_NomeShader,int pIGL_TpShader);
     void Compile        (                        );
     uint ProgramId      (QString pIGL_NomeProgram);

     //Material,Lights,Textures and Video Management Functions
     CIGLMaterial * AddMaterial       (QString pIGL_MaterialName, int  pIGL_MaterialMode);

     CIGLTexture  * AddTexture        (QString pIGL_TextureName ,
                                       QString pIGL_FileName    ,
                                       int pIGL_TextureMode    );

     CIGLTexture  * AddCubeMapTexture (QString pIMA_TextureName ,
                                       QString pIGL_Right       ,
                                       QString pIGL_Left        ,
                                       QString pIGL_Top         ,
                                       QString pIGL_Bottom      ,
                                       QString pIGL_Back        ,
                                       QString pIGL_Front       );

     CIGLLight    * AddLight   (QString pIGL_LightName   );
     CIGLVideo    * AddVideo   (QString pIGL_VideoName   );
     CIGLCamera   * AddCamera  (QString pIGL_CameraName  );
     CIMT3DObject * Add3DObject(QString pIGL_ObjectName  );

     bool           AddMaterial(QString pIGL_MaterialName, int pIGL_MaterialMode,uint &pIGLIndex);

     bool           AddTexture (QString pIGL_TextureName ,
                                QString pIGL_FileName    ,
                                int     pIGL_TextureMode ,
                                uint   &pIGLIndex        );

     bool           AddCubeMapTexture (QString pIMA_TextureName ,
                                       QString pIGL_Right       ,
                                       QString pIGL_Left        ,
                                       QString pIGL_Top         ,
                                       QString pIGL_Bottom      ,
                                       QString pIGL_Back        ,
                                       QString pIGL_Front       ,
                                       uint   &pIGLIndex        );

     bool           AddLight   (QString pIGL_LightName   ,uint &pIGLIndex);
     bool           AddVideo   (QString pIGL_VideoName   ,uint &pIGLIndex);
     bool           AddCamera  (QString pIGL_CameraName  ,uint &pIGLIndex);
     bool           Add3DObject(QString pIGL_ObjectName  ,uint &pIGLIndex);

     CIGLMaterial * GetMaterial(uint pIGLIndex);
     CIGLTexture  * GetTexture (uint pIGLIndex);
     CIGLLight    * GetLight   (uint pIGLIndex);
     CIGLVideo    * GetVideo   (uint pIGLIndex);
     CIGLCamera   * GetCamera  (uint pIGLIndex);
     CIMT3DObject * Get3DObject(uint pIGLIndex);

     bool GetTextureProperties(int   pIGL_TextureId, uint &pIGL_OpenGLId, uint &pIGL_Height, uint &pIGL_Width, uint &pIGL_Format);

     bool UpdateMaterial(CIGLMaterial *pIGL_Material);
     bool UpdateTexture (CIGLTexture  *pIGL_Texture);
     bool UpdateLight   (CIGLLight    *pIGL_Light);
     bool UpdateVideo   (CIGLVideo    *pIGL_Video);
     bool UpdateCamera  (CIGLCamera   *pIGL_Camera);
     bool Update3DObject(CIMT3DObject *pIGL_Object);

     bool PrepareMaterial(CIGLMaterial *pIGL_Material);
     bool PrepareTexture (CIGLTexture  *pIGL_Texture);
     bool PrepareLight   (CIGLLight    *pIGL_Light);
     bool PrepareCamera  (CIGLCamera   *pIGL_Camera);
     bool Prepare3DObject(CIMT3DObject *pIGL_Object, uint pIGLShading, uint pIGLGeometry);

     bool PrepareMaterial(uint pIGLIndex);
     bool PrepareTexture (uint pIGLIndex);
     bool PrepareLight   (uint pIGLIndex);
     bool PrepareCamera  (uint pIGLIndex);
     bool Prepare3DObject(uint pIGLIndex, uint pIGLShading, uint pIGLGeometry);

     //The single shot functions perform what the Prepare functions do for all objects(Warning!!!)
     //If you prepare single objects AND perform a singleshot too you will duplicate GPU Resources without use them!
     //A Single Shot function to create the textures in the Graphics Board.
     bool SingleShotHWTextures();
     //A Single Shot function to create the Objects VBO´s in the Graphics Board.
     bool SingleShotHWObjects();

     //Rendering Functions
     void RenderScene();
     void PaintSplash(QPainter *painter,QPaintEvent *event,float TimeElapsed);

     CIGLSplashScreen *IGL_Splash;

private:
    static CIGLFunctions     *pGLExec     ;
    static QOpenGLContext    *pGLContext  ;
    static QSurfaceFormat     pGLFormat   ;
    static QOffscreenSurface *pGLOffScreen;

    GLuint IGL_CurrentPgmId;

    /********************************/
    /*Atributos Privados de Acesso  */
    /********************************/
    int                   IGL_PgmCounter;
    int                   IGL_MatCounter;
    int                   IGL_TexCounter;
    int                   IGL_LgtCounter;
    int                   IGL_VidCounter;
    int                   IGL_CamCounter;
    int                   IGL_ObjCounter;

    vector<CIGLProgram *> IGL_Programs;
    vector<CIGLMaterial*> IGL_Materials;
    vector<CIGLTexture *> IGL_Textures;
    vector<CIGLLight   *> IGL_Lights;
    vector<CIGLVideo   *> IGL_Videos;
    vector<CIGLCamera  *> IGL_Cameras;
    vector<CIMT3DObject*> IGL_Objects;

    bool bI3DSuportaShaders       ,
         bI3DSuportaVertexShader  ,
         bI3DSuportaFragmentShader,
         bI3DSuportaTessCtrlShader,
         bI3DSuportaTessEvalShader,
         bI3DSuportaGeometryShader,
         bI3DSuportaComputeShader ,
         bI3DSuportaFeedback      ;

    int CalculateVersion(int iMajor,int iMinor);

    /******************************/
    /*Metodos Privados de Acesso  */
    /******************************/
    bool CheckDuplicated(QString pIGL_NomeProgram,int &pIGL_IndiceExistente,uint pIGL_ListType);
    bool CheckExistent  (QString pIGL_NomeProgram                          ,uint pIGL_ListType);
    bool CheckExistent  (int     pIGL_Indice                               ,uint pIGL_ListType);
    int  GetPgmIndex    (QString pIGL_NomeProgram                          );
};

#endif // INSGL_H
