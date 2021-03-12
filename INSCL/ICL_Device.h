/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CICLDEVICE_H
#define CICLDEVICE_H

#include "INSCL_global.h"
#include "ICL_Program.h"

class CICLDevice
{
public:
     CICLDevice(cl_device_id pICL_DeviceID,cl_platform_id pICL_PlatformID,QString pICL_DefaultGPUVendor);
    ~CICLDevice(                                                                                       );

     void          execPgm     (CIMTVertexBuffer *pICL_Buffer  , uint pICL_BufferSize, CIMTMatrix *pICL_Transform);
     void          execPgm     (uint              pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform);

     uint          PegaTpDevice        (                                                  );
     CICLProgram*  PegaProgramaPorNome (QString pICL_Nome                                 );
     void          PegaIndicadores     (bool &pICL_DefaultGPUCard,bool &pICL_InteropDevice);

private:
    
    // ------Atributos da plataforma OpenCL-------------

    //Atributos de execução de Kernels
    cl_device_id     ICL_DeviceID;
    cl_device_type*  ICL_DeviceType;
    cl_context       ICL_DeviceContext;
    cl_command_queue ICL_DeviceCommandQueue;
    
    //atributos de descrição do device
    char*   ICL_Nome;
    char*   ICL_Vendor;
    char*   ICL_Extensions;

    //atributos numericos do device
    cl_uint*        ICL_VendorId;
    cl_uint*        ICL_MaxComputeUnits;
    cl_uint*        ICL_MaxWorkItemDimensions;
    cl_uint*        ICL_GlobalMemCacheSize;
    size_t*         ICL_MaxWorkItemDimensionsSize;
    size_t*         ICL_MaxWorkGroupSize;
    cl_ulong*       ICL_GlobalMemorySize;
    cl_ulong*       ICL_MaxAllocationSize;

    //Programas associados ao device.
    cl_uint                ICL_QtdProgramas;
    vector<CICLProgram*>   ICL_Programas;

    // ------Atributos do Objeto no sistema-------------

    //atributos booleanos de funcionamento
    bool   ICL_DefaultGPUCard;
    bool   ICL_InteropDevice;

    //atributos de identificação do device no sistema
    int    ICL_SystemDeviceType;

    // ---- Operações Privadas do Device ----
    void   ExtraiGPUDefault(QString pICL_DefaultGPUVendor );
    void   ExtraiGLInterop (                              );
    void   ExtraiVendor    (                              );
    void   ExtraiCompUnits (                              );
    void   ExtraiExtensions(                              );
    void   ExtraiDevice    (                              );
    bool   CriaContexto    (cl_platform_id pICL_PlatformID);
    bool   CompilaKernels  (                              );
    bool   CriaExecQueue   (                              );
};

#endif // CICLDEVICE_H
