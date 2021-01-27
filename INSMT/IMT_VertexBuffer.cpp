#include "IMT_VertexBuffer.h"

CIMTVertexBuffer::CIMTVertexBuffer()
{
    IMT_VboIds[0] = 0;
    IMT_VboIds[1] = 0;
    IMT_VboIds[2] = 0;

    IMT_IsValid     = false;
    IMT_IsGPUBuffer = false;
}

CIMTVertexBuffer::CIMTVertexBuffer( const CIMTVertexBuffer & copy )
{   
    IMT_Buffer   = copy.IMT_Buffer  ;
    IMT_Indices  = copy.IMT_Indices ;
    IMT_Feedback = copy.IMT_Feedback;

    IMT_VboIds[0] = copy.IMT_VboIds[0];
    IMT_VboIds[1] = copy.IMT_VboIds[1];
    IMT_VboIds[2] = copy.IMT_VboIds[2];

    IMT_IsValid     = copy.IMT_IsValid;
    IMT_IsGPUBuffer = copy.IMT_IsGPUBuffer;
}

CIMTVertexBuffer& CIMTVertexBuffer::operator=  ( const CIMTVertexBuffer& opr )
{
    IMT_Buffer   = opr.IMT_Buffer  ;
    IMT_Indices  = opr.IMT_Indices ;
    IMT_Feedback = opr.IMT_Feedback;

    IMT_VboIds[0] = opr.IMT_VboIds[0];
    IMT_VboIds[1] = opr.IMT_VboIds[1];
    IMT_VboIds[2] = opr.IMT_VboIds[2];

    IMT_IsValid     = opr.IMT_IsValid;
    IMT_IsGPUBuffer = opr.IMT_IsGPUBuffer;

    return *this;
}

void CIMTVertexBuffer::Initialize(uint pIMT_NumberOfVertex)
{

    if ( pIMT_NumberOfVertex == 0 ) return;

    IMT_Buffer   = vector<CIMTVertex>(  pIMT_NumberOfVertex        ,CIMTVertex());
    IMT_Indices  = vector<uint      >(((pIMT_NumberOfVertex-2) * 3),0           );
    IMT_Feedback = vector<CIMTVector>(  pIMT_NumberOfVertex        ,CIMTVector());
}

void CIMTVertexBuffer::Initialize(uint pIMT_NumberOfVertex,uint pIMT_NumberOfIndex)
{

    if ( pIMT_NumberOfVertex == 0 ) return;

    IMT_Buffer   = vector<CIMTVertex>(  pIMT_NumberOfVertex ,CIMTVertex());
    IMT_Indices  = vector<uint      >(  pIMT_NumberOfIndex  ,0           );
    IMT_Feedback = vector<CIMTVector>(  pIMT_NumberOfVertex ,CIMTVector());
}
