#include "INSGL.h"

//Now we can create multiple OpenGL Contexts including without a Widget Huhuuu!
CIGLFunctions     * INSGL::pGLExec=NULL;
QOpenGLContext    * INSGL::pGLContext=NULL;
QSurfaceFormat      INSGL::pGLFormat;
QOffscreenSurface * INSGL::pGLOffScreen=NULL;

INSGL::INSGL()
{
    IGL_PgmCounter=0;
    IGL_MatCounter=0;
    IGL_TexCounter=0;
    IGL_LgtCounter=0;
    IGL_VidCounter=0;
    IGL_CamCounter=0;
    IGL_ObjCounter=0;
}

INSGL::INSGL(bool pOffScreenRendering)
{
    int VF,VMaj,VMin;

    //This is just to avoid the situation of the default constructor being used for static context heritage
    if(!pOffScreenRendering)return;

    pGLOffScreen = new QOffscreenSurface();
    pGLOffScreen->create();

    pGLContext = new QOpenGLContext();
    pGLContext->create();
    pGLContext->makeCurrent(pGLOffScreen);

    if(pGLContext->isValid())
    {
       pGLFormat = pGLContext->format();
    }
    else
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Error Creating OpenGL Context");
        qWarning() << "Error Creating OpenGL Context.";

        exit(1);
    }

    VMaj = pGLFormat.majorVersion();
    VMin = pGLFormat.minorVersion();

    VF = CalculateVersion(VMaj,VMin);

    //Force Use the Last Supported OpenGL
    if(VF > 45)
    {
        pGLFormat.setMajorVersion(4);
        pGLFormat.setMinorVersion(5);
        VF=45;
    }

    #ifdef Q_OS_WIN
    switch(VF)
    {
        case 45:{pGLExec = new CIGLFunctionsPCv45(pGLContext,VF,VMaj,VMin);}break;
        default:{pGLExec = new CIGLFunctionsPCv45(pGLContext,VF,VMaj,VMin);}break;
     }
     #endif


    //colocado pq esta mais comum placas com tudo isto
    bI3DSuportaShaders = true;
    bI3DSuportaFeedback= true;

    bI3DSuportaVertexShader  = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex);
    bI3DSuportaFragmentShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment);
    bI3DSuportaTessCtrlShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::TessellationControl);
    bI3DSuportaTessEvalShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::TessellationEvaluation);
    bI3DSuportaGeometryShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Geometry);
    bI3DSuportaComputeShader = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Compute);

    IGL_PgmCounter=0;
    IGL_MatCounter=0;
    IGL_TexCounter=0;
    IGL_LgtCounter=0;
    IGL_VidCounter=0;
    IGL_CamCounter=0;
    IGL_ObjCounter=0;

    int tIGL_ProgId = AddProgram("CoreRender");

 #ifdef Q_OS_WIN
        switch(GetVersion())
        {
           case IGL_OGL_V45:
           {
              AddShader(tIGL_ProgId,"world/Shaders/vs/pc/ins3dvs45.glsl",IGL_VERTEX_SHADER_TYPE);
              AddShader(tIGL_ProgId,"world/Shaders/fs/pc/ins3dfs45.glsl",IGL_FRAGMENT_SHADER_TYPE);
           }break;
           default:
           {
              AddShader(tIGL_ProgId,"world/Shaders/vs/pc/ins3dvs45.glsl",IGL_VERTEX_SHADER_TYPE);
              AddShader(tIGL_ProgId,"world/Shaders/fs/pc/ins3dfs45.glsl",IGL_FRAGMENT_SHADER_TYPE);
           }break;
        }
 #endif
        /***************************************************************/
        /*Versão dos shaders para Mobile!!!                            */
        /***********************************************************************************************/
 #ifdef Q_OS_ANDROID
        AddShader(tIGL_ProgId,":/world/Shaders/vs/android/ins3dvs.glsl",IGL_VERTEX_SHADER_TYPE);
        AddShader(tIGL_ProgId,":/world/Shaders/fs/android/ins3dfs.glsl",IGL_FRAGMENT_SHADER_TYPE);
 #endif

 #ifdef Q_OS_MAC
        AddShader(tIGL_ProgId,":/world/Shaders/vs/mac/ins3dvs.glsl",IGL_VERTEX_SHADER_TYPE);
        AddShader(tIGL_ProgId,":/world/Shaders/fs/mac/ins3dfs.glsl",IGL_FRAGMENT_SHADER_TYPE);
 #endif

        Compile();

        AddMaterial("Material Padrão"     , IGL_MATERIAL_TEXTURE);
        AddMaterial("Material Selecionado", IGL_MATERIAL_COLOR  );

        //Set the Current Program Id
        IGL_CurrentPgmId = ProgramId("CoreRender");

        IGL_Splash = new CIGLSplashScreen();

}

INSGL::INSGL(QOpenGLContext *pContext)
{
    int VF,VMaj,VMin;

    if(pContext->isValid())
    {
       pGLContext = pContext;
       pGLFormat  = pContext->format();

    }
    else
    {
        QMessageBox::information(0, "Insane RT Framework",
                                    "Erro na Criação Contexto OpenGL");
        qWarning() << "Erro na Criação Contexto OpenGL.";

        exit(1);
    }

    VMaj = pGLFormat.majorVersion();
    VMin = pGLFormat.minorVersion();

    VF = CalculateVersion(VMaj,VMin);

    //Force Use the Last Supported OpenGL
    if(VF > 45)
    {
        pGLFormat.setMajorVersion(4);
        pGLFormat.setMinorVersion(5);
        VMaj = 4;
        VMin = 5;
        VF=45;
    }

   #ifdef Q_OS_WIN
   switch(VF)
   {
      //case 40:{pGLExec = new CIGLFunctionsPCv40(pGLContext,VF,VMaj,VMin);}break;
      //case 41:{pGLExec = new CIGLFunctionsPCv41(pGLContext,VF,VMaj,VMin);}break;
      //case 42:{pGLExec = new CIGLFunctionsPCv42(pGLContext,VF,VMaj,VMin);}break;
      //case 43:{pGLExec = new CIGLFunctionsPCv43(pGLContext,VF,VMaj,VMin);}break;
      //case 44:{pGLExec = new CIGLFunctionsPCv44(pGLContext,VF,VMaj,VMin);}break;
      case 45:{pGLExec = new CIGLFunctionsPCv45(pGLContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsPCv45(pGLContext,VF,VMaj,VMin);}break;
   }
   #endif

   #ifdef Q_OS_ANDROID
   switch(VF)
   {
      case 20:{pGLExec = new CIGLFunctionsAndroid(pGLContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsAndroid(pGLContext,VF,VMaj,VMin);}break;
   }
   #endif

   #ifdef Q_OS_MAC
   switch(VF)
   {
      case 20:{pGLExec = new CIGLFunctionsMacOS(pGLContext,VF,VMaj,VMin);}break;
      default:{pGLExec = new CIGLFunctionsMacOS(pGLContext,VF,VMaj,VMin);}break;
   }
   #endif

   //colocado pq esta mais comum placas com tudo isto
   bI3DSuportaShaders = true;
   bI3DSuportaFeedback= true;

   bI3DSuportaVertexShader  = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Vertex);
   bI3DSuportaFragmentShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Fragment);
   bI3DSuportaTessCtrlShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::TessellationControl);
   bI3DSuportaTessEvalShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::TessellationEvaluation);
   bI3DSuportaGeometryShader= QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Geometry);
   bI3DSuportaComputeShader = QOpenGLShader::hasOpenGLShaders(QOpenGLShader::Compute);

   IGL_PgmCounter=0;
   IGL_MatCounter=0;
   IGL_TexCounter=0;
   IGL_LgtCounter=0;
   IGL_VidCounter=0;
   IGL_CamCounter=0;
   IGL_ObjCounter=0;

   int tIGL_ProgId = AddProgram("CoreRender");

#ifdef Q_OS_WIN
       switch(GetVersion())
       {
          case IGL_OGL_V45:
          {
             AddShader(tIGL_ProgId,"world/Shaders/vs/pc/ins3dvs45.glsl",IGL_VERTEX_SHADER_TYPE);
             AddShader(tIGL_ProgId,"world/Shaders/fs/pc/ins3dfs45.glsl",IGL_FRAGMENT_SHADER_TYPE);
          }break;
          default:
          {
             AddShader(tIGL_ProgId,"world/Shaders/vs/pc/ins3dvs45.glsl",IGL_VERTEX_SHADER_TYPE);
             AddShader(tIGL_ProgId,"world/Shaders/fs/pc/ins3dfs45.glsl",IGL_FRAGMENT_SHADER_TYPE);
          }break;
       }
#endif
       /***************************************************************/
       /*Versão dos shaders para Mobile!!!                            */
       /***********************************************************************************************/
#ifdef Q_OS_ANDROID
       AddShader(tIGL_ProgId,":/world/Shaders/vs/android/ins3dvs.glsl",IGL_VERTEX_SHADER_TYPE);
       AddShader(tIGL_ProgId,":/world/Shaders/fs/android/ins3dfs.glsl",IGL_FRAGMENT_SHADER_TYPE);
#endif

#ifdef Q_OS_MAC
       AddShader(tIGL_ProgId,":/world/Shaders/vs/mac/ins3dvs.glsl",IGL_VERTEX_SHADER_TYPE);
       AddShader(tIGL_ProgId,":/world/Shaders/fs/mac/ins3dfs.glsl",IGL_FRAGMENT_SHADER_TYPE);
#endif

       Compile();

       AddMaterial("Material Padrão"     , IGL_MATERIAL_TEXTURE);
       AddMaterial("Material Selecionado", IGL_MATERIAL_COLOR  );

       //Set the Current Program Id
       IGL_CurrentPgmId = ProgramId("CoreRender");

       IGL_Splash = new CIGLSplashScreen();

}

