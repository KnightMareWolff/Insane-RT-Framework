#include "IGL_Functions.h"

//Valor estatico para verificar se o contexto já foi criado
bool CIGLFunctions::bIGLContextoInicializado = false;

CIGLFunctions::CIGLFunctions()
{

    tf_varyings = new char*;
    tf_varyings[0] = new char[10];
    strcpy(tf_varyings[0],"f_position");

}


bool CIGLFunctions::iglEnableStates()
{
    return true;
}

bool CIGLFunctions::iglDisableStates()
{
    return true;
}

bool CIGLFunctions::iglActiveTexture(unsigned int estado)
{
    Q_UNUSED(estado);
    return true;
}


bool CIGLFunctions::iglEnable(unsigned int estado)
{
    Q_UNUSED(estado);
    return true;
}

bool CIGLFunctions::iglDisable(unsigned int estado)
{
    Q_UNUSED(estado);
    return true;
}

bool CIGLFunctions::iglDeleteTextures(int vlr, GLuint *Id)
{
    Q_UNUSED(vlr);
    Q_UNUSED(Id);
    return true;
}

bool CIGLFunctions::iglDeleteBuffers(int vlr, GLuint *Id)
{
    Q_UNUSED(vlr);
    Q_UNUSED(Id);
    return true;
}

bool CIGLFunctions::iglRenderBuffers(int            vlr           ,
                                     long           QtdVertices   ,
                                     long           QtdIndices    ,
                                     GLuint         ProgramId,
                                     GLuint        *Id            ,
                                     bool           FeedBack      ,
                                     FeedBackData  *FeedbackBuffer)
{
    Q_UNUSED(vlr);
    Q_UNUSED(QtdVertices);
    Q_UNUSED(QtdIndices);
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(FeedBack);
    Q_UNUSED(FeedbackBuffer);
    return true;
}


bool CIGLFunctions::iglSetMaterial(GLuint ProgramId,
                                   CIMTVector4 CorDifusa        ,
                                   CIMTVector4 CorAmbiente      ,
                                   CIMTVector4 CorEmissiva      ,
                                   CIMTVector4 CorSpecular      ,
                                   CIMTVector4 CorAlpha         ,
                                   bool       bRejeitaAlphabits,
                                   float      opacidade        ,
                                   float      brilho           ,
                                   float      reflexao         ,
                                   float      IndiceRefracao   )
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorEmissiva);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(CorAlpha);
    Q_UNUSED(bRejeitaAlphabits);
    Q_UNUSED(opacidade);
    Q_UNUSED(brilho);
    Q_UNUSED(reflexao);
    Q_UNUSED(IndiceRefracao);
    return true;
}

bool CIGLFunctions::iglSetPointLight       (GLuint ProgramId,
                                           unsigned int Id ,
                                           CIMTVector4  pos,
                                           CIMTVector4  dir,
                                           CIMTVector4  CorDifusa,
                                           CIMTVector4  CorAmbiente,
                                           CIMTVector4  CorSpecular,
                                           float        Expoente   ,
                                           float        CutOff     ,
                                           float        AtenuacaoConstante,
                                           float        AtenuacaoLinear   ,
                                           float        AtenuacaoQuadratica)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(pos);
    Q_UNUSED(dir);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(Expoente);
    Q_UNUSED(CutOff);
    Q_UNUSED(AtenuacaoConstante);
    Q_UNUSED(AtenuacaoLinear);
    Q_UNUSED(AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctions::iglSetDirectionalLight  (GLuint ProgramId, unsigned int Id,
                                             CIMTVector4 pos ,
                                             CIMTVector4 dir,
                                             CIMTVector4 CorDifusa,
                                             CIMTVector4 CorAmbiente,
                                             CIMTVector4 CorSpecular,
                                             float Expoente,
                                             float CutOff,
                                             float AtenuacaoConstante,
                                             float AtenuacaoLinear,
                                             float AtenuacaoQuadratica)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(pos);
    Q_UNUSED(dir);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(Expoente);
    Q_UNUSED(CutOff);
    Q_UNUSED(AtenuacaoConstante);
    Q_UNUSED(AtenuacaoLinear);
    Q_UNUSED(AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctions::iglSetSpotLight (GLuint ProgramId, unsigned int Id,
                                     CIMTVector4  pos,
                                     CIMTVector4 dir,
                                     CIMTVector4 CorDifusa,
                                     CIMTVector4 CorAmbiente,
                                     CIMTVector4 CorSpecular,
                                     float Expoente,
                                     float CutOff,
                                     float AtenuacaoConstante,
                                     float AtenuacaoLinear,
                                     float AtenuacaoQuadratica)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Id);
    Q_UNUSED(pos);
    Q_UNUSED(dir);
    Q_UNUSED(CorDifusa);
    Q_UNUSED(CorAmbiente);
    Q_UNUSED(CorSpecular);
    Q_UNUSED(Expoente);
    Q_UNUSED(CutOff);
    Q_UNUSED(AtenuacaoConstante);
    Q_UNUSED(AtenuacaoLinear);
    Q_UNUSED(AtenuacaoQuadratica);
    return true;
}

