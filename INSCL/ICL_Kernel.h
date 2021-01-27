#ifndef CICLKERNEL_H
#define CICLKERNEL_H

#include "INSCL_global.h"

class CICLKernel
{
public:
     CICLKernel(cl_kernel  pICL_KernelID);
    ~CICLKernel();

    cl_kernel  ICL_KernelID      ;
    cl_uint    ICL_QtdArgumentos ;
    char       ICL_NomeFuncao[32];

    cl_mem            ICL_BufferIn    ;
    cl_mem            ICL_BufferOut   ;
    cl_uint           ICL_GLBufferSize;
    cl_float16        ICL_TransfMatrix;
    CIMTVertexBuffer *ICL_VertexBuffer;

    void PreparaParametro(cl_context pICL_DeviceContext,CIMTVertexBuffer *pGLBuffer  ,uint pGLBufferSize,CIMTMatrix *pTransfMatrix);
    void PreparaParametro(cl_context pICL_DeviceContext,uint              pGLBufferId,uint pGLBufferSize,CIMTMatrix *pTransfMatrix);

    void ExecutaKernel   (cl_command_queue pICL_DeviceCommandQueue,CIMTVertexBuffer *pGLBuffer  );
    void ExecutaKernel   (cl_command_queue pICL_DeviceCommandQueue,uint              pGLBufferId);
};

#endif // CICLKERNEL_H
