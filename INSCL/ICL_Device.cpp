/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "ICL_Device.h"

CICLDevice::~CICLDevice()
{
    clReleaseCommandQueue(ICL_DeviceCommandQueue);
    clReleaseContext     (ICL_DeviceContext     );
}

CICLDevice::CICLDevice(cl_device_id pICL_DeviceID, cl_platform_id pICL_PlatformID, QString pICL_DefaultGPUVendor)
{
    ICL_DeviceID = pICL_DeviceID;

    //Extrai Nome e Type do Device
    ExtraiDevice();

    //Extrai Nome e ID do Vendor
    ExtraiVendor();

    //Extrai informações de Compute Units para processamento
    ExtraiCompUnits();

    //Extrai as Extensões disponiveis no hardware
    ExtraiExtensions();

    //Identifica se o device é a GPU default do sistema
    ExtraiGPUDefault(pICL_DefaultGPUVendor);

    //Identifica se o device possui extenção de interoperabilidade.
    ExtraiGLInterop();

    //Cria Contexto de execução para o Device na Plataforma
    CriaContexto(pICL_PlatformID);

    //Compila todos os Kernels disponíveis para o Device
    CompilaKernels();

    //Cria a Queue de Execução para os requests de processamento
    CriaExecQueue();
}

void CICLDevice::execPgm(CIMTVertexBuffer *pICL_Buffer, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
   CICLProgram *tPrograma = PegaProgramaPorNome("INSGL.cl");
   if(tPrograma)
   {
      CICLKernel *tKernel = tPrograma->PegaKernelPorNome("TransformGLBuffer");
      if(tKernel)
      {
         tKernel->PreparaParametro(ICL_DeviceContext,pICL_Buffer,pICL_BufferSize,pICL_Transform);
         tKernel->ExecutaKernel(ICL_DeviceCommandQueue,pICL_Buffer);
      }
      else
      {
          //tratar erro aqui!!!
      }
   }
   else
   {
       //tratar erro!!!
   }
}

void CICLDevice::execPgm(uint pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
    CICLProgram *tPrograma = PegaProgramaPorNome("INSGL");
    if(tPrograma)
    {
       CICLKernel *tKernel = tPrograma->PegaKernelPorNome("TransformGLBuffer");
       if(tKernel)
       {
          tKernel->PreparaParametro(ICL_DeviceContext,pICL_BufferId,pICL_BufferSize,pICL_Transform);
          tKernel->ExecutaKernel(ICL_DeviceCommandQueue,pICL_BufferId);
       }
       else
       {
           //tratar erro aqui!!!
       }
    }
    else
    {
        //tratar erro!!!
    }
}

uint CICLDevice::PegaTpDevice()
{
    return ICL_SystemDeviceType;
}

CICLProgram* CICLDevice::PegaProgramaPorNome(QString pICL_Nome)
{
    for(int i=0;i<ICL_QtdProgramas;i++)
    {
        QFileInfo file(ICL_Programas[i]->ICL_ProgramName);
        if(file.baseName() == pICL_Nome)return ICL_Programas[i];
    }

    return NULL;
}

void CICLDevice::PegaIndicadores(bool &pICL_DefaultGPUCard, bool &pICL_InteropDevice)
{
    pICL_DefaultGPUCard = ICL_DefaultGPUCard;
    pICL_InteropDevice  = ICL_InteropDevice;
}

void CICLDevice::ExtraiGPUDefault(QString pICL_DefaultGPUVendor)
{
    QString sDeviceVendor;

    sDeviceVendor = QString(ICL_Vendor);

    switch(PegaTpDevice())
    {
       case ICL_DEV_GPU:
       {
          if(sDeviceVendor == pICL_DefaultGPUVendor)
          {
              ICL_DefaultGPUCard = true;
          }
          else
          {
              ICL_DefaultGPUCard = false;
          }
       }break;
       default:{ICL_DefaultGPUCard = false;}break;
    }
}

void CICLDevice::ExtraiGLInterop()
{
    QString sExtensions = QString(ICL_Extensions);

    if(sExtensions.contains("cl_khr_gl_sharing",Qt::CaseInsensitive))
    {
        ICL_InteropDevice = true;
    }
    else
    {
        ICL_InteropDevice = false;
    }
}

