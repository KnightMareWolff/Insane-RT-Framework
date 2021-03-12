/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CICLSystem_H
#define CICLSystem_H

#include "INSCL_global.h"
#include "ICL_Platform.h"

class INSCL_EXPORT CICLSystem
{
public:
    CICLSystem(                        );
    CICLSystem(QOpenGLContext *pContext,QString pICL_DefaultGPUVendor);

    // ---- Operações em Hardware ----
    void UpdateHardwareDevices();
    void TransformBufferGL(CIMTVertexBuffer *pICL_Buffer  ,uint pICL_BufferSize,CIMTMatrix *pICL_Transform);
    void TransformBufferGL(uint              pICL_BufferId,uint pICL_BufferSize,CIMTMatrix *pICL_Transform);

    // ---- Operações Auxiliares
    void ExtraiIndicadores(bool &pICL_InteropComputing,bool &pICL_HeterogComputing,bool &pICL_AuxiliaryComputing);

private:
    QWGLNativeContext ICL_ContextoGLNativo;//Native Context of the Surface
    QOffscreenSurface *pGLOffScreen;//For the Cases we need update OpenGL Data in a Offscreen Context
    QOpenGLContext    *pGLContext  ;
    QSurfaceFormat     pGLFormat   ;

    //atributos para OpenGL
    HGLRC ICL_GLRC;//Native OpenGL.
    HDC   ICL_HDC ;//Windows Context Native Device Driver.
    HWND  ICL_HWND;//Handle Native Screen

    //OpenCL Attributes
    cl_platform_id*         ICL_ListaID;
    cl_uint                 ICL_QtdPlataformas;
    vector<CICLPlatform*>   ICL_Plataformas;

    //Interoperation CL/GL
    QString                 ICL_DefaultGPUVendor;
    bool                    ICL_InteropComputing;
    bool                    ICL_HeterogComputing;
    bool                    ICL_AuxiliaryComputing;

    //Counters
    int                     ICL_CPUCounter;
    int                     ICL_GPUCounter;
    int                     ICL_ACECounter;

    //Platform Indicators
    int                     ICL_GraphicsPlat;//Platform Graphics/Interop(GPU Primary)
    int                     ICL_Heterogeneus;//Platform for Heterogêneus Computing(GPU Secundary)
    int                     ICL_Auxiliary   ;//Platform Auxiliary(CPU)

    //  ---- Operações Privadas ----
    void ExtraiContadores();//Conta o Numero de Devices disponiveis
    void ExtraiIndices   ();//Coleta os indices de plataforma disponiveis
};

#endif // CICLSystem_H
