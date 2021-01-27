#include "ICL_Platform.h"

CICLPlatform::CICLPlatform(cl_platform_id pICL_PlatformID, QString pICL_DefaultGPUVendor)
{
    cl_int  ICL_Error;
    size_t  ICL_ParameterSize;

    ICL_PlatformID = pICL_PlatformID;

    //Pega Informação do Profile Plataforma(Pega Primeiro o Tamanho depois a string)
    ICL_Error = clGetPlatformInfo( ICL_PlatformID , CL_PLATFORM_PROFILE, 0, NULL, &ICL_ParameterSize );

    ICL_Profile = new char[ICL_ParameterSize];
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_PROFILE, ICL_ParameterSize, ICL_Profile , NULL );

    //Pega Informação do Profile Plataforma(Pega Primeiro o Tamanho depois a string)
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_VERSION, 0, NULL, &ICL_ParameterSize );

    ICL_Versao = new char[ICL_ParameterSize];
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_VERSION, ICL_ParameterSize, ICL_Versao , NULL );

    //Pega Informação do Nome da Plataforma
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_NAME, 0, NULL, &ICL_ParameterSize );

    ICL_Nome = new char[ICL_ParameterSize];
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_NAME, ICL_ParameterSize, ICL_Nome , NULL );

    //Pega Informação do Vendor da Plataforma
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_VENDOR, 0, NULL, &ICL_ParameterSize );

    ICL_Vendor = new char[ICL_ParameterSize];
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_VENDOR, ICL_ParameterSize, ICL_Vendor , NULL );

    //Pega Informação das Extensões da Plataforma
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_EXTENSIONS, 0, NULL, &ICL_ParameterSize );

    ICL_Extensoes = new char[ICL_ParameterSize];
    ICL_Error = clGetPlatformInfo( ICL_PlatformID, CL_PLATFORM_EXTENSIONS, ICL_ParameterSize, ICL_Extensoes , NULL );

    //Pega quantos devices estão espetados na máquina pelo tipo de Device
    //CL_DEVICE_TYPE_DEFAULT
    ICL_Error = clGetDeviceIDs(ICL_PlatformID , CL_DEVICE_TYPE_ALL, 0, NULL, &ICL_QtdDevices);
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter O Numero de Devices Anexados a Plataforma.";
        exit(1);
    }

    //aloca o numero necessario de device IDs
    ICL_ListaID = new cl_device_id[ICL_QtdDevices];

    /* Load the information about your devices into the variable 'devices' */
    ICL_Error = clGetDeviceIDs(ICL_PlatformID , CL_DEVICE_TYPE_ALL , ICL_QtdDevices , ICL_ListaID , NULL);
    if (ICL_Error != CL_SUCCESS )
    {
        //qWarning() << "Não foi possivel Obter Os Ids de Devices Anexados a Plataforma.";
        exit(1);
    }

    //Inicializa a lista de Devices da plataforma construindo a partir do ID do Device
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        ICL_Devices.push_back(new CICLDevice(ICL_ListaID[i],ICL_PlatformID,pICL_DefaultGPUVendor));
    }

}

void CICLPlatform::execDevice(CIMTVertexBuffer *pICL_Buffer, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
    //Inicializa a lista de Devices da plataforma construindo a partir do ID do Device
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        if(ICL_Devices[i]->PegaTpDevice() == ICL_DEV_GPU)
        {
            ICL_Devices[i]->execPgm(pICL_Buffer,pICL_BufferSize,pICL_Transform);
        }
    }
}

void CICLPlatform::execDevice(uint pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform)
{
    //Inicializa a lista de Devices da plataforma construindo a partir do ID do Device
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        if(ICL_Devices[i]->PegaTpDevice() == ICL_DEV_GPU)
        {
            ICL_Devices[i]->execPgm(pICL_BufferId,pICL_BufferSize,pICL_Transform);
        }
    }
}

int CICLPlatform::CountDevicesByType(int pICL_DeviceType)
{
    int tICL_Count = 0;

    //Realiza Contagem de Devices pelo Tipo passado
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        if(ICL_Devices[i]->PegaTpDevice() == pICL_DeviceType)
        {
            tICL_Count++;
        }
    }

    return tICL_Count;
}

bool CICLPlatform::VerificaGPUPrimaria()
{
    bool tICL_DefaultGPU = false;
    bool tICL_InteropDev = false;
    bool tICL_IsPrimary  = false;

    int  tICL_GPUCount   = 0;
    int  tICL_CPUCount   = 0;

    //Realiza Contagem de Devices pelo Tipo passado
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        if(ICL_Devices[i]->PegaTpDevice()==ICL_DEV_GPU)
        {
           tICL_GPUCount++;

           ICL_Devices[i]->PegaIndicadores(tICL_DefaultGPU,tICL_InteropDev);
           if(tICL_DefaultGPU && tICL_InteropDev)
           {
               tICL_IsPrimary = true;
           }
        }
        if(ICL_Devices[i]->PegaTpDevice()==ICL_DEV_CPU)
        {
           tICL_CPUCount++;
        }
    }

    if(tICL_GPUCount > 0 && tICL_IsPrimary==true)return true;
    return false;
}

bool CICLPlatform::VerificaGPUSecundaria()
{
    bool tICL_DefaultGPU   = false;
    bool tICL_InteropDev   = false;
    bool tICL_IsSecundary  = false;

    int  tICL_GPUCount   = 0;
    int  tICL_CPUCount   = 0;

    //Realiza Contagem de Devices pelo Tipo passado
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        if(ICL_Devices[i]->PegaTpDevice()==ICL_DEV_GPU)
        {
           tICL_GPUCount++;

           ICL_Devices[i]->PegaIndicadores(tICL_DefaultGPU,tICL_InteropDev);
           if(!tICL_DefaultGPU)
           {
               tICL_IsSecundary = true;
           }
        }
        if(ICL_Devices[i]->PegaTpDevice()==ICL_DEV_CPU)
        {
           tICL_CPUCount++;
        }
    }

    if(tICL_GPUCount > 0 && tICL_IsSecundary==true)return true;
    return false;
}

bool CICLPlatform::VerificaCPUAuxiliar()
{
    bool tICL_IsAuxiliary  = false;

    int  tICL_GPUCount   = 0;
    int  tICL_CPUCount   = 0;

    //Realiza Contagem de Devices pelo Tipo passado
    for(uint i=0; i<ICL_QtdDevices;i++ )
    {
        if(ICL_Devices[i]->PegaTpDevice()==ICL_DEV_GPU)
        {
           tICL_GPUCount++;
        }
        if(ICL_Devices[i]->PegaTpDevice()==ICL_DEV_CPU)
        {
           tICL_CPUCount++;
        }
    }

    if(tICL_GPUCount == 0 && tICL_CPUCount > 0)tICL_IsAuxiliary = true;

    return tICL_IsAuxiliary;
}