int INSGL::CalculateVersion(int iMajor, int iMinor)
{
    switch(iMajor)
    {
        case 1:
        {
            switch(iMinor)
            {
               case 0:{return 10;}break;
               case 1:{return 11;}break;
               case 2:{return 12;}break;
               case 3:{return 13;}break;
               case 4:{return 14;}break;
               case 5:{return 15;}break;
               default:
               {
                QMessageBox::information(0, "Insane RT Framework",
                                            "Erro de identificação da Versão OGL");
                qWarning() << "Erro de identificação da Versão OGL.";

                exit(1);
               }break;
            }
        }break;

        case 2:
        {
           switch(iMinor)
           {
              case 0:{return 20;}break;
              case 1:{return 21;}break;
              default:
              {
               QMessageBox::information(0, "Insane RT Framework",
                                           "Erro de identificação da Versão OGL");
               qWarning() << "Erro de identificação da Versão OGL.";

               exit(1);
              }break;
           }
        }break;

        case 3:
        {
           switch(iMinor)
           {
              case 0:{return 30;}break;
              case 1:{return 31;}break;
              case 2:{return 32;}break;
              case 3:{return 33;}break;
              default:
              {
               QMessageBox::information(0, "Insane RT Framework",
                                           "Erro de identificação da Versão OGL");
               qWarning() << "Erro de identificação da Versão OGL.";

               exit(1);
              }break;
           }
        }break;

        case 4:
        {
           switch(iMinor)
           {
              case 0:{return 40;}break;
              case 1:{return 41;}break;
              case 2:{return 42;}break;
              case 3:{return 43;}break;
              case 4:{return 44;}break;
              case 5:{return 45;}break;
              case 6:{return 46;}break;
              default:
              {
               QMessageBox::information(0, "Insane RT Framework",
                                           "Erro de identificação da Versão OGL");
               qWarning() << "Erro de identificação da Versão OGL.";

               exit(1);
              }break;
           }
        }break;

        default:
        {
           QMessageBox::information(0, "Insane RT Framework",
                                       "Erro de identificação da Versão OGL");
           qWarning() << "Erro de identificação da Versão OGL.";

           exit(1);

        }break;
    }

    return 0;
}

bool INSGL::GLEnableStates (){pGLExec->iglEnableStates();return true;}
bool INSGL::GLDisableStates(){pGLExec->iglDisableStates();return true;}
bool INSGL::GLFinish(){pGLExec->iglFinish();return true;}

bool INSGL::GLEnable(uint pIGL_State)
{
    pGLExec->iglEnable(pIGL_State);
    return true;
}

bool INSGL::GLDisable(uint pIGL_State)
{
    pGLExec->iglDisable(pIGL_State);
    return true;
}

bool INSGL::SetActiveTexture(uint pIGL_Texture)
{
    pGLExec->iglActiveTexture(pIGL_Texture);
    return true;
}

