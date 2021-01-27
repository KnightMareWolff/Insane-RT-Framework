#ifndef IGL_FUNCTIONS_H
#define IGL_FUNCTIONS_H

#include "INSGL_global.h"

class CIGLFunctions
{
public:
    CIGLFunctions();

    virtual bool iglEnableStates       ();
    virtual bool iglDisableStates      ();
    virtual bool iglFinish             ();
    virtual bool iglFenceSync          (GLsync &pIGL_Sync);
    virtual bool iglWaitSync           (GLsync  pIGL_Sync);
    virtual bool iglActiveTexture      (unsigned int estado);
    virtual bool iglEnable             (unsigned int estado);
    virtual bool iglDisable            (unsigned int estado);
    virtual bool iglDeleteTextures     (int vlr, GLuint *Id);
    virtual bool iglDeleteBuffers      (int vlr, GLuint *Id);

    virtual bool iglRenderBuffers      (int           vlr,
                                        long          QtdVertices,
                                        long          QtdIndices,
                                        GLuint        ProgramId ,
                                        GLuint       *Id,
                                        bool          FeedBack,
                                        FeedBackData *FeedbackBuffer);

    virtual bool iglSetMaterial        (GLuint ProgramId,
                                        CIMTVector4 CorDifusa        ,
                                        CIMTVector4 CorAmbiente      ,
                                        CIMTVector4 CorEmissiva      ,
                                        CIMTVector4 CorSpecular      ,
                                        CIMTVector4 CorAlpha         ,
                                        bool       bRejeitaAlphabits,
                                        float      opacidade        ,
                                        float      brilho           ,
                                        float      reflexao         ,
                                        float      IndiceRefracao);

    virtual bool iglSetPointLight      (GLuint ProgramId,
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
                                        float         AtenuacaoQuadratica);

    virtual bool iglSetDirectionalLight(GLuint ProgramId,
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
                                        float         AtenuacaoQuadratica);

    virtual bool iglSetSpotLight       (GLuint ProgramId,
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
                                        float         AtenuacaoQuadratica);

    virtual bool iglSetPerspectiveView (GLuint  ProgramId ,
                                        float ValorProx,
                                        float ValorDist,
                                        int   ValorAltura,
                                        int   ValorLargura,
                                        float FOV);
    virtual bool iglSetOrthogonalView  (GLuint  ProgramId ,
                                        float ValorProx,
                                        float ValorDist,
                                        int   ValorAltura,
                                        int   ValorLargura);

    virtual bool iglSetLookAt          (GLuint  ProgramId ,CIMTVector Pos,CIMTVector View,CIMTVector Up);

    virtual bool iglSetUniformInt      (GLuint  ProgramId ,const GLchar *nome,int        vlr);
    virtual bool iglSetUniformFloat    (GLuint  ProgramId ,const GLchar *nome,float      vlr);
    virtual bool iglSetUniformVec3     (GLuint  ProgramId ,const GLchar *nome,CIMTVector  vlr);
    virtual bool iglSetUniformVec4     (GLuint  ProgramId ,const GLchar *nome,CIMTVector4 vlr);
    virtual bool iglSetUniformMatrix   (GLuint  ProgramId ,CIMTMatrix mtx);

    virtual bool iglCalPVMMatrix       (CIMTMatrix mtx,CIMTMatrix &resmtx);
    virtual bool iglGetPVMMatrix       (CIMTMatrix &resmtx               );

    virtual bool iglInitBuffers        (CIMTVertex        *IGL_VertexBuffer   ,
                                        GLuint            *IGL_VertexIndices  ,
                                        long               IGL_QtdVertices    ,
                                        long               IGL_QtdIndices     ,
                                        GLuint             IGL_VboIds[3]      );

    virtual bool iglColormaterial      (GLuint ProgramId, bool bHabilita);
    virtual bool iglMaterialMode       (GLuint ProgramId, int  iMode    );
    virtual bool iglReadPixels         (int x,int y,  GLchar *res    );
    virtual bool iglFrontFace          (int           iMode          );
    virtual int  iglGetVersion         (                             );

    virtual bool iglCreateTexture      (GLuint        &IGL_TextureId     ,
                                        GLubyte       *IGL_TextureData   ,
                                        GLuint         IGL_TextureWidth  ,
                                        GLuint         IGL_TextureHeight ,
                                        GLuint         IGL_TextureFormat ,
                                        GLuint         IGL_TextureMipmaps);
    virtual bool iglCreateCubeMap      (GLuint        &IGL_TextureId     ,
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

    virtual bool iglPrepareTexture     (GLuint         IGL_TextureId     ,
                                        GLuint         IGL_TextureMode   ,
                                        GLboolean      IGL_TextureUpdate ,
                                        GLubyte       *IGL_TextureData   ,
                                        GLuint         IGL_TextureWidth  ,
                                        GLuint         IGL_TextureHeight ,
                                        GLuint         IGL_TextureFormat);

    virtual bool iglTransformFeedback  (GLuint         IGL_ProgramId);

    virtual bool iglTransformBuffer    (GLuint           IGL_VboId      ,
                                        GLuint           IGL_QtdVertices,
                                        CIMTMatrix       IGL_TransfMtx  ,
                                        CIMTVertex      *IGL_VertexData);

    virtual CIMTVertex * iglMapBuffer  (GLuint           IGL_VboId      );
    virtual bool         iglUnMapBuffer(                                );
    virtual QString      iglGetString  (GLuint           IGL_StringId   );

protected:

    int  iIGLVersion       ,
         iIGLMinorVersion  ,
         iIGLMajorVersion  ,
         iIGLPlatform      ;

    static bool bIGLContextoInicializado;

    char **tf_varyings;

    CIMTMatrix mIGLViewMatrix;
    CIMTMatrix mIGLProjectionMatrix;
    CIMTMatrix mIGLPVMMatrix;
};

#endif // IGL_FUNCTIONS_H
