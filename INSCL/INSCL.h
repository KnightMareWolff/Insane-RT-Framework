/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef INSCL_H
#define INSCL_H

#include "INSCL_global.h"
#include "ICL_System.h"

class INSCL_EXPORT INSCL
{
public:
    INSCL(                                                      );
    INSCL(QOpenGLContext *pContext,QString pICL_DefaultGPUVendor);

    void execCL(int pICL_Function                                                                                   );
    void execCL(int pICL_Function, CIMTVertexBuffer *pICL_Buffer  , uint pICL_BufferSize, CIMTMatrix *pICL_Transform);
    void execCL(int pICL_Function, uint              pICL_BufferId, uint pICL_BufferSize, CIMTMatrix *pICL_Transform);

    bool SupportGLInteroperation();
    bool SupportHWOptimization  ();

private:
    static CICLSystem *pINSCLStaticInterface;
};

#endif // INSCL_H
