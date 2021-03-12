/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CIMTVERTEXBUFFER_H
#define CIMTVERTEXBUFFER_H

#include "IMT_Vertex.h"

class INSMT_EXPORT CIMTVertexBuffer
{
public:
    CIMTVertexBuffer();
    CIMTVertexBuffer( const CIMTVertexBuffer & copy );

    CIMTVertexBuffer& operator=  ( const CIMTVertexBuffer& opr );

    void Initialize(uint pIMT_NumberOfVertex                        );//for triangulated meshs (nVtx - 2) * 3
    void Initialize(uint pIMT_NumberOfVertex,uint pIMT_NumberOfIndex);//with arbitrary number of indexes

    uint GetSize     (){return IMT_Buffer.size();}
    uint GetIndexSize(){return IMT_Indices.size();}

    //Buffer Data
    vector<CIMTVertex> IMT_Buffer   ;
    vector<uint      > IMT_Indices  ;
    uint               IMT_VboIds[3];
    vector<CIMTVector> IMT_Feedback ;

    //Checking Flags
    bool               IMT_IsValid;
    bool               IMT_IsGPUBuffer;
};

#endif // CIMTVERTEXBUFFER_H