bool INSGL::SetFrontFace(uint pIGL_State, uint pIGL_Direction)
{
    switch(pIGL_State)
    {
       case IGL_SH_ENABLE:
       {
          switch(pIGL_Direction)
          {
             case IGL_WINMODE_CW :{pGLExec->iglFrontFace(GL_CW );}break;
             case IGL_WINMODE_CCW:{pGLExec->iglFrontFace(GL_CCW);}break;
          }
       }break;

       case IGL_SH_DISABLE:
       {
          switch(pIGL_Direction)
          {
             case IGL_WINMODE_CW :{pGLExec->iglFrontFace(GL_CCW);}break;
             case IGL_WINMODE_CCW:{pGLExec->iglFrontFace(GL_CW );}break;
          }
       }break;

       default:
       {
          qWarning() << "State Parameter Not Found - SetFrontFace.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::SetMaterialMode(uint pIGL_State, uint pIGL_Mode)
{
    switch(pIGL_State)
    {
       case IGL_SH_ENABLE:
       {
          switch(pIGL_Mode)
          {
          case IGL_MATERIAL_COLOR    :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_COLORMATERIAL   );}break;
          case IGL_MATERIAL_TEXTURE  :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_TEXTUREDMATERIAL);}break;
          case IGL_MATERIAL_MIXED    :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_MIXEDMATERIAL   );}break;
          case IGL_MATERIAL_NORMALMAP:{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_NMAPMATERIAL    );}break;
          case IGL_MATERIAL_REFLEXIVE:{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_REFLMATERIAL    );}break;
          case IGL_MATERIAL_REFRATIVE:{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_REFRMATERIAL    );}break;
          case IGL_MATERIAL_CUBEMAP  :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_CUBEMAPMATERIAL );}break;
          }
       }break;

       case IGL_SH_DISABLE:
       {
          switch(pIGL_Mode)
          {
          case IGL_MATERIAL_COLOR    :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_COLORMATERIAL   );}break;
          case IGL_MATERIAL_TEXTURE  :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_COLORMATERIAL   );}break;
          case IGL_MATERIAL_MIXED    :{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_TEXTUREDMATERIAL);}break;
          case IGL_MATERIAL_NORMALMAP:{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_MIXEDMATERIAL   );}break;
          case IGL_MATERIAL_REFLEXIVE:{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_MIXEDMATERIAL   );}break;
          case IGL_MATERIAL_REFRATIVE:{pGLExec->iglMaterialMode(IGL_CurrentPgmId,IGL_SH_MIXEDMATERIAL   );}break;
          }
       }break;

       default:
       {
          qWarning() << "State Parameter Not Found - SetMaterialMode.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::GLDeleteTextures(uint pIGL_NumberOfTextures,uint *pIGL_TextureIds)
{
    pGLExec->iglDeleteTextures(pIGL_NumberOfTextures,pIGL_TextureIds);
    return true;
}
bool INSGL::GLDeleteBuffers (uint pIGL_NumberOfBuffers ,uint *pIGL_BufferIds )
{
    pGLExec->iglDeleteBuffers(pIGL_NumberOfBuffers,pIGL_BufferIds);
    return true;
}

bool INSGL::GLDrawBuffer(int IGL_GeometryMode, long QtdVertices, long QtdIndices, GLuint ProgramId, GLuint *Id, bool FeedBack, FeedBackData *FeedbackBuffer)
{
    pGLExec->iglRenderBuffers(IGL_GeometryMode,
                              QtdVertices     ,
                              QtdIndices      ,
                              ProgramId       ,
                              Id              ,
                              FeedBack        ,
                              FeedbackBuffer  );
    return true;
}

bool INSGL::execGL   (int          iOglFcn          ,
                      GLuint       ProgramId        ,
                      CIMTVector4   CorDifusa        ,
                      CIMTVector4   CorAmbiente      ,
                      CIMTVector4   CorEmissiva      ,
                      CIMTVector4   CorSpecular      ,
                      CIMTVector4   CorAlpha         ,
                      bool         bAlphaReject     ,
                      float        opacidade        ,
                      float        brilho           ,
                      float        reflexao         ,
                      float        IndiceRefracao   )
{
    switch(iOglFcn)
    {
       case IGL_SH_MATERIAL:
       {
          pGLExec->iglSetMaterial(ProgramId     ,
                                   CorDifusa     ,
                                   CorAmbiente   ,
                                   CorEmissiva   ,
                                   CorSpecular   ,
                                   CorAlpha      ,
                                   bAlphaReject  ,
                                   opacidade     ,
                                   brilho        ,
                                   reflexao      ,
                                   IndiceRefracao);
       }break;
       default:
       {
          qWarning() << "Função execGL (material) utilizada em versao nao suportada.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL   (int iOglFcn      ,
                      GLuint ProgramId ,
                      unsigned int  Id ,
                      CIMTVector4    pos,
                      CIMTVector4    dir,
                      CIMTVector4    CorDifusa,
                      CIMTVector4    CorAmbiente,
                      CIMTVector4    CorSpecular,
                      float         Expoente,
                      float         CutOff,
                      float         AtenuacaoConstante,
                      float         AtenuacaoLinear,
                      float         AtenuacaoQuadratica)
{
    switch(iOglFcn)
    {
       case IGL_SH_LIGHT_POINT:
       {
           pGLExec->iglSetPointLight(ProgramId           ,
                                    Id                  ,
                                    pos                 ,
                                    dir                 ,
                                    CorDifusa           ,
                                    CorAmbiente         ,
                                    CorSpecular         ,
                                    Expoente            ,
                                    CutOff              ,
                                    AtenuacaoConstante  ,
                                    AtenuacaoLinear     ,
                                    AtenuacaoQuadratica);
       }break;
       case IGL_SH_LIGHT_DIRECTIONAL:
       {
        pGLExec->iglSetDirectionalLight(ProgramId           ,
                                      Id                  ,
                                      pos                 ,
                                      dir                 ,
                                      CorDifusa           ,
                                      CorAmbiente         ,
                                      CorSpecular         ,
                                      Expoente            ,
                                      CutOff              ,
                                      AtenuacaoConstante  ,
                                      AtenuacaoLinear     ,
                                      AtenuacaoQuadratica);
       }break;
       case IGL_SH_LIGHT_SPOT:
       {
        pGLExec->iglSetSpotLight(ProgramId           ,
                                Id                  ,
                                pos                 ,
                                dir                 ,
                                CorDifusa           ,
                                CorAmbiente         ,
                                CorSpecular         ,
                                Expoente            ,
                                CutOff              ,
                                AtenuacaoConstante  ,
                                AtenuacaoLinear     ,
                                AtenuacaoQuadratica);
       }break;
       default:
       {
          qWarning() << "Função execGL (LUZES PF) Inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint  ProgramId ,float ValorProx,float ValorDist,int ValorAltura,int ValorLargura,float FOV)
{
    switch(iOglFcn)
    {
       case IGL_SH_PERSPECTIVE:
       {
          pGLExec->iglSetPerspectiveView(ProgramId    ,
                                         ValorProx    ,
                                         ValorDist    ,
                                         ValorAltura  ,
                                         ValorLargura ,
                                         FOV         );
       }break;

       case IGL_SH_ORTHO:
       {
          pGLExec->iglSetOrthogonalView(ProgramId    ,
                                       ValorProx    ,
                                       ValorDist    ,
                                       ValorAltura  ,
                                       ValorLargura );
       }break;

       default:
       {
          qWarning() << "Função execGL (perspectiva) Inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint  ProgramId ,CIMTVector Pos,CIMTVector View,CIMTVector Up)
{
    switch(iOglFcn)
    {
       case IGL_SH_LOOKAT:
       {
          pGLExec->iglSetLookAt(ProgramId,Pos,View,Up);
       }break;

       default:
       {
          qWarning() << "Função execGL (Lookat) Inexistente.";
          return false;
       }
    }

    return true;
}

bool INSGL::execGL(int iOglFcn,GLuint  ProgramId ,const GLchar *nome,int vlr)
{
    switch(iOglFcn)
    {
       case IGL_SH_UNIINT:
       {
          pGLExec->iglSetUniformInt(ProgramId,nome,vlr);
       }break;
       default:
       {
          qWarning() << "Função execGL (Nome,Valor) inexistente.";
          return false;
       }
    }

    return true;
}


bool INSGL::GLCreateVertexBuffer(vector<CIMTVertex> IGL_VertexBuffer   ,
                          vector<uint      > IGL_VertexIndices  ,
                          long               IGL_QtdVertices    ,
                          long               IGL_QtdIndices     ,
                          GLuint             IGL_VboIds[2]      )
{
    pGLExec->iglInitBuffers(&IGL_VertexBuffer[0],
                            &IGL_VertexIndices[0],
                            IGL_QtdVertices    ,
                            IGL_QtdIndices     ,
                            IGL_VboIds         );
    return true;
}

bool INSGL::GLSetModelMatrix(CIMTMatrix mtx)
{
    pGLExec->iglSetUniformMatrix(IGL_CurrentPgmId,mtx);
    return true;
}

bool INSGL::GLSetShadingMode(uint pIGLShading)
{
    switch(pIGLShading)
    {
       case IGL_SHADING_MODE_FLAT  : {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",0);}break;
       case IGL_SHADING_MODE_SMOOTH: {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",1);}break;
       case IGL_SHADING_MODE_DIFLAT: {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",2);}break;
       case IGL_SHADING_MODE_DIFOTH: {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",3);}break;
       case IGL_SHADING_MODE_NOONE : {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",4);}break;
       default:{execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",0);}break;
    }
    return true;
}

bool INSGL::GLReadPixel(int  x, int y ,  GLchar *res)
{
    pGLExec->iglReadPixels(x,y,res);
    return true;
}

bool INSGL::GLCreateSingleTexture(GLuint        &IGL_TextureId     ,
                                  GLubyte       *IGL_TextureData   ,
                                  GLuint         IGL_TextureWidth  ,
                                  GLuint         IGL_TextureHeight ,
                                  GLuint         IGL_TextureFormat ,
                                  GLuint         IGL_TextureMipmaps)
{
    pGLExec->iglCreateTexture(IGL_TextureId     ,
                              IGL_TextureData   ,
                              IGL_TextureWidth  ,
                              IGL_TextureHeight ,
                              IGL_TextureFormat ,
                              IGL_TextureMipmaps);
    return true;
}

bool INSGL::GLCreateCubeMap(GLuint        &IGL_TextureId     ,
                            GLubyte       *IGL_TextureRight  ,
                            GLubyte       *IGL_TextureLeft   ,
                            GLubyte       *IGL_TextureTop    ,
                            GLubyte       *IGL_TextureBottom ,
                            GLubyte       *IGL_TextureBack   ,
                            GLubyte       *IGL_TextureFront  ,
                            GLuint         IGL_TextureWidth  ,
                            GLuint         IGL_TextureHeight ,
                            GLuint         IGL_TextureFormat ,
                            GLuint         IGL_TextureMipmaps)
{
    pGLExec->iglCreateCubeMap(IGL_TextureId     ,
                              IGL_TextureRight  ,
                              IGL_TextureLeft   ,
                              IGL_TextureTop    ,
                              IGL_TextureBottom ,
                              IGL_TextureBack   ,
                              IGL_TextureFront  ,
                              IGL_TextureWidth  ,
                              IGL_TextureHeight ,
                              IGL_TextureFormat ,
                              IGL_TextureMipmaps);
    return true;
}

bool INSGL::execGL   (int iOglFcn, GLuint         IGL_TextureId     ,
                                   GLuint         IGL_TextureMode   ,
                                   GLboolean      IGL_TextureUpdate ,
                                   GLubyte       *IGL_TextureData   ,
                                   GLuint         IGL_TextureWidth  ,
                                   GLuint         IGL_TextureHeight ,
                                   GLuint         IGL_TextureFormat )
{
    switch(iOglFcn)
    {
       case IGL_TEXTURE_PREP:
       {
          pGLExec->iglPrepareTexture(IGL_TextureId    ,
                                     IGL_TextureMode  ,
                                     IGL_TextureUpdate,
                                     IGL_TextureData  ,
                                     IGL_TextureWidth ,
                                     IGL_TextureHeight,
                                     IGL_TextureFormat);
       }break;

       default:
       {
          qWarning() << "Função com parametro IGL_TEXTURE_PREP , Não encontrada.";
          return false;
       }break;
    }
    return true;
}

bool INSGL::CalculatePVMMatrix(CIMTMatrix pIGLModelMatrix, CIMTMatrix &pIGLPVMMatrix, bool bReset)
{
    if(bReset)
    {
        return pGLExec->iglCalPVMMatrix(pIGLModelMatrix,pIGLPVMMatrix);
    }
    else
    {
        return pGLExec->iglGetPVMMatrix(pIGLPVMMatrix);
    }
    return false;//apenas para o compilador não reclamar...
}

int INSGL::GetVersion()
{
    return pGLExec->iglGetVersion();
}

bool INSGL::FenceSync(GLsync &pIGL_Sync)
{
   return pGLExec->iglFenceSync(pIGL_Sync);
}

bool INSGL::WaitSync(GLsync  pIGL_Sync)
{
   return pGLExec->iglWaitSync(pIGL_Sync);
}

bool INSGL::AddTransformFeedback(GLuint ProgramId)
{
    pGLExec->iglTransformFeedback(ProgramId);
    return true;
}

bool INSGL::TransformBuffer(GLuint           IGL_VboId       ,
                            GLuint           IGL_QtdVert     ,
                            CIMTMatrix       IGL_ModelMatrix ,
                            CIMTVertex      *IGL_VertexBuffer)
{
    pGLExec->iglTransformBuffer(IGL_VboId          ,
                                IGL_QtdVert        ,
                                IGL_ModelMatrix    ,
                                IGL_VertexBuffer   );
    return true;
}

CIMTVertex * INSGL::MapBuffer(GLuint IGL_VboId)
{
    return pGLExec->iglMapBuffer(IGL_VboId);
}

bool INSGL::UnMapBuffer()
{
    pGLExec->iglUnMapBuffer();
    return true;
}

QString INSGL::GetVendor()
{
   return QString(pGLExec->iglGetString(GL_VENDOR));
}

int INSGL::AddProgram(QString pIGL_ProgramName )
{
    int             IdDuplicado = 0   ;
    //Caso já exista material com este Nome retorna o ID do material existente
    if ( CheckDuplicated(pIGL_ProgramName,IdDuplicado,IGL_LIST_TYPE_SHADERS) ) return IdDuplicado;

    IGL_Programs.push_back(new CIGLProgram());
    //Repassa os valores para o Novo material(Usado a Quantidade previa sem incremento como indice do vetor)
    IGL_Programs[IGL_PgmCounter]->IGL_ProgramName = pIGL_ProgramName;

    //Incrementa contador de materiais
    IGL_PgmCounter += 1;

    //Retorna indice atual onde o material foi alocado
    return IGL_PgmCounter - 1;
}

void INSGL::AddShader(QString pIGL_ProgramName,QString pIGL_NomeShader,int pIGL_TpShader)
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = GetPgmIndex(pIGL_ProgramName);

    if(!CheckExistent(Indice,IGL_LIST_TYPE_SHADERS))return;

    IGL_Programs[Indice]->AddShader(pIGL_NomeShader,pIGL_TpShader);
}

void INSGL::AddShader(int pIGL_Indice,QString pIGL_NomeShader,int pIGL_TpShader)
{
    if(!CheckExistent(pIGL_Indice,IGL_LIST_TYPE_SHADERS))return;

    IGL_Programs[pIGL_Indice]->AddShader(pIGL_NomeShader,pIGL_TpShader);
}

void INSGL::Compile()
{
    for(uint i=0 ; i<IGL_Programs.size();i++)
    {
        if(IGL_Programs[i]->IGL_Feedback)
        {
            AddTransformFeedback(IGL_Programs[i]->programId());
        }

        IGL_Programs[i]->link();
        IGL_Programs[i]->bind();
    }
}

uint INSGL::ProgramId(QString pIGL_ProgramName)
{
    //Como o Nome é a chave de pesquisa, checamos se o mesmo existe
    int Indice = GetPgmIndex(pIGL_ProgramName);

    return IGL_Programs[Indice]->programId();
}

bool INSGL::CheckDuplicated(QString pIGL_ProgramName, int &pIGL_IndiceExistente, uint pIGL_ListType)
{
    switch(pIGL_ListType)
    {
    case IGL_LIST_TYPE_SHADERS:
    {
        for(int i=0;i<IGL_PgmCounter;i++)
        {
            if(IGL_Programs[i]->IGL_ProgramName == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_MATERIALS:
    {
        for(int i=0;i<IGL_MatCounter;i++)
        {
            if(IGL_Materials[i]->GetName() == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_TEXTURES:
    {
        for(int i=0;i<IGL_TexCounter;i++)
        {
            if(IGL_Textures[i]->GetName() == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_LIGHTS:
    {
        for(int i=0;i<IGL_LgtCounter;i++)
        {
            if(IGL_Lights[i]->GetName() == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_VIDEOS:
    {
        for(int i=0;i<IGL_VidCounter;i++)
        {
            if(IGL_Videos[i]->GetName() == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_CAMERAS:
    {
        for(int i=0;i<IGL_CamCounter;i++)
        {
            if(IGL_Cameras[i]->GetName() == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_OBJECTS:
    {
        for(int i=0;i<IGL_ObjCounter;i++)
        {
            if(IGL_Objects[i]->GetName() == pIGL_ProgramName)
            {
                pIGL_IndiceExistente = i;
                return true;
            }
        }
    }break;
    }

    pIGL_IndiceExistente = -1;

    return false;
}

bool INSGL::CheckExistent(QString pIGL_ProgramName, uint pIGL_ListType)
{
    switch(pIGL_ListType)
    {
    case IGL_LIST_TYPE_SHADERS:
    {
        for(int i=0;i<IGL_PgmCounter;i++)
        {
            if(IGL_Programs[i]->IGL_ProgramName == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_MATERIALS:
    {
        for(int i=0;i<IGL_MatCounter;i++)
        {
            if(IGL_Materials[i]->GetName() == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_TEXTURES:
    {
        for(int i=0;i<IGL_TexCounter;i++)
        {
            if(IGL_Textures[i]->GetName() == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_LIGHTS:
    {
        for(int i=0;i<IGL_LgtCounter;i++)
        {
            if(IGL_Lights[i]->GetName() == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_VIDEOS:
    {
        for(int i=0;i<IGL_VidCounter;i++)
        {
            if(IGL_Videos[i]->GetName() == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_CAMERAS:
    {
        for(int i=0;i<IGL_CamCounter;i++)
        {
            if(IGL_Cameras[i]->GetName() == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    case IGL_LIST_TYPE_OBJECTS:
    {
        for(int i=0;i<IGL_ObjCounter;i++)
        {
            if(IGL_Objects[i]->GetName() == pIGL_ProgramName)
            {
                return true;
            }
        }
    }break;
    }
    return false;
}

bool INSGL::CheckExistent(int pIGL_Indice, uint pIGL_ListType)
{
    switch(pIGL_ListType)
    {
    case IGL_LIST_TYPE_SHADERS:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_PgmCounter-1)return false;
    }break;
    case IGL_LIST_TYPE_MATERIALS:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_MatCounter-1)return false;
    }break;
    case IGL_LIST_TYPE_TEXTURES:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_TexCounter-1)return false;
    }break;
    case IGL_LIST_TYPE_LIGHTS:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_LgtCounter-1)return false;
    }break;
    case IGL_LIST_TYPE_VIDEOS:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_VidCounter-1)return false;
    }break;
    case IGL_LIST_TYPE_CAMERAS:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_CamCounter-1)return false;
    }break;
    case IGL_LIST_TYPE_OBJECTS:
    {
        if(pIGL_Indice < 0               )return false;
        if(pIGL_Indice > IGL_ObjCounter-1)return false;
    }break;
    }

    return true;
}

int INSGL::GetPgmIndex(QString pIGL_ProgramName)
{
    for(int i=0;i<IGL_PgmCounter;i++)
    {
        if(IGL_Programs[i]->IGL_ProgramName == pIGL_ProgramName)
        {
            return i;
        }
    }
    return -1;
}

//Material,Lights,Textures and Video Management Functions
CIGLMaterial * INSGL::AddMaterial(QString pIGL_MaterialName, int pIGL_MaterialMode)
{
    int             IdDuplicado = 0   ;
    //Caso já exista material com este Nome retorna o ID do material existente
    if ( CheckDuplicated(pIGL_MaterialName,IdDuplicado,IGL_LIST_TYPE_MATERIALS) ) return IGL_Materials[IdDuplicado];

    IGL_Materials.push_back(new CIGLMaterial());
    //Repassa os valores para o Novo material(Usado a Quantidade previa sem incremento como indice do vetor)
    IGL_Materials[IGL_MatCounter]->SetName(pIGL_MaterialName);
    //Define qual sera o material mode usado na renderizacao
    IGL_Materials[IGL_MatCounter]->SetMode(pIGL_MaterialMode);

    //Incrementa contador de materiais
    IGL_MatCounter += 1;

    //Retorna indice atual onde o material foi alocado
    return IGL_Materials[IGL_MatCounter - 1];

}

bool INSGL::AddMaterial(QString pIGL_MaterialName,int pIGL_MaterialMode,uint &pIGLIndex)
{
    int             IdDuplicado = 0   ;

    //Caso já exista material com este Nome retorna o ID do material existente
    if ( CheckDuplicated(pIGL_MaterialName,IdDuplicado,IGL_LIST_TYPE_MATERIALS) ) return false;

    IGL_Materials.push_back(new CIGLMaterial());
    //Repassa os valores para o Novo material(Usado a Quantidade previa sem incremento como indice do vetor)
    IGL_Materials[IGL_MatCounter]->SetName(pIGL_MaterialName);
    //Define qual sera o material mode usado na renderizacao
    IGL_Materials[IGL_MatCounter]->SetMode(pIGL_MaterialMode);

    //Incrementa contador de materiais
    IGL_MatCounter += 1;

    pIGLIndex = IGL_MatCounter - 1;

    //Retorna indice atual onde o material foi alocado
    return true;
}

CIGLTexture  * INSGL::AddTexture (QString pIGL_TextureName ,
                                  QString pIGL_FileName    ,
                                  int pIGL_TextureMode     )
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_TextureName,IdDuplicado,IGL_LIST_TYPE_TEXTURES) ) return IGL_Textures[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Textures.push_back(new CIGLTexture());
    IGL_Textures[IGL_TexCounter]->SetName(pIGL_TextureName);
    IGL_Textures[IGL_TexCounter]->CreateTexture(pIGL_FileName,pIGL_TextureMode);

    //incrementa a quantidade de texturas
    IGL_TexCounter += 1;

    //retorna o indice atual da nova textura
    return IGL_Textures[IGL_TexCounter - 1];

}

CIGLTexture  * INSGL::AddCubeMapTexture (QString pIGL_TextureName ,
                                         QString pIGL_Right       ,
                                         QString pIGL_Left        ,
                                         QString pIGL_Top         ,
                                         QString pIGL_Bottom      ,
                                         QString pIGL_Back        ,
                                         QString pIGL_Front       )
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_TextureName,IdDuplicado,IGL_LIST_TYPE_TEXTURES) ) return IGL_Textures[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Textures.push_back(new CIGLTexture());
    IGL_Textures[IGL_TexCounter]->CreateCubeMap(pIGL_Right,
                                                pIGL_Left,
                                                pIGL_Top,
                                                pIGL_Bottom,
                                                pIGL_Back,
                                                pIGL_Front);

    //incrementa a quantidade de texturas
    IGL_TexCounter += 1;

    //retorna o indice atual da nova textura
    return IGL_Textures[IGL_TexCounter - 1];

}

bool INSGL::AddTexture (QString pIGL_TextureName , QString pIGL_FileName    , int pIGL_TextureMode, uint &pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_TextureName,IdDuplicado,IGL_LIST_TYPE_TEXTURES) ) return false;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Textures.push_back(new CIGLTexture());
    IGL_Textures[IGL_TexCounter]->SetName(pIGL_TextureName);
    IGL_Textures[IGL_TexCounter]->CreateTexture(pIGL_FileName,pIGL_TextureMode);

    //incrementa a quantidade de texturas
    IGL_TexCounter += 1;

    pIGLIndex = IGL_TexCounter - 1;

    //retorna o indice atual da nova textura
    return true;
}

bool INSGL::AddCubeMapTexture (QString pIGL_TextureName ,
                               QString pIGL_Right       ,
                               QString pIGL_Left        ,
                               QString pIGL_Top         ,
                               QString pIGL_Bottom      ,
                               QString pIGL_Back        ,
                               QString pIGL_Front       ,
                               uint   &pIGLIndex        )
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_TextureName,IdDuplicado,IGL_LIST_TYPE_TEXTURES) ) return IGL_Textures[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Textures.push_back(new CIGLTexture());
    IGL_Textures[IGL_TexCounter]->SetName(pIGL_TextureName);
    IGL_Textures[IGL_TexCounter]->CreateCubeMap(pIGL_Right,
                                                pIGL_Left,
                                                pIGL_Top,
                                                pIGL_Bottom,
                                                pIGL_Back,
                                                pIGL_Front);

    //incrementa a quantidade de texturas
    IGL_TexCounter += 1;

    pIGLIndex = IGL_TexCounter - 1;

    //retorna o indice atual da nova textura
    return true;

}

CIGLLight    * INSGL::AddLight   (QString pIGL_LightName   )
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_LightName,IdDuplicado,IGL_LIST_TYPE_LIGHTS) ) return IGL_Lights[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Lights.push_back(new CIGLLight());
    IGL_Lights[IGL_LgtCounter]->SetName(pIGL_LightName);

    //incrementa a quantidade de texturas
    IGL_LgtCounter += 1;

    //retorna o indice atual da nova textura
    return IGL_Lights[IGL_LgtCounter - 1];
}

bool INSGL::AddLight   (QString pIGL_LightName   ,uint &pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_LightName,IdDuplicado,IGL_LIST_TYPE_LIGHTS) ) return false;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Lights.push_back(new CIGLLight());
    IGL_Lights[IGL_LgtCounter]->SetName(pIGL_LightName);

    //incrementa a quantidade de texturas
    IGL_LgtCounter += 1;

    pIGLIndex = IGL_LgtCounter - 1;

    //retorna o indice atual da nova textura
    return true;
}

CIGLVideo    * INSGL::AddVideo   (QString pIGL_VideoName)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_VideoName,IdDuplicado,IGL_LIST_TYPE_VIDEOS) ) return IGL_Videos[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Videos.push_back(new CIGLVideo(pIGL_VideoName));

    //incrementa a quantidade de texturas
    IGL_VidCounter += 1;

    //retorna o indice atual da nova textura
    return IGL_Videos[IGL_VidCounter - 1];
}

bool INSGL::AddVideo   (QString pIGL_VideoName , uint &pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_VideoName,IdDuplicado,IGL_LIST_TYPE_VIDEOS) ) return false;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Videos.push_back(new CIGLVideo(pIGL_VideoName));

    //incrementa a quantidade de texturas
    IGL_VidCounter += 1;

    pIGLIndex = IGL_VidCounter - 1;

    //retorna o indice atual da nova textura
    return true;
}


CIGLCamera    * INSGL::AddCamera   (QString pIGL_CameraName)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_CameraName,IdDuplicado,IGL_LIST_TYPE_CAMERAS) ) return IGL_Cameras[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Cameras.push_back(new CIGLCamera());
    IGL_Cameras[IGL_CamCounter]->SetName(pIGL_CameraName);

    //incrementa a quantidade de texturas
    IGL_CamCounter += 1;

    //retorna o indice atual da nova textura
    return IGL_Cameras[IGL_CamCounter - 1];
}

bool INSGL::AddCamera   (QString pIGL_CameraName , uint &pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_CameraName,IdDuplicado,IGL_LIST_TYPE_CAMERAS) ) return false;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Cameras.push_back(new CIGLCamera());
    IGL_Cameras[IGL_CamCounter]->SetName(pIGL_CameraName);

    //incrementa a quantidade de texturas
    IGL_CamCounter += 1;

    pIGLIndex = IGL_CamCounter - 1;

    //retorna o indice atual da nova textura
    return true;
}

CIMT3DObject * INSGL::Add3DObject(QString pIGL_ObjectName)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_ObjectName,IdDuplicado,IGL_LIST_TYPE_OBJECTS) ) return IGL_Objects[IdDuplicado];

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Objects.push_back(new CIMT3DObject());
    IGL_Objects[IGL_ObjCounter]->SetName(pIGL_ObjectName);

    //incrementa a quantidade de texturas
    IGL_ObjCounter += 1;

    //retorna o indice atual da nova textura
    return IGL_Objects[IGL_ObjCounter - 1];
}

bool INSGL::Add3DObject(QString pIGL_ObjectName , uint &pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_ObjectName,IdDuplicado,IGL_LIST_TYPE_OBJECTS) ) return false;

    //Por enquanto esta sendo construida as texturas no momento do Add, porem esta sendo incluido
    //métodos para se apenas alocar e construir todas de uma vez só após a definição dos arquivos
    IGL_Objects.push_back(new CIMT3DObject());
    IGL_Objects[IGL_ObjCounter]->SetName(pIGL_ObjectName);

    //incrementa a quantidade de texturas
    IGL_ObjCounter += 1;

    pIGLIndex = IGL_ObjCounter - 1;

    //retorna o indice atual da nova textura
    return true;
}

//TODO: Include Error Checkings
CIGLMaterial * INSGL::GetMaterial(uint pIGLIndex){return IGL_Materials[pIGLIndex];}
CIGLTexture  * INSGL::GetTexture (uint pIGLIndex){return IGL_Textures [pIGLIndex];}
CIGLLight    * INSGL::GetLight   (uint pIGLIndex){return IGL_Lights   [pIGLIndex];}
CIGLVideo    * INSGL::GetVideo   (uint pIGLIndex){return IGL_Videos   [pIGLIndex];}
CIGLCamera   * INSGL::GetCamera  (uint pIGLIndex){return IGL_Cameras  [pIGLIndex];}
CIMT3DObject * INSGL::Get3DObject(uint pIGLIndex){return IGL_Objects  [pIGLIndex];}


bool INSGL::UpdateMaterial(CIGLMaterial *pIGL_Material)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Material->GetName(),IdDuplicado,IGL_LIST_TYPE_MATERIALS) )
    {
        *IGL_Materials[IdDuplicado] = *pIGL_Material;
        return true;
    }
    return false;
}

bool INSGL::UpdateTexture (CIGLTexture  *pIGL_Texture)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Texture->IGL_Name,IdDuplicado,IGL_LIST_TYPE_TEXTURES) )
    {
        *IGL_Textures[IdDuplicado] = *pIGL_Texture;
        return true;
    }
    return false;
}

bool INSGL::UpdateLight   (CIGLLight    *pIGL_Light)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Light->GetName(),IdDuplicado,IGL_LIST_TYPE_LIGHTS) )
    {
        *IGL_Lights[IdDuplicado] = *pIGL_Light;
        return true;
    }
    return false;
}

bool INSGL::UpdateVideo(CIGLVideo *pIGL_Video)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Video->GetName(),IdDuplicado,IGL_LIST_TYPE_VIDEOS) )
    {
        *IGL_Videos[IdDuplicado] = *pIGL_Video;
        return true;
    }
    return false;
}

bool INSGL::UpdateCamera(CIGLCamera *pIGL_Camera)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Camera->GetName(),IdDuplicado,IGL_LIST_TYPE_CAMERAS) )
    {
        *IGL_Cameras[IdDuplicado] = *pIGL_Camera;
        return true;
    }
    return false;
}

