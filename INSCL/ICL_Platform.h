/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CICLPlatform_H
#define CICLPlatform_H

#include "INSCL_global.h"
#include "ICL_Device.h"

class CICLPlatform
{
public:
    CICLPlatform(cl_platform_id pICL_PlatformID,QString pICL_DefaultGPUVendor);

    void execDevice(CIMTVertexBuffer *pICL_Buffer  , uint pICL_BufferSize, CIMTMatrix *pICL_Transform);
    void execDevice(uint              pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform);

    // ---- Métodos Públicos Auxiliares ----
    int  CountDevicesByType   (int pICL_DeviceType);
    bool VerificaGPUPrimaria  (                   );
    bool VerificaGPUSecundaria(                   );
    bool VerificaCPUAuxiliar  (                   );

private:
    cl_platform_id ICL_PlatformID;

    //atributos de descrição da plataforma
    char*   ICL_Profile;
    char*   ICL_Versao;
    char*   ICL_Nome;
    char*   ICL_Vendor;
    char*   ICL_Extensoes;

    //atributos de controle
    cl_uint         ICL_QtdDevices; //quantidade de devices na plataforma
    cl_device_id*   ICL_ListaID;    //Lista de ID´s de devices na plataforma

    //Lista de Devices da Plataforma
    vector<CICLDevice*> ICL_Devices;
};

#endif // CICLPlatform_H
