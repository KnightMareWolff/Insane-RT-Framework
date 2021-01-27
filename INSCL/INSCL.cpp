#include "INSCL.h"

//Inicialização da Instância Estatica
CICLSystem* INSCL::pINSCLStaticInterface=NULL;

/****************************************/
/*Rotinas de Inicialização de Interface */
/****************************************/
INSCL::INSCL()
{
}

INSCL::INSCL(QGLContext *pContext, QString pICL_DefaultGPUVendor)
{
    pINSCLStaticInterface = new CICLSystem(pContext,pICL_DefaultGPUVendor);
}

INSCL::INSCL(QOpenGLContext *pContext, QString pICL_DefaultGPUVendor)
{
    pINSCLStaticInterface = new CICLSystem(pContext,pICL_DefaultGPUVendor);
}

void INSCL::execCL(int pICL_Function)
{
    switch(pICL_Function)
    {
       case ICL_EXEC_UPDATE_GL_CTXT:
       {
          pINSCLStaticInterface->UpdateHardwareDevices();
       }break;
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
       }
    }
}

void INSCL::execCL(int pICL_Function, CIMTVertexBuffer *pICL_Buffer, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
    switch(pICL_Function)
    {
       case ICL_EXEC_TRANSFORM_GL:
       {
          pINSCLStaticInterface->TransformBufferGL(pICL_Buffer,pICL_BufferSize,pICL_Transform);
       }break;
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
       }
    }
}

void INSCL::execCL(int pICL_Function, uint pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
    switch(pICL_Function)
    {
       case ICL_EXEC_TRANSFORM_GL:
       {
          pINSCLStaticInterface->TransformBufferGL(pICL_BufferId,pICL_BufferSize,pICL_Transform);
       }break;
       default:
       {
          qWarning() << "Não Ha Função para este comando.";
       }
    }
}

bool INSCL::SupportGLInteroperation()
{
    bool tICL_InteropSupported;
    bool tICL_HeterogeneousSupported;
    bool tICL_AuxiliarySupported;

    pINSCLStaticInterface->ExtraiIndicadores(tICL_InteropSupported,tICL_HeterogeneousSupported,tICL_AuxiliarySupported);

    return tICL_InteropSupported;
}

bool INSCL::SupportHWOptimization()
{
    bool tICL_InteropSupported;
    bool tICL_HeterogeneousSupported;
    bool tICL_AuxiliarySupported;

    pINSCLStaticInterface->ExtraiIndicadores(tICL_InteropSupported,tICL_HeterogeneousSupported,tICL_AuxiliarySupported);

    if(tICL_HeterogeneousSupported || tICL_AuxiliarySupported)return true;
    return false;
}
