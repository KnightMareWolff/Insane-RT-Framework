#include "ICL_Kernel.h"

CICLKernel::~CICLKernel()
{
   clReleaseKernel(ICL_KernelID);
}

CICLKernel::CICLKernel(cl_kernel pICL_KernelID)
{

    ICL_KernelID = pICL_KernelID;

    clGetKernelInfo(ICL_KernelID, CL_KERNEL_FUNCTION_NAME, sizeof(ICL_NomeFuncao)    ,  ICL_NomeFuncao      , NULL);
    clGetKernelInfo(ICL_KernelID, CL_KERNEL_NUM_ARGS     , sizeof(ICL_QtdArgumentos) , &ICL_QtdArgumentos   , NULL);

    //qWarning() << "Kernel Name: " << ICL_NomeFuncao << "Com Qtd Ags:" << ICL_QtdArgumentos;

    //ICL_VertexBuffer = NULL;

}

void CICLKernel::PreparaParametro(cl_context pICL_DeviceContext, CIMTVertexBuffer *pGLBuffer, uint pGLBufferSize, CIMTMatrix *pTransfMatrix)
{
    cl_int  ICL_Error;

    float * matriz = new float[16];

    //Verifica se o Buffer já foi usado
    if(ICL_VertexBuffer->IMT_Buffer.size()==0)
    {
       ICL_VertexBuffer = new CIMTVertexBuffer();
    }
    else
    {
       //se o tamanho for diferente a gende limpa e recria
       if(ICL_GLBufferSize!=pGLBufferSize)
       {
          delete []ICL_VertexBuffer;
          ICL_VertexBuffer   = NULL;
          ICL_VertexBuffer = new CIMTVertexBuffer();
       }
    }

    //Copia dados do Buffer Original que será atualizado na Volta do processamento
    memcpy( ICL_VertexBuffer, pGLBuffer ,pGLBufferSize * sizeof(CIMTVertexBuffer));

    //Cria um buffer no dispositivo(Buffer de entrada)
    ICL_BufferIn = clCreateBuffer(pICL_DeviceContext,
                                  CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
                                  sizeof(CIMTVertexBuffer) * pGLBufferSize,
                                  ICL_VertexBuffer,
                                  &ICL_Error);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel Mapear o Buffer de Entrada.";
        exit(1);
    }

    //Cria um buffer no dispositivo(Buffer de entrada)
    ICL_BufferOut = clCreateBuffer(pICL_DeviceContext,
                                   CL_MEM_READ_WRITE ,
                                   sizeof(CIMTVertexBuffer) * pGLBufferSize,
                                   NULL,
                                   &ICL_Error);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel Mapear o Buffer OpenGL.";
        exit(1);
    }

    //Seta o tamanho do buffer
    ICL_GLBufferSize = pGLBufferSize;

    //Seta a matriz de transformação
    matriz  = *pTransfMatrix;

    ICL_TransfMatrix.s0 = matriz[0];
    ICL_TransfMatrix.s1 = matriz[1];
    ICL_TransfMatrix.s2 = matriz[2];
    ICL_TransfMatrix.s3 = matriz[3];
    ICL_TransfMatrix.s4 = matriz[4];
    ICL_TransfMatrix.s5 = matriz[5];
    ICL_TransfMatrix.s6 = matriz[6];
    ICL_TransfMatrix.s7 = matriz[7];
    ICL_TransfMatrix.s8 = matriz[8];
    ICL_TransfMatrix.s9 = matriz[9];
    ICL_TransfMatrix.sa = matriz[10];
    ICL_TransfMatrix.sb = matriz[11];
    ICL_TransfMatrix.sc = matriz[12];
    ICL_TransfMatrix.sd = matriz[13];
    ICL_TransfMatrix.se = matriz[14];
    ICL_TransfMatrix.sf = matriz[15];

    //Seta o Parametro do Buffer
    ICL_Error = clSetKernelArg(ICL_KernelID,0,sizeof(cl_mem),(void*)&ICL_BufferIn);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel atribuir buffer a Kernel.";
        exit(1);
    }

    //Seta parametro do tamanho do buffer
    ICL_Error = clSetKernelArg(ICL_KernelID,1,sizeof(cl_mem),(void *)&ICL_BufferOut);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel atribuir buffer a Kernel.";
        exit(1);
    }

    ICL_Error = clSetKernelArg(ICL_KernelID,2,sizeof(cl_float16),(void *)&ICL_TransfMatrix);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel atribuir buffer a Kernel.";
        exit(1);
    }

}