bool CIGLFunctions::iglSetPerspectiveView(GLuint  ProgramId ,
                                          float ValorProx   ,
                                          float ValorDist   ,
                                          int   ValorAltura ,
                                          int   ValorLargura,
                                          float FOV         )
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(ValorProx);
    Q_UNUSED(ValorDist);
    Q_UNUSED(ValorAltura);
    Q_UNUSED(ValorLargura);
    Q_UNUSED(FOV);
    return true;
}

bool CIGLFunctions::iglSetOrthogonalView(GLuint ProgramId,
                                         float  ValorProx,
                                         float  ValorDist,
                                         int    ValorAltura,
                                         int    ValorLargura)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(ValorProx);
    Q_UNUSED(ValorDist);
    Q_UNUSED(ValorAltura);
    Q_UNUSED(ValorLargura);
    return true;
}

bool CIGLFunctions::iglSetLookAt(GLuint ProgramId, CIMTVector Pos, CIMTVector View, CIMTVector Up)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(Pos);
    Q_UNUSED(View);
    Q_UNUSED(Up);
    return true;
}

bool CIGLFunctions::iglSetUniformInt(GLuint ProgramId, const GLchar *nome, int vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetUniformFloat(GLuint ProgramId, const GLchar *nome, float vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetUniformVec3(GLuint ProgramId, const GLchar *nome, CIMTVector vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetUniformVec4(GLuint ProgramId, const GLchar *nome, CIMTVector4 vlr)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(nome);
    Q_UNUSED(vlr);
    return true;
}

bool CIGLFunctions::iglSetUniformMatrix(GLuint ProgramId, CIMTMatrix mtx)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(mtx);
    return true;
}

bool CIGLFunctions::iglCalPVMMatrix(CIMTMatrix mtx,CIMTMatrix &resmtx)
{
    Q_UNUSED(mtx);
    Q_UNUSED(resmtx);
    return true;
}

bool CIGLFunctions::iglGetPVMMatrix(CIMTMatrix &resmtx)
{
    Q_UNUSED(resmtx);
    return true;
}

bool CIGLFunctions::iglInitBuffers( CIMTVertex        *IGL_VertexBuffer  ,
                                    GLuint            *IGL_VertexIndices ,
                                    long               IGL_QtdVertices   ,
                                    long               IGL_QtdIndices    ,
                                    GLuint             IGL_VboIds[]      )
{
    Q_UNUSED(IGL_VertexBuffer);
    Q_UNUSED(IGL_VertexIndices);
    Q_UNUSED(IGL_QtdVertices);
    Q_UNUSED(IGL_QtdIndices);
    Q_UNUSED(IGL_VboIds);
    return true;
}

bool CIGLFunctions::iglFinish()
{
   return true;
}

bool CIGLFunctions::iglFenceSync(GLsync &pIGL_Sync)
{

   Q_UNUSED(pIGL_Sync);
   return true;
}

bool CIGLFunctions::iglWaitSync(GLsync pIGL_Sync)
{
   Q_UNUSED(pIGL_Sync);
   return true;
}

bool CIGLFunctions::iglColormaterial(GLuint ProgramId, bool bHabilita)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(bHabilita);
    return true;
}

