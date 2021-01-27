#ifndef CICLSystem_H
#define CICLSystem_H

#include "INSCL_global.h"
#include "ICL_Platform.h"

class INSCL_EXPORT CICLSystem
{
public:
    CICLSystem(                        );
    CICLSystem(QOpenGLContext *pContext,QString pICL_DefaultGPUVendor);
    CICLSystem(QGLContext     *pContext,QString pICL_DefaultGPUVendor);

    // ---- Operações em Hardware ----
    void UpdateHardwareDevices();
    void TransformBufferGL(CIMTVertexBuffer *pICL_Buffer  ,uint pICL_BufferSize,CIMTMatrix *pICL_Transform);
    void TransformBufferGL(uint              pICL_BufferId,uint pICL_BufferSize,CIMTMatrix *pICL_Transform);

    // ---- Operações Auxiliares
    void ExtraiIndicadores(bool &pICL_InteropComputing,bool &pICL_HeterogComputing,bool &pICL_AuxiliaryComputing);

private:
    QWGLNativeContext ICL_ContextoGLNativo;

    //atributos para OpenGL
    HGLRC ICL_GLRC;//Contexto Nativo OpenGL.
    HDC   ICL_HDC ;//Contexto Nativo do Device Driver.
    HWND  ICL_HWND;//Handle Nativo da Tela de Renderização

    //atributos para OpenCL
    cl_platform_id*         ICL_ListaID;
    cl_uint                 ICL_QtdPlataformas;
    vector<CICLPlatform*>   ICL_Plataformas;

    //atributos de Interoperação CL/GL
    QString                 ICL_DefaultGPUVendor;
    bool                    ICL_InteropComputing;
    bool                    ICL_HeterogComputing;
    bool                    ICL_AuxiliaryComputing;

    //atributos de contagem para montagem de profile
    int                     ICL_CPUCounter;
    int                     ICL_GPUCounter;
    int                     ICL_ACECounter;

    //indices de cada plataforma para acesso direto de acordo com logica de processamento
    int                     ICL_GraphicsPlat;//Plataforma Grafica/Interop(GPU Primária)
    int                     ICL_Heterogeneus;//Plataforma Computação Heterogênea(GPU Secundaria)
    int                     ICL_Auxiliary   ;//Plataforma Auxiliar(CPU)

    //  ---- Operações Privadas ----
    void ExtraiContadores();//Conta o Numero de Devices disponiveis
    void ExtraiIndices   ();//Coleta os indices de plataforma disponiveis
};

#endif // CICLSystem_H
