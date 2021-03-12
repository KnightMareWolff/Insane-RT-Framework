/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CICLProgram_H
#define CICLProgram_H

#include "INSCL_global.h"
#include "ICL_Kernel.h"

class CICLProgram
{
public:
     CICLProgram(cl_context   pICL_DeviceContext ,
                 cl_device_id pICL_DeviceID      ,
                 QString      pICL_FileName      );

    ~CICLProgram(                                );

     CICLKernel* PegaKernelPorNome(QString pICL_Nome);

     QString ICL_ProgramName;

private:
    cl_program    ICL_ProgramID;

    //controle de compilação
    //Log de Compilação
    char*   program_log;
    size_t  log_size;

    //Kernels para Execução
    cl_uint             ICL_QtdKernels;
    vector<CICLKernel*> ICL_Kernels;
};

#endif // CICLProgram_H