void CICLKernel::PreparaParametro(cl_context pICL_DeviceContext, uint pGLBufferId, uint pGLBufferSize, CIMTMatrix *pTransfMatrix)
{
    cl_int  ICL_Error;

    float * matriz = new float[16];

    ICL_BufferIn = clCreateFromGLBuffer(pICL_DeviceContext, CL_MEM_WRITE_ONLY, pGLBufferId , &ICL_Error);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel Recuperar Buffer para Interop. OpenGL.";
        exit(1);
    }


    //Seta o tamanho do buffer
    ICL_GLBufferSize = pGLBufferSize;

    //Seta a matriz de transformação
    matriz  = *pTransfMatrix;

    ICL_TransfMatrix.s0 = matriz[0];
    ICL_TransfMatrix.s1 = matriz[1];
    ICL_TransfMatrix.s2 = matriz[2];
    ICL_TransfMatrix.s3 = matriz[3];
    ICL_TransfMatrix.s4 = matriz[4];
    ICL_TransfMatrix.s5 = matriz[5];
    ICL_TransfMatrix.s6 = matriz[6];
    ICL_TransfMatrix.s7 = matriz[7];
    ICL_TransfMatrix.s8 = matriz[8];
    ICL_TransfMatrix.s9 = matriz[9];
    ICL_TransfMatrix.sa = matriz[10];
    ICL_TransfMatrix.sb = matriz[11];
    ICL_TransfMatrix.sc = matriz[12];
    ICL_TransfMatrix.sd = matriz[13];
    ICL_TransfMatrix.se = matriz[14];
    ICL_TransfMatrix.sf = matriz[15];

    //Seta o Parametro do Buffer
    ICL_Error = clSetKernelArg(ICL_KernelID,0,sizeof(cl_mem),(void*)&ICL_BufferIn);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel atribuir buffer a Kernel.";
        exit(1);
    }

    ICL_Error = clSetKernelArg(ICL_KernelID,1,sizeof(cl_float16),(void *)&ICL_TransfMatrix);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel atribuir buffer a Kernel.";
        exit(1);
    }

}

void CICLKernel::ExecutaKernel(cl_command_queue pICL_DeviceCommandQueue, CIMTVertexBuffer *pGLBuffer)
{
   cl_int  ICL_Error;

   size_t    globalWorkSize[1] = {ICL_GLBufferSize};
   size_t    localWorkSize[1]  = {1};
   cl_event  eventND[1];

   ICL_Error = clEnqueueNDRangeKernel(pICL_DeviceCommandQueue, ICL_KernelID, 1 , NULL, globalWorkSize ,localWorkSize, 0, NULL , eventND );
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }


   //Coloca na Fila a requisição do resultado(leitura do buffer de saida)
   ICL_Error = clEnqueueReadBuffer(pICL_DeviceCommandQueue,
                                   ICL_BufferOut,
                                   CL_TRUE,                                    // blocking read
                                   0,                                          // write from the start
                                   sizeof(CIMTVertexBuffer) * ICL_GLBufferSize, // how much to copy
                                   pGLBuffer,
                                   0,
                                   NULL,
                                   eventND);

   ICL_Error = clWaitForEvents(1, &eventND[0]);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }

   ICL_Error = clFlush(pICL_DeviceCommandQueue);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }


   ICL_Error = clReleaseEvent(*eventND);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }

   ICL_Error = clFinish(pICL_DeviceCommandQueue);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }

   clReleaseMemObject(ICL_BufferIn);
   clReleaseMemObject(ICL_BufferOut);

}

void CICLKernel::ExecutaKernel(cl_command_queue pICL_DeviceCommandQueue, uint pGLBufferId)
{
   cl_int  ICL_Error;

   size_t    globalWorkSize[1]  = {ICL_GLBufferSize};
   size_t    localWorkSize [1]  = {1};
   cl_event  eventND[1];

   // Adquire o Buffer GL
   ICL_Error = clEnqueueAcquireGLObjects(pICL_DeviceCommandQueue,1,&ICL_BufferIn, 0, 0, NULL);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }


   ICL_Error = clEnqueueNDRangeKernel(pICL_DeviceCommandQueue, ICL_KernelID, 1 , NULL, globalWorkSize ,localWorkSize, 0, NULL , eventND );
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }

   ICL_Error = clWaitForEvents(1, &eventND[0]);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }

   ICL_Error = clFlush(pICL_DeviceCommandQueue);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }


   ICL_Error = clReleaseEvent(*eventND);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }


   ICL_Error = clEnqueueReleaseGLObjects(pICL_DeviceCommandQueue, 1, &ICL_BufferIn, 0, 0, 0);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }


   ICL_Error = clFinish(pICL_DeviceCommandQueue);
   if(ICL_Error != CL_SUCCESS)
   {
       //qWarning() << "Não foi possivel requisitar buffer a Kernel.";
       exit(1);
   }

   clReleaseMemObject(ICL_BufferIn);

}
