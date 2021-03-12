/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "ICL_System.h"

CICLSystem::CICLSystem()
{
    cl_int  ICL_Error;

    //Zera os contadores do sistema heterogêneo.
    ICL_CPUCounter = 0;
    ICL_GPUCounter = 0;
    ICL_ACECounter = 0;

    //Inicializa Flags de Computação Heterogênea
    ICL_InteropComputing  = false;
    ICL_HeterogComputing  = false;
    ICL_AuxiliaryComputing= false;

    //Creates an Offscreen OpenGL Context, since we not receive any context to be used...
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

    //Coleta Qual é o Contexto OpenGL Nativo do sistema
    QVariant nativeHandle = pGLContext->nativeHandle();

    if (!nativeHandle.isNull() && nativeHandle.canConvert<QWGLNativeContext>())
    {
        ICL_ContextoGLNativo = nativeHandle.value<QWGLNativeContext>();

        //ICL_GLRC             = ICL_ContextoGLNativo.context();
        ICL_GLRC             = wglGetCurrentContext();

        ICL_HWND             = ICL_ContextoGLNativo.window ();

        //ICL_HDC              = GetDC(ICL_HWND);
        ICL_HDC              = wglGetCurrentDC();
    }


    //Pega o Numero de Plataformas disponiveis
    ICL_Error = clGetPlatformIDs(0, NULL, &ICL_QtdPlataformas);
    if(ICL_Error != CL_SUCCESS)
    {
       qWarning() << "Não foi possivel Obter Nenhuma Plataforma Heterogenea.";
       exit(1);
    }

    //aloca o numero necessario de platform ids
    ICL_ListaID = new cl_platform_id[ICL_QtdPlataformas];

    //Pega os ID´s de das plataformas
    ICL_Error = clGetPlatformIDs(ICL_QtdPlataformas, ICL_ListaID , NULL);
    if(ICL_Error != CL_SUCCESS)
    {
       qWarning() << "Não foi possivel Obter Os Ids de Plataforma Heterogenea.";
       exit(1);
    }

    //Inicializa a lista de Plataformas do sistema construindo a partir do ID da Plataforma
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        ICL_Plataformas.push_back(new CICLPlatform(ICL_ListaID[i],ICL_DefaultGPUVendor));
    }

    ExtraiContadores();
    ExtraiIndices   ();

    qWarning() << "Plataforma Heterogênea Criada.";
    qWarning() << "Contadores:";
    qWarning() << "GPU´s detectadas:" << ICL_GPUCounter ;
    qWarning() << "CPU´s detectadas:" << ICL_GPUCounter ;
    qWarning() << "ACE´s detectadas:" << ICL_ACECounter ;
    qWarning() << "=================";
    qWarning() << "Indice Graphics     :" << ICL_GraphicsPlat ;
    qWarning() << "Indice Heterogeneous:" << ICL_Heterogeneus ;
    qWarning() << "Indice Auxiliary    :" << ICL_Auxiliary ;
}