bool CIGLFunctions::iglMaterialMode(GLuint ProgramId, int iMode)
{
    Q_UNUSED(ProgramId);
    Q_UNUSED(iMode);
    return true;
}



bool CIGLFunctions::iglReadPixels(int x,int y,GLchar *res)
{
    Q_UNUSED(x);
    Q_UNUSED(y);
    Q_UNUSED(res);
    return true;
}

bool CIGLFunctions::iglFrontFace(int iMode)
{
    Q_UNUSED(iMode);
    return true;
}

int CIGLFunctions::iglGetVersion()
{
    return 99;
}

bool CIGLFunctions::iglCreateTexture(GLuint        &IGL_TextureId     ,
                                     GLubyte       *IGL_TextureData   ,
                                     GLuint         IGL_TextureWidth  ,
                                     GLuint         IGL_TextureHeight ,
                                     GLuint         IGL_TextureFormat,
                                     GLuint         IGL_TextureMipmaps)
{
    Q_UNUSED(IGL_TextureId);
    Q_UNUSED(IGL_TextureData);
    Q_UNUSED(IGL_TextureWidth);
    Q_UNUSED(IGL_TextureHeight);
    Q_UNUSED(IGL_TextureFormat);
    Q_UNUSED(IGL_TextureMipmaps);
    return true;
}

bool CIGLFunctions::iglCreateCubeMap      (GLuint        &IGL_TextureId     ,
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
    Q_UNUSED(IGL_TextureId);
    Q_UNUSED(IGL_TextureRight);
    Q_UNUSED(IGL_TextureLeft);
    Q_UNUSED(IGL_TextureTop);
    Q_UNUSED(IGL_TextureBottom);
    Q_UNUSED(IGL_TextureBack);
    Q_UNUSED(IGL_TextureFront);
    Q_UNUSED(IGL_TextureWidth);
    Q_UNUSED(IGL_TextureHeight);
    Q_UNUSED(IGL_TextureFormat);
    Q_UNUSED(IGL_TextureMipmaps);
    return true;
}

bool CIGLFunctions::iglPrepareTexture(GLuint     IGL_TextureId     ,
                                      GLuint     IGL_TextureMode   ,
                                      GLboolean  IGL_TextureUpdate ,
                                      GLubyte   *IGL_TextureData   ,
                                      GLuint     IGL_TextureWidth  ,
                                      GLuint     IGL_TextureHeight,
                                      GLuint     IGL_TextureFormat)
{
    Q_UNUSED(IGL_TextureId);
    Q_UNUSED(IGL_TextureMode);
    Q_UNUSED(IGL_TextureUpdate);
    Q_UNUSED(IGL_TextureData);
    Q_UNUSED(IGL_TextureWidth);
    Q_UNUSED(IGL_TextureHeight);
    Q_UNUSED(IGL_TextureFormat);
    return true;
}

bool CIGLFunctions::iglTransformFeedback(GLuint IGL_ProgramId)
{
    Q_UNUSED(IGL_ProgramId);
    return true;
}

bool CIGLFunctions::iglTransformBuffer(GLuint           IGL_VboId    ,
                                       GLuint           IGL_QtdVertices,
                                       CIMTMatrix       IGL_TransfMtx,
                                       CIMTVertex      *IGL_VertexData)
{
    Q_UNUSED(IGL_VboId);
    Q_UNUSED(IGL_QtdVertices);
    Q_UNUSED(IGL_TransfMtx);
    Q_UNUSED(IGL_VertexData);
    return true;
}

CIMTVertex *CIGLFunctions::iglMapBuffer(GLuint IGL_VboId)
{
    Q_UNUSED(IGL_VboId);
    return NULL;
}

bool CIGLFunctions::iglUnMapBuffer()
{
    return true;
}

QString CIGLFunctions::iglGetString(GLuint IGL_StringId)
{
    Q_UNUSED(IGL_StringId);
    return QString("Default String");
}