bool INSGL::Update3DObject(CIMT3DObject *pIGL_Object)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Object->GetName(),IdDuplicado,IGL_LIST_TYPE_OBJECTS) )
    {
        *IGL_Objects[IdDuplicado] = *pIGL_Object;
        return true;
    }
    return false;
}

bool INSGL::PrepareMaterial(CIGLMaterial *pIGL_Material)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Material->GetName(),IdDuplicado,IGL_LIST_TYPE_MATERIALS) )
    {
        if(pIGL_Material->GetMode() == IGL_MATERIAL_REFLEXIVE)pIGL_Material->SetReflection(0.85f);
        if(pIGL_Material->GetMode() == IGL_MATERIAL_REFRATIVE)pIGL_Material->SetRefraction(0.1f);

        execGL(IGL_SH_MATERIAL,IGL_CurrentPgmId,
                               pIGL_Material->GetDiffuse()   ,
                               pIGL_Material->GetAmbient()   ,
                               pIGL_Material->GetEmissive()  ,
                               pIGL_Material->GetSpecular()  ,
                               pIGL_Material->GetAlpha()     ,
                               pIGL_Material->GetRejection() ,
                               pIGL_Material->GetOpacy()     ,
                               pIGL_Material->GetShininess() ,
                               pIGL_Material->GetReflection(),
                               pIGL_Material->GetRefraction());

        switch(pIGL_Material->GetMode())
        {
        case IGL_MATERIAL_COLOR:
        {
           SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_COLOR);
        }break;
        case IGL_MATERIAL_TEXTURE:
        {
           SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_TEXTURE);
           //PrepareTexture(pIGL_Material->GetTexture());
        }break;
        case IGL_MATERIAL_MIXED:
        {
            SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_MIXED);
            //PrepareTexture(pIGL_Material->GetTexture());

        }break;
        case IGL_MATERIAL_NORMALMAP:
        {
           SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_NORMALMAP);
           //PrepareTexture(pIGL_Material->GetTexture());

        }break;
        case IGL_MATERIAL_REFLEXIVE:
        {
           SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_REFLEXIVE);
           //PrepareTexture(pIGL_Material->GetTexture());

        }break;
        case IGL_MATERIAL_REFRATIVE:
        {
           SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_REFRATIVE);
           //PrepareTexture(pIGL_Material->GetTexture());

        }break;
        case IGL_MATERIAL_CUBEMAP:
        {
           SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_CUBEMAP);
           //PrepareTexture(pIGL_Material->GetTexture());
        }break;
        }
        return true;
    }
    return false;
}