void CICLDevice::ExtraiVendor()
{
    cl_int  ICL_Error;
    size_t  ICL_ParameterSize;
    //Pega o Device Vendor
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_VENDOR , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    //aloca o nome
    ICL_Vendor = new char[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_VENDOR , ICL_ParameterSize, ICL_Vendor , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }


    //Pega o VendorID
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_VENDOR_ID , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_VendorId = new cl_uint[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_VENDOR_ID , ICL_ParameterSize, ICL_VendorId , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

}

void CICLDevice::ExtraiCompUnits()
{
    cl_int  ICL_Error;
    size_t  ICL_ParameterSize;
    //Pega o Maximo de Compute Units
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_COMPUTE_UNITS , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_MaxComputeUnits = new cl_uint[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_COMPUTE_UNITS , ICL_ParameterSize, ICL_MaxComputeUnits , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }


    //Pega o Maximo de Working Itens Dimensions
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_MaxWorkItemDimensions = new cl_uint[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS , ICL_ParameterSize, ICL_MaxWorkItemDimensions , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }


    //Pega Tamanho Maximo de WorkItem por Dimensão
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_WORK_ITEM_SIZES , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_MaxWorkItemDimensionsSize = new size_t[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_WORK_ITEM_SIZES , ICL_ParameterSize, ICL_MaxWorkItemDimensionsSize , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    //Pega Tamanho Maximo de WorkGroups
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_WORK_GROUP_SIZE , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_MaxWorkGroupSize = new size_t[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_WORK_GROUP_SIZE , ICL_ParameterSize, ICL_MaxWorkGroupSize , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    //Pega o Global Cache Memory Size
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_GlobalMemCacheSize = new cl_uint[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE , ICL_ParameterSize, ICL_GlobalMemCacheSize , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }


    //Pega o Global Memory Size
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_GLOBAL_MEM_SIZE , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_GlobalMemorySize = new cl_ulong[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_GLOBAL_MEM_SIZE , ICL_ParameterSize, ICL_GlobalMemorySize , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    //Pega o Max Allocation Size
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_MEM_ALLOC_SIZE , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_MaxAllocationSize = new cl_ulong[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_MAX_MEM_ALLOC_SIZE , ICL_ParameterSize, ICL_MaxAllocationSize , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }
}

void CICLDevice::ExtraiExtensions()
{
    cl_int  ICL_Error;
    size_t  ICL_ParameterSize;
    //Pega as extensões do device
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_EXTENSIONS , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    ICL_Extensions = new char[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_EXTENSIONS , ICL_ParameterSize, ICL_Extensions , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }
}

void CICLDevice::ExtraiDevice()
{
    cl_int  ICL_Error;
    size_t  ICL_ParameterSize;
    //Pega o Tipo do Device
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_TYPE , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    //Aloca o tamanho dos device Type
    ICL_DeviceType = new cl_device_type[ICL_ParameterSize];

    /***********************************************************************************/
    /*TIPOS POSSIVEIS DE DEVICE:                                                       */
    /*case CL_DEVICE_TYPE_CPU         : qWarning() << "Device Type: CPU"       ;break; */
    /*case CL_DEVICE_TYPE_GPU         : qWarning() << "Device Type: GPU"       ;break; */
    /*case CL_DEVICE_TYPE_ACCELERATOR : qWarning() << "Device Type: Acelerator";break; */
    /*case CL_DEVICE_TYPE_DEFAULT     : qWarning() << "Device Type: Default"   ;break; */
    /***********************************************************************************/
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_TYPE , ICL_ParameterSize, ICL_DeviceType , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Device Type.";
        return;
    }

    //Atribui ao Device o Device Type do Sistema
    switch(*ICL_DeviceType)
    {
       case CL_DEVICE_TYPE_CPU:
       {
          ICL_SystemDeviceType = ICL_DEV_CPU;
       }break;

       case CL_DEVICE_TYPE_GPU:
       {
          ICL_SystemDeviceType = ICL_DEV_GPU;
       }break;

       case CL_DEVICE_TYPE_ACCELERATOR:
       {
          ICL_SystemDeviceType = ICL_DEV_ACEL;
       }break;
    }

    //Pega o Device Name
    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_NAME , 0, NULL, &ICL_ParameterSize );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }

    //aloca o nome
    ICL_Nome = new char[ICL_ParameterSize];

    ICL_Error = clGetDeviceInfo( ICL_DeviceID , CL_DEVICE_NAME , ICL_ParameterSize, ICL_Nome , NULL );
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Info Device.";
        return;
    }
}