CICLSystem::CICLSystem(QOpenGLContext *pContext,QString pICL_DefaultGPUVendor)
{
    cl_int  ICL_Error;

    //Repassa qual é o Vendor da GPU Default do sistema
    ICL_DefaultGPUVendor = pICL_DefaultGPUVendor;

    //Zera os contadores do sistema heterogêneo.
    ICL_CPUCounter = 0;
    ICL_GPUCounter = 0;
    ICL_ACECounter = 0;

    //Inicializa Flags de Computação Heterogênea
    ICL_InteropComputing  = false;
    ICL_HeterogComputing  = false;
    ICL_AuxiliaryComputing= false;

    //Coleta Qual é o Contexto OpenGL Nativo do sistema
    QVariant nativeHandle = pContext->nativeHandle();

    if (!nativeHandle.isNull() && nativeHandle.canConvert<QWGLNativeContext>())
    {
        ICL_ContextoGLNativo = nativeHandle.value<QWGLNativeContext>();

        //ICL_GLRC             = ICL_ContextoGLNativo.context();
        ICL_GLRC             = wglGetCurrentContext();

        ICL_HWND             = ICL_ContextoGLNativo.window ();

        //ICL_HDC              = GetDC(ICL_HWND);
        ICL_HDC              = wglGetCurrentDC();
    }


    //Pega o Numero de Plataformas disponiveis
    ICL_Error = clGetPlatformIDs(0, NULL, &ICL_QtdPlataformas);
    if(ICL_Error != CL_SUCCESS)
    {
       qWarning() << "Não foi possivel Obter Nenhuma Plataforma Heterogenea.";
       exit(1);
    }

    //aloca o numero necessario de platform ids
    ICL_ListaID = new cl_platform_id[ICL_QtdPlataformas];

    //Pega os ID´s de das plataformas
    ICL_Error = clGetPlatformIDs(ICL_QtdPlataformas, ICL_ListaID , NULL);
    if(ICL_Error != CL_SUCCESS)
    {
       qWarning() << "Não foi possivel Obter Os Ids de Plataforma Heterogenea.";
       exit(1);
    }

    //Inicializa a lista de Plataformas do sistema construindo a partir do ID da Plataforma
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        ICL_Plataformas.push_back(new CICLPlatform(ICL_ListaID[i],ICL_DefaultGPUVendor));
    }

    ExtraiContadores();
    ExtraiIndices   ();

    qWarning() << "Plataforma Heterogênea Criada.";
    qWarning() << "Contadores:";
    qWarning() << "GPU´s detectadas:" << ICL_GPUCounter ;
    qWarning() << "CPU´s detectadas:" << ICL_GPUCounter ;
    qWarning() << "ACE´s detectadas:" << ICL_ACECounter ;
    qWarning() << "=================";
    qWarning() << "Indice Graphics     :" << ICL_GraphicsPlat ;
    qWarning() << "Indice Heterogeneous:" << ICL_Heterogeneus ;
    qWarning() << "Indice Auxiliary    :" << ICL_Auxiliary ;
}

void CICLSystem::UpdateHardwareDevices()
{
    ICL_GLRC  = wglGetCurrentContext();
    ICL_HDC   = wglGetCurrentDC();
}

void CICLSystem::TransformBufferGL(CIMTVertexBuffer *pICL_Buffer, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
   ICL_Plataformas[ICL_Heterogeneus]->execDevice(pICL_Buffer,pICL_BufferSize,pICL_Transform);
}

void CICLSystem::TransformBufferGL(uint pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
   ICL_Plataformas[ICL_GraphicsPlat]->execDevice(pICL_BufferId,pICL_BufferSize,pICL_Transform);
}

void CICLSystem::ExtraiContadores()
{
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        ICL_CPUCounter += ICL_Plataformas[i]->CountDevicesByType(ICL_DEV_CPU);
        ICL_GPUCounter += ICL_Plataformas[i]->CountDevicesByType(ICL_DEV_GPU);
        ICL_ACECounter += ICL_Plataformas[i]->CountDevicesByType(ICL_DEV_ACEL);
    }
}

void CICLSystem::ExtraiIndices()
{
    for(uint i=0; i<ICL_QtdPlataformas;i++ )
    {
        if(ICL_Plataformas[i]->VerificaGPUPrimaria())
        {
            ICL_GraphicsPlat = i;
            ICL_InteropComputing = true;
        }

        if(ICL_Plataformas[i]->VerificaGPUSecundaria())
        {
            ICL_Heterogeneus = i;
            ICL_HeterogComputing = true;
        }

        if(ICL_Plataformas[i]->VerificaCPUAuxiliar())
        {
            ICL_Auxiliary = i;
            ICL_AuxiliaryComputing = true;
        }
    }
}

void CICLSystem::ExtraiIndicadores(bool &pICL_InteropComputing, bool &pICL_HeterogComputing, bool &pICL_AuxiliaryComputing)
{
    pICL_InteropComputing   = ICL_InteropComputing;
    pICL_HeterogComputing   = ICL_HeterogComputing;
    pICL_AuxiliaryComputing = ICL_AuxiliaryComputing;
}