bool INSGL::GetTextureProperties(int   pIGL_TextureId ,
                                   uint &pIGL_OpenGLId  ,
                                   uint &pIGL_Height    ,
                                   uint &pIGL_Width     ,
                                   uint &pIGL_Format    )
{
    pIGL_OpenGLId = IGL_Textures[pIGL_TextureId]->IGL_IdT;
    pIGL_Height   = IGL_Textures[pIGL_TextureId]->IGL_Height;
    pIGL_Width    = IGL_Textures[pIGL_TextureId]->IGL_Width;
    pIGL_Format   = IGL_Textures[pIGL_TextureId]->IGL_Format;
    return true;
}

bool INSGL::PrepareTexture (CIGLTexture  *pIGL_Texture)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Texture->GetName(),IdDuplicado,IGL_LIST_TYPE_TEXTURES) )
    {
        unsigned int tOpenGLId,tAltura,tLargura,tFormato;

        //Seta Multitextura como verdadeiro
        execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"multitextura",1);

        GLEnable(GL_TEXTURE_2D);
        SetActiveTexture(GL_TEXTURE0);
        execGL(IGL_SH_UNIINT       ,IGL_CurrentPgmId,"textura_base",0);

        //Caso seja um Render to Texture prepara a textura atualizando a imagem
        if(pIGL_Texture->IGL_TextureMode==IGL_TEXTURE_RENDER)
        {
            if(pIGL_Texture->IGL_Video->GetStatus() != IGL_VIDEO_STATUS_FINISH)
            {
               pIGL_Texture->IGL_Video->GetProperties(tAltura,tLargura,tFormato);

               execGL(IGL_TEXTURE_PREP,pIGL_Texture->IGL_IdT,IGL_TEXTURE_LINEAR,true ,pIGL_Texture->IGL_Video->GetFrame(),tAltura,tLargura,tFormato);
            }
            else
            {
               execGL(IGL_TEXTURE_PREP,pIGL_Texture->IGL_IdT,pIGL_Texture->IGL_TextureMode,false,NULL,0,0,pIGL_Texture->IGL_Format);
            }
        }
        else
        {
            //Prepara a textura normal sem atualizar a imagem
            execGL(IGL_TEXTURE_PREP,pIGL_Texture->IGL_IdT,pIGL_Texture->IGL_TextureMode,false,NULL,0,0,pIGL_Texture->IGL_Format);
        }

        //processa os Layers da textura
        for(uint iLayer=0 ;iLayer < pIGL_Texture->IGL_Layers.size(); iLayer++)
        {
            switch(iLayer)
            {
               case 0:
               {
                   GLEnable(GL_TEXTURE_2D);
                   SetActiveTexture(GL_TEXTURE1);
                   execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"textura_detalhe",1);

                   GetTextureProperties(pIGL_Texture->IGL_Layers[iLayer],tOpenGLId,tAltura,tLargura,tFormato);

                   execGL(IGL_TEXTURE_PREP,tOpenGLId,pIGL_Texture->IGL_TextureMode,false,NULL,0,0,tFormato);

               }break;
               case 1:
               {
                   GLEnable(GL_TEXTURE_2D);
                   SetActiveTexture(GL_TEXTURE2);
                   execGL(IGL_SH_UNIINT       ,IGL_CurrentPgmId,"textura_normal_map",2);

                   GetTextureProperties(pIGL_Texture->IGL_Layers[iLayer],tOpenGLId,tAltura,tLargura,tFormato);

                   execGL(IGL_TEXTURE_PREP,tOpenGLId,pIGL_Texture->IGL_TextureMode,false,NULL,0,0,tFormato);
               }break;
               case 2:
               {
                   GLEnable(GL_TEXTURE_2D);
                   SetActiveTexture(GL_TEXTURE3);
                   execGL(IGL_SH_UNIINT       ,IGL_CurrentPgmId,"textura_cube_map",3);

                   GetTextureProperties(pIGL_Texture->IGL_Layers[iLayer],tOpenGLId,tAltura,tLargura,tFormato);

                   execGL(IGL_TEXTURE_PREP,tOpenGLId,pIGL_Texture->IGL_TextureMode,false,NULL,0,0,tFormato);
               }break;
               case 3:
               {
                   //execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE4);
                   //execGL(IGL_SH_UNIINT,"textura_cube_map",3);
                   //pI3DTextureManager->Bind(IGL_Layers[iLayer]);
                   //pI3DTextureManager->SetaWrapMode(IGL_Layers[iLayer],pTextMode);
                }break;
                default:
                {
                   qWarning() << "Atenção! Numero de Layers em Textura excedido!.";
                }break;
             }
         }
        return true;
    }
    return false;
}
bool INSGL::PrepareLight(CIGLLight *pIGL_Light)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Light->GetName(),IdDuplicado,IGL_LIST_TYPE_LIGHTS) )
    {
        switch(pIGL_Light->GetType())
        {
           case LIGHTTYPE_POINT:
           {
            execGL(IGL_SH_LIGHT_POINT                ,
                       IGL_CurrentPgmId              ,
                       (GLenum)IdDuplicado           ,
                       pIGL_Light->GetPos()          ,
                       pIGL_Light->GetDir()          ,
                       pIGL_Light->GetDiffuse()      ,
                       pIGL_Light->GetAmbient()      ,
                       pIGL_Light->GetSpecular()     ,
                       pIGL_Light->GetExpoent()      ,
                       pIGL_Light->GetCutOff()       ,
                       pIGL_Light->GetConstantAtt()  ,
                       pIGL_Light->GetLinearAtt()    ,
                       pIGL_Light->GetQuadraticAtt());
           }break;
           case LIGHTTYPE_SPOT:
           {
            execGL(IGL_SH_LIGHT_SPOT                 ,
                       IGL_CurrentPgmId              ,
                       (GLenum)IdDuplicado           ,
                       pIGL_Light->GetPos()          ,
                       pIGL_Light->GetDir()          ,
                       pIGL_Light->GetDiffuse()      ,
                       pIGL_Light->GetAmbient()      ,
                       pIGL_Light->GetSpecular()     ,
                       pIGL_Light->GetExpoent()      ,
                       pIGL_Light->GetCutOff()       ,
                       pIGL_Light->GetConstantAtt()  ,
                       pIGL_Light->GetLinearAtt()    ,
                       pIGL_Light->GetQuadraticAtt());
           }break;
           case LIGHTTYPE_DIRECTIONAL:
           {
            execGL(IGL_SH_LIGHT_DIRECTIONAL          ,
                       IGL_CurrentPgmId              ,
                       (GLenum)IdDuplicado           ,
                       pIGL_Light->GetPos()          ,
                       pIGL_Light->GetDir()          ,
                       pIGL_Light->GetDiffuse()      ,
                       pIGL_Light->GetAmbient()      ,
                       pIGL_Light->GetSpecular()     ,
                       pIGL_Light->GetExpoent()      ,
                       pIGL_Light->GetCutOff()       ,
                       pIGL_Light->GetConstantAtt()  ,
                       pIGL_Light->GetLinearAtt()    ,
                       pIGL_Light->GetQuadraticAtt());
           }break;
           default:{}break;
         }
        return true;
    }
    return false;
}