bool CICLDevice::CriaContexto(cl_platform_id pICL_PlatformID)
{
    cl_int  ICL_Error;
    //Abre O contexto de execução do Device de acordo com o tipo (CPU ou GPU??)
    //Obs:. para abertura de contexto de interoperabilidade somente sera executado na GPU Default do sistema
    //Já que a aplicação utiliza contexto unico para renderização
    switch(ICL_SystemDeviceType)
    {
       case ICL_DEV_CPU:
       {
          ICL_DeviceContext = clCreateContext(NULL, 1, &ICL_DeviceID , NULL, NULL, &ICL_Error);
          if (ICL_Error != CL_SUCCESS)
          {
             //qWarning() << "Não foi possivel Abrir contexto normal.";
             return false;
          }
       }break;

       case ICL_DEV_GPU:
       {
          if(ICL_DefaultGPUCard)
          {
             //Estrutura Properties para contexto OpenGL para windows
             //Obs:. Para as outras plataformas adaptar aqui primeiramente , depois organizar melhor ;)
             #ifdef Q_OS_WIN
             cl_context_properties properties[] =
             {
                 CL_CONTEXT_PLATFORM, (cl_context_properties) pICL_PlatformID,
                 CL_GL_CONTEXT_KHR,   (cl_context_properties) wglGetCurrentContext(),
                 CL_WGL_HDC_KHR,      (cl_context_properties) wglGetCurrentDC(),
                 0
             };
             #endif

             ICL_DeviceContext = clCreateContext(properties,1,&ICL_DeviceID,NULL,NULL,&ICL_Error);
             if (ICL_Error != CL_SUCCESS)
             {
                //qWarning() << "Não foi possivel Abrir contexto Interoperação.";
                return false;
             }
          }
          else
          {
              ICL_DeviceContext = clCreateContext(NULL, 1, &ICL_DeviceID , NULL, NULL, &ICL_Error);
              if (ICL_Error != CL_SUCCESS)
              {
                 //qWarning() << "Não foi possivel Abrir contexto normal.";
                 return false;
              }
          }
       }break;
    }

    return true;
}

bool CICLDevice::CompilaKernels()
{
    //Cria Lista de Programas Baseado no tipo de dispositivo vs estrutura diretorio
    switch(ICL_SystemDeviceType)
    {
       case ICL_DEV_CPU:
       {
          //Pega a lista de Kernels disponiveis
          QDir dir = QDir("world/Kernels/AMD/CPU/");
          QStringList nameFilters;
          nameFilters << QStringLiteral("*.cl");
          QStringList entries = dir.entryList(nameFilters,QDir::Files|QDir::Readable, QDir::Size);

          ICL_QtdProgramas = (cl_uint)entries.size();

          for(cl_uint i=0;i<ICL_QtdProgramas;i++)
          {
             //Para cada .cl criamos um programa diferente
             ICL_Programas.push_back(new CICLProgram(ICL_DeviceContext,ICL_DeviceID,dir.path() + "/" + entries[i]));
          }
       }break;

       case ICL_DEV_GPU:
       {
          //Pega a lista de Kernels disponiveis
          QDir dir = QDir("world/Kernels/AMD/GPU/");
          QStringList nameFilters;
          nameFilters << QStringLiteral("*.cl");
          QStringList entries = dir.entryList(nameFilters,QDir::Files|QDir::Readable, QDir::Size);

          ICL_QtdProgramas = (cl_uint)entries.size();

          for(cl_uint i=0;i<ICL_QtdProgramas;i++)
          {
             //Para cada .cl criamos um programa diferente
             ICL_Programas.push_back(new CICLProgram(ICL_DeviceContext,ICL_DeviceID,dir.path() + "/" + entries[i]));
          }
       }break;
    }

    return true;
}

bool CICLDevice::CriaExecQueue()
{
    cl_int  ICL_Error;
    //Cria uma Command Queue para execução de Kernels
    ICL_DeviceCommandQueue = clCreateCommandQueue(ICL_DeviceContext, ICL_DeviceID , 0, &ICL_Error);
    if(ICL_Error != CL_SUCCESS)
    {
        //qWarning() << "Não foi possivel Criar uma Command Queue no device para este Contexto.";
        exit(1);
    }

    return true;
}