bool INSGL::PrepareCamera(CIGLCamera *pIGL_Camera)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Camera->GetName(),IdDuplicado,IGL_LIST_TYPE_CAMERAS) )
    {
        switch(pIGL_Camera->GetProjection())
        {
           case IGL_PROJECTION_PERSP:
           {
              execGL(IGL_SH_PERSPECTIVE,IGL_CurrentPgmId,
                                        pIGL_Camera->GetNear(),
                                        pIGL_Camera->GetFar(),
                                        pIGL_Camera->GetHeight(),
                                        pIGL_Camera->GetWidth(),
                                        pIGL_Camera->GetFOV());

              execGL(IGL_SH_LOOKAT,IGL_CurrentPgmId,pIGL_Camera->GetPos(),pIGL_Camera->GetView(),pIGL_Camera->GetUp());
              pIGL_Camera->CalcTime();
           }break;
           case IGL_PROJECTION_ORTHO:
           {
              execGL(IGL_SH_ORTHO,IGL_CurrentPgmId,
                                  pIGL_Camera->GetNear(),
                                  pIGL_Camera->GetFar(),
                                  pIGL_Camera->GetHeight(),
                                  pIGL_Camera->GetWidth(),
                                  pIGL_Camera->GetFOV());
              execGL(IGL_SH_LOOKAT,IGL_CurrentPgmId,pIGL_Camera->GetPos(),pIGL_Camera->GetView(),pIGL_Camera->GetUp());
              pIGL_Camera->CalcTime();
           }break;
           default:
           {
              qWarning() << "Perspectiva de camera invalida!";
           }
        }
        return true;
    }
    return false;
}

bool INSGL::Prepare3DObject(CIMT3DObject *pIGL_Object,uint pIGLShading,uint pIGLGeometry)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(pIGL_Object->GetName(),IdDuplicado,IGL_LIST_TYPE_OBJECTS) )
    {
        //Pop the Object´s Transformation from the Queue.
        bool        tIMT_UseRef;
        uint        tIMT_TransfType;
        CIMTVector  tIMT_Amount,
                    tIMT_Reference;

        if(pIGL_Object->PopTransformation(tIMT_TransfType,
                                          tIMT_UseRef,
                                          tIMT_Amount,
                                          tIMT_Reference))
        {
           switch(tIMT_TransfType)
           {
           case 0:
           {
               if(tIMT_UseRef)
               {
                  pIGL_Object->IMT_Pos += tIMT_Amount;
               }
               else
               {
                  pIGL_Object->IMT_Pos  = tIMT_Amount;
               }

           }break;
           case 1:
           {
               pIGL_Object->IMT_Rot += tIMT_Amount;
               /*************************************/
               /*Verificamos se chegamos a 360 graus*/
               /*Somente acontece com Dinamico      */
               /*************************************/
               if(fabs(pIGL_Object->IMT_Rot.x)==360.0f){pIGL_Object->IMT_Rot.x=0.0f;}
               if(fabs(pIGL_Object->IMT_Rot.y)==360.0f){pIGL_Object->IMT_Rot.y=0.0f;}
               if(fabs(pIGL_Object->IMT_Rot.z)==360.0f){pIGL_Object->IMT_Rot.z=0.0f;}

               if(!tIMT_UseRef)
               {
                  pIGL_Object->IMT_RefRot = pIGL_Object->IMT_Pos;
               }
               else
               {
                  pIGL_Object->IMT_RefRot = tIMT_Reference;
               }

               //pIGL_Object->IMT_MtxTransf.RotateAxis(pIGL_Object->IMT_Pos,DEG2RAD(pIGL_Object->IMT_Rot.y),true);


           }break;
           case 2:
           {
               if(!tIMT_UseRef)
               {
                  pIGL_Object->IMT_Scl    = tIMT_Amount;
                  pIGL_Object->IMT_RefScl = pIGL_Object->IMT_Pos;
               }
               else
               {
                  pIGL_Object->IMT_Scl    = tIMT_Amount;
                  pIGL_Object->IMT_RefScl = tIMT_Reference;
               }

           }break;
           }

           //All the 3 operations(Translation,Scale and Rotation) are stored in a single Model Matrix
           //Update the Model Matrix in OpenGL
           pIGL_Object->IMT_MtxTransf.Translate(pIGL_Object->IMT_Pos.x,pIGL_Object->IMT_Pos.y,pIGL_Object->IMT_Pos.z,true);
           pIGL_Object->IMT_MtxTransf.RotateX  (DEG2RAD(pIGL_Object->IMT_Rot.x),pIGL_Object->IMT_RefRot,false);
           pIGL_Object->IMT_MtxTransf.RotateY  (DEG2RAD(pIGL_Object->IMT_Rot.y),pIGL_Object->IMT_RefRot,false);
           pIGL_Object->IMT_MtxTransf.RotateZ  (DEG2RAD(pIGL_Object->IMT_Rot.z),pIGL_Object->IMT_RefRot,false);
           pIGL_Object->IMT_MtxTransf.Scale(pIGL_Object->IMT_Scl.x,pIGL_Object->IMT_Scl.y,pIGL_Object->IMT_Scl.z,pIGL_Object->IMT_RefScl,false);

           //Update the Model Matrix in OpenGL
           GLSetModelMatrix(pIGL_Object->IMT_MtxTransf);
        }
        else
        {
           //Update the Model Matrix in OpenGL
           pIGL_Object->IMT_MtxTransf.Translate(pIGL_Object->IMT_Pos.x,pIGL_Object->IMT_Pos.y,pIGL_Object->IMT_Pos.z,true);
           pIGL_Object->IMT_MtxTransf.RotateX  (DEG2RAD(pIGL_Object->IMT_Rot.x),pIGL_Object->IMT_RefRot,false);
           pIGL_Object->IMT_MtxTransf.RotateY  (DEG2RAD(pIGL_Object->IMT_Rot.y),pIGL_Object->IMT_RefRot,false);
           pIGL_Object->IMT_MtxTransf.RotateZ  (DEG2RAD(pIGL_Object->IMT_Rot.z),pIGL_Object->IMT_RefRot,false);
           pIGL_Object->IMT_MtxTransf.Scale(pIGL_Object->IMT_Scl.x,pIGL_Object->IMT_Scl.y,pIGL_Object->IMT_Scl.z,pIGL_Object->IMT_RefScl,false);
           GLSetModelMatrix(pIGL_Object->IMT_MtxTransf);
        }



        switch(pIGLShading)
        {
           case IGL_SHADING_MODE_FLAT  : {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",0);}break;
           case IGL_SHADING_MODE_SMOOTH: {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",1);}break;
           case IGL_SHADING_MODE_DIFLAT: {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",2);}break;
           case IGL_SHADING_MODE_DIFOTH: {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",3);}break;
           case IGL_SHADING_MODE_NOONE : {execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",4);}break;
           default:{execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"modo_iluminacao",0);}break;
        }

        PrepareMaterial(pIGL_Object->IMT_Materials[0]);
        PrepareTexture (pIGL_Object->IMT_Textures [0]);

        if(pIGL_Object->IMT_Geometry.IMT_Type == IMT_MESH_TYPE_FACETED)
        {
            for(uint j=0;j<pIGL_Object->IMT_Geometry.IMT_Faces.size();j++)
            {
                GLDrawBuffer(pIGLGeometry                                                                 ,
                             pIGL_Object->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.GetSize()            ,
                             pIGL_Object->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.GetIndexSize()       ,
                             IGL_CurrentPgmId                                                             ,
                             pIGL_Object->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.IMT_VboIds,false,NULL);
            }
        }
        else
        {
            GLDrawBuffer(pIGLGeometry                    ,
                         pIGL_Object->IMT_Geometry.IMT_VertexBuffer.GetSize(),
                         pIGL_Object->IMT_Geometry.IMT_VertexBuffer.GetIndexSize(),
                         IGL_CurrentPgmId,
                         pIGL_Object->IMT_Geometry.IMT_VertexBuffer.IMT_VboIds,false,NULL);
        }

        return true;
    }
    return false;
}

bool INSGL::PrepareMaterial(uint pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(IGL_Materials[pIGLIndex]->GetName(),IdDuplicado,IGL_LIST_TYPE_MATERIALS) )
    {
        if(IGL_Materials[pIGLIndex]->GetMode() == IGL_MATERIAL_REFLEXIVE)IGL_Materials[pIGLIndex]->SetReflection(0.85f);
        if(IGL_Materials[pIGLIndex]->GetMode() == IGL_MATERIAL_REFRATIVE)IGL_Materials[pIGLIndex]->SetRefraction(0.1f);

        execGL(IGL_SH_MATERIAL,IGL_CurrentPgmId,
                               IGL_Materials[pIGLIndex]->GetDiffuse()   ,
                               IGL_Materials[pIGLIndex]->GetAmbient()   ,
                               IGL_Materials[pIGLIndex]->GetEmissive()  ,
                               IGL_Materials[pIGLIndex]->GetSpecular()  ,
                               IGL_Materials[pIGLIndex]->GetAlpha()     ,
                               IGL_Materials[pIGLIndex]->GetRejection() ,
                               IGL_Materials[pIGLIndex]->GetOpacy()     ,
                               IGL_Materials[pIGLIndex]->GetShininess() ,
                               IGL_Materials[pIGLIndex]->GetReflection(),
                               IGL_Materials[pIGLIndex]->GetRefraction());

        switch(IGL_Materials[pIGLIndex]->GetMode())
        {
           case IGL_MATERIAL_COLOR:
           {
              SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_COLOR);
           }break;
           case IGL_MATERIAL_TEXTURE:
           {
              SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_TEXTURE);
              //PrepareTexture(IGL_Materials[pIGLIndex]->GetTexture());
           }break;
           case IGL_MATERIAL_MIXED:
           {
               SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_MIXED);
               //PrepareTexture(IGL_Materials[pIGLIndex]->GetTexture());

           }break;
           case IGL_MATERIAL_NORMALMAP:
           {
              SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_NORMALMAP);
              //PrepareTexture(IGL_Materials[pIGLIndex]->GetTexture());

           }break;
           case IGL_MATERIAL_REFLEXIVE:
           {
              SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_REFLEXIVE);
              //PrepareTexture(IGL_Materials[pIGLIndex]->GetTexture());

           }break;
           case IGL_MATERIAL_REFRATIVE:
           {
              SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_REFRATIVE);
              //PrepareTexture(IGL_Materials[pIGLIndex]->GetTexture());

           }break;
           case IGL_MATERIAL_CUBEMAP:
           {
              SetMaterialMode(IGL_SH_ENABLE,IGL_MATERIAL_CUBEMAP);
              //PrepareTexture(IGL_Materials[pIGLIndex]->GetTexture());
           }break;
        }
        return true;
    }
    return false;
}

bool INSGL::PrepareTexture (uint pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(IGL_Textures[pIGLIndex]->GetName(),IdDuplicado,IGL_LIST_TYPE_TEXTURES) )
    {
        unsigned int tOpenGLId,tAltura,tLargura,tFormato;

        //Seta Multitextura como verdadeiro
        execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"multitextura",1);

        GLEnable(GL_TEXTURE_2D);
        SetActiveTexture(GL_TEXTURE0);
        execGL(IGL_SH_UNIINT       ,IGL_CurrentPgmId,"textura_base",0);

        //Caso seja um Render to Texture prepara a textura atualizando a imagem
        if(IGL_Textures[pIGLIndex]->IGL_TextureMode==IGL_TEXTURE_RENDER)
        {
            if(IGL_Textures[pIGLIndex]->IGL_Video->GetStatus() != IGL_VIDEO_STATUS_FINISH)
            {
               IGL_Textures[pIGLIndex]->IGL_Video->GetProperties(tAltura,tLargura,tFormato);

               execGL(IGL_TEXTURE_PREP,IGL_Textures[pIGLIndex]->IGL_IdT,IGL_TEXTURE_LINEAR,true ,IGL_Textures[pIGLIndex]->IGL_Video->GetFrame(),tAltura,tLargura,tFormato);
            }
            else
            {
               execGL(IGL_TEXTURE_PREP,IGL_Textures[pIGLIndex]->IGL_IdT,IGL_Textures[pIGLIndex]->IGL_TextureMode,false,NULL,0,0,IGL_Textures[pIGLIndex]->IGL_Format);
            }
        }
        else
        {
            //Prepara a textura normal sem atualizar a imagem
            execGL(IGL_TEXTURE_PREP,IGL_Textures[pIGLIndex]->IGL_IdT,IGL_Textures[pIGLIndex]->IGL_TextureMode,false,NULL,0,0,IGL_Textures[pIGLIndex]->IGL_Format);
        }

        //processa os Layers da textura
        for(uint iLayer=0 ;iLayer < IGL_Textures[pIGLIndex]->IGL_Layers.size(); iLayer++)
        {
            switch(iLayer)
            {
               case 0:
               {
                   GLEnable(GL_TEXTURE_2D);
                   SetActiveTexture(GL_TEXTURE1);
                   execGL(IGL_SH_UNIINT,IGL_CurrentPgmId,"textura_detalhe",1);

                   GetTextureProperties(IGL_Textures[pIGLIndex]->IGL_Layers[iLayer],tOpenGLId,tAltura,tLargura,tFormato);

                   execGL(IGL_TEXTURE_PREP,tOpenGLId,IGL_Textures[pIGLIndex]->IGL_TextureMode,false,NULL,0,0,tFormato);

               }break;
               case 1:
               {
                   GLEnable(GL_TEXTURE_2D);
                   SetActiveTexture(GL_TEXTURE2);
                   execGL(IGL_SH_UNIINT       ,IGL_CurrentPgmId,"textura_normal_map",2);

                   GetTextureProperties(IGL_Textures[pIGLIndex]->IGL_Layers[iLayer],tOpenGLId,tAltura,tLargura,tFormato);

                   execGL(IGL_TEXTURE_PREP,tOpenGLId,IGL_Textures[pIGLIndex]->IGL_TextureMode,false,NULL,0,0,tFormato);
               }break;
               case 2:
               {
                   GLEnable(GL_TEXTURE_2D);
                   SetActiveTexture(GL_TEXTURE3);
                   execGL(IGL_SH_UNIINT       ,IGL_CurrentPgmId,"textura_cube_map",3);

                   GetTextureProperties(IGL_Textures[pIGLIndex]->IGL_Layers[iLayer],tOpenGLId,tAltura,tLargura,tFormato);

                   execGL(IGL_TEXTURE_PREP,tOpenGLId,IGL_Textures[pIGLIndex]->IGL_TextureMode,false,NULL,0,0,tFormato);
               }break;
               case 3:
               {
                   //execGL(IGL_SH_ACTIVETEXTURE,GL_TEXTURE4);
                   //execGL(IGL_SH_UNIINT,"textura_cube_map",3);
                   //pI3DTextureManager->Bind(IGL_Layers[iLayer]);
                   //pI3DTextureManager->SetaWrapMode(IGL_Layers[iLayer],pTextMode);
                }break;
                default:
                {
                   qWarning() << "Atenção! Numero de Layers em Textura excedido!.";
                }break;
             }
         }
        return true;
    }
    return false;
}
bool INSGL::PrepareLight(uint pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(IGL_Lights[pIGLIndex]->GetName(),IdDuplicado,IGL_LIST_TYPE_LIGHTS) )
    {
        switch(IGL_Lights[pIGLIndex]->GetType())
        {
           case LIGHTTYPE_POINT:
           {
            execGL(IGL_SH_LIGHT_POINT                ,
                       IGL_CurrentPgmId             ,
                       (GLenum)IdDuplicado           ,
                       IGL_Lights[pIGLIndex]->GetPos()          ,
                       IGL_Lights[pIGLIndex]->GetDir()          ,
                       IGL_Lights[pIGLIndex]->GetDiffuse()      ,
                       IGL_Lights[pIGLIndex]->GetAmbient()      ,
                       IGL_Lights[pIGLIndex]->GetSpecular()     ,
                       IGL_Lights[pIGLIndex]->GetExpoent()      ,
                       IGL_Lights[pIGLIndex]->GetCutOff()       ,
                       IGL_Lights[pIGLIndex]->GetConstantAtt()  ,
                       IGL_Lights[pIGLIndex]->GetLinearAtt()    ,
                       IGL_Lights[pIGLIndex]->GetQuadraticAtt());
           }break;
           case LIGHTTYPE_SPOT:
           {
            execGL(IGL_SH_LIGHT_SPOT                ,
                       IGL_CurrentPgmId             ,
                       (GLenum)IdDuplicado           ,
                       IGL_Lights[pIGLIndex]->GetPos()          ,
                       IGL_Lights[pIGLIndex]->GetDir()          ,
                       IGL_Lights[pIGLIndex]->GetDiffuse()      ,
                       IGL_Lights[pIGLIndex]->GetAmbient()      ,
                       IGL_Lights[pIGLIndex]->GetSpecular()     ,
                       IGL_Lights[pIGLIndex]->GetExpoent()      ,
                       IGL_Lights[pIGLIndex]->GetCutOff()       ,
                       IGL_Lights[pIGLIndex]->GetConstantAtt()  ,
                       IGL_Lights[pIGLIndex]->GetLinearAtt()    ,
                       IGL_Lights[pIGLIndex]->GetQuadraticAtt());
           }break;
           case LIGHTTYPE_DIRECTIONAL:
           {
            execGL(IGL_SH_LIGHT_DIRECTIONAL          ,
                       IGL_CurrentPgmId             ,
                       (GLenum)IdDuplicado           ,
                       IGL_Lights[pIGLIndex]->GetPos()          ,
                       IGL_Lights[pIGLIndex]->GetDir()          ,
                       IGL_Lights[pIGLIndex]->GetDiffuse()      ,
                       IGL_Lights[pIGLIndex]->GetAmbient()      ,
                       IGL_Lights[pIGLIndex]->GetSpecular()     ,
                       IGL_Lights[pIGLIndex]->GetExpoent()      ,
                       IGL_Lights[pIGLIndex]->GetCutOff()       ,
                       IGL_Lights[pIGLIndex]->GetConstantAtt()  ,
                       IGL_Lights[pIGLIndex]->GetLinearAtt()    ,
                       IGL_Lights[pIGLIndex]->GetQuadraticAtt());
           }break;
           default:{}break;
         }
        return true;
    }
    return false;
}


bool INSGL::PrepareCamera(uint pIGLIndex)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(IGL_Cameras[pIGLIndex]->GetName(),IdDuplicado,IGL_LIST_TYPE_CAMERAS) )
    {
        switch(IGL_Cameras[pIGLIndex]->GetProjection())
        {
           case IGL_PROJECTION_PERSP:
           {
              execGL(IGL_SH_PERSPECTIVE,IGL_CurrentPgmId,
                                        IGL_Cameras[pIGLIndex]->GetNear(),
                                        IGL_Cameras[pIGLIndex]->GetFar(),
                                        IGL_Cameras[pIGLIndex]->GetHeight(),
                                        IGL_Cameras[pIGLIndex]->GetWidth(),
                                        IGL_Cameras[pIGLIndex]->GetFOV());

              execGL(IGL_SH_LOOKAT,IGL_CurrentPgmId,IGL_Cameras[pIGLIndex]->GetPos(),IGL_Cameras[pIGLIndex]->GetView(),IGL_Cameras[pIGLIndex]->GetUp());
           }break;
           case IGL_PROJECTION_ORTHO:
           {
              execGL(IGL_SH_ORTHO,IGL_CurrentPgmId,
                                  IGL_Cameras[pIGLIndex]->GetNear(),
                                  IGL_Cameras[pIGLIndex]->GetFar(),
                                  IGL_Cameras[pIGLIndex]->GetHeight(),
                                  IGL_Cameras[pIGLIndex]->GetWidth(),
                                  IGL_Cameras[pIGLIndex]->GetFOV());
              execGL(IGL_SH_LOOKAT,IGL_CurrentPgmId,IGL_Cameras[pIGLIndex]->GetPos(),IGL_Cameras[pIGLIndex]->GetView(),IGL_Cameras[pIGLIndex]->GetUp());
           }break;
           default:
           {
              qWarning() << "Perspectiva de camera invalida!";
           }
        }
        return true;
    }
    return false;
}

bool INSGL::Prepare3DObject(uint pIGLIndex,uint pIGLShading,uint pIGLGeometry)
{
    int            IdDuplicado= 0   ;
    //Inserir aqui checagem de duplicado
    if ( CheckDuplicated(IGL_Objects[pIGLIndex]->GetName(),IdDuplicado,IGL_LIST_TYPE_OBJECTS) )
    {
        //Atualiza a Matriz Model na OpenGL
        GLSetModelMatrix(IGL_Objects[pIGLIndex]->IMT_MtxTransf);

        GLSetShadingMode(pIGLShading);

        if(IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_Type == IMT_MESH_TYPE_FACETED)
        {
            for(uint j=0;j<IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_Faces.size();j++)
            {
                GLDrawBuffer(pIGLGeometry                                                                 ,
                             IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.GetSize()            ,
                             IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.GetIndexSize()       ,
                             IGL_CurrentPgmId                                                             ,
                             IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.IMT_VboIds,false,NULL);
            }
        }
        else
        {
            GLDrawBuffer(pIGLGeometry                    ,
                         IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_VertexBuffer.GetSize(),
                         IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_VertexBuffer.GetIndexSize(),
                         IGL_CurrentPgmId,
                         IGL_Objects[pIGLIndex]->IMT_Geometry.IMT_VertexBuffer.IMT_VboIds,false,NULL);
        }
        return true;
    }
    return false;
}

bool INSGL::SingleShotHWTextures()
{
    for(int i=0;i<IGL_TexCounter;i++)
    {
        if(IGL_Textures[i]->IGL_TextureMode != IGL_TEXTURE_CUBEMAP)
        {
            GLEnable(GL_TEXTURE_2D);
            GLCreateSingleTexture(IGL_Textures[i]->IGL_IdT                      ,
                                  IGL_Textures[i]->IGL_Image->IMT_GridData.ptr(),
                                  IGL_Textures[i]->IGL_Height                   ,
                                  IGL_Textures[i]->IGL_Width                    ,
                                  IGL_Textures[i]->IGL_Format                   ,
                                  1                                             );
        }
        else
        {
            GLEnable(GL_TEXTURE_CUBE_MAP);
            GLCreateCubeMap(IGL_Textures[i]->IGL_IdT                            ,
                            IGL_Textures[i]->IGL_ImageRight->IMT_GridData.ptr() ,
                            IGL_Textures[i]->IGL_ImageLeft->IMT_GridData.ptr()  ,
                            IGL_Textures[i]->IGL_ImageTop->IMT_GridData.ptr()   ,
                            IGL_Textures[i]->IGL_ImageBottom->IMT_GridData.ptr(),
                            IGL_Textures[i]->IGL_ImageBack->IMT_GridData.ptr()  ,
                            IGL_Textures[i]->IGL_ImageFront->IMT_GridData.ptr() ,
                            IGL_Textures[i]->IGL_Height                         ,
                            IGL_Textures[i]->IGL_Width                          ,
                            IGL_Textures[i]->IGL_Format                         ,
                            1                                                  );
        }
    }
    return true;
}

bool INSGL::SingleShotHWObjects()
{
    for(int i=0;i<IGL_ObjCounter;i++)
    {

        if(IGL_Objects[i]->IMT_Geometry.IMT_Type == IMT_MESH_TYPE_FACETED)
        {
            for(uint j=0;j<IGL_Objects[i]->IMT_Geometry.IMT_Faces.size();j++)
            {
                GLCreateVertexBuffer(IGL_Objects[i]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.IMT_Buffer    ,
                                     IGL_Objects[i]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.IMT_Indices   ,
                                     IGL_Objects[i]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.GetSize()     ,
                                     IGL_Objects[i]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.GetIndexSize(),
                                     IGL_Objects[i]->IMT_Geometry.IMT_Faces[j].IMT_VertexBuffer.IMT_VboIds    );
            }
        }
        else
        {
            GLCreateVertexBuffer(IGL_Objects[i]->IMT_Geometry.IMT_VertexBuffer.IMT_Buffer    ,
                                 IGL_Objects[i]->IMT_Geometry.IMT_VertexBuffer.IMT_Indices   ,
                                 IGL_Objects[i]->IMT_Geometry.IMT_VertexBuffer.GetSize()     ,
                                 IGL_Objects[i]->IMT_Geometry.IMT_VertexBuffer.GetIndexSize(),
                                 IGL_Objects[i]->IMT_Geometry.IMT_VertexBuffer.IMT_VboIds    );
        }

    }
    return true;
}

void INSGL::RenderScene()
{
    GLEnableStates();
    SetFrontFace(IGL_SH_ENABLE,IGL_WINMODE_CCW);

    PrepareCamera(IGL_Cameras[0]);

    for(int i=0;i<IGL_LgtCounter;i++)
    {
        PrepareLight(IGL_Lights[i]);
    }

    for(int i=0;i<IGL_ObjCounter;i++)
    {
        switch(IGL_Objects[i]->GetType())
        {
        case IMT_OBJECT_TYPE_CUBE   :{Prepare3DObject(IGL_Objects[i],IGL_SHADING_MODE_FLAT,IGL_RENDER_TRIANGLES);}break;
        case IMT_OBJECT_TYPE_SKY    :{Prepare3DObject(IGL_Objects[i],IGL_SHADING_MODE_FLAT,IGL_RENDER_TRIANGLES);}break;
        case IMT_OBJECT_TYPE_TERRAIN:{Prepare3DObject(IGL_Objects[i],IGL_SHADING_MODE_FLAT,IGL_RENDER_TRIANGLE_STRIP);}break;
        }


    }

    GLDisableStates();
}

void INSGL::PaintSplash(QPainter *painter, QPaintEvent *event, float TimeElapsed)
{
    IGL_Splash->paint(painter,event,TimeElapsed);
}
