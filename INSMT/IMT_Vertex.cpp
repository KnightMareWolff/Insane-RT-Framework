#include "IMT_Vertex.h"
#include <cstring>


CIMTVertex::CIMTVertex( )
{
    // Reset required variables.
    memcpy(IMT_Position ,CIMTVector (0.0f,0.0f,0.0f).v,sizeof(float) * 3);
    memcpy(IMT_TexCoord ,CIMTVector2(0.0f,0.0f)     .v,sizeof(float) * 2);
    memcpy(IMT_Normal   ,CIMTVector (0.0f,0.0f,0.0f).v,sizeof(float) * 3);
    memcpy(IMT_Smooth   ,CIMTVector (0.0f,0.0f,0.0f).v,sizeof(float) * 3);
    memcpy(IMT_Tangent  ,CIMTVector (0.0f,0.0f,0.0f).v,sizeof(float) * 3);
    memcpy(IMT_Bitangent,CIMTVector (0.0f,0.0f,0.0f).v,sizeof(float) * 3);
}

CIMTVertex::CIMTVertex( const CIMTVertex & vec )
{
    memcpy(IMT_Position   , vec.IMT_Position ,sizeof(float) * 3);
    memcpy(IMT_TexCoord   , vec.IMT_TexCoord ,sizeof(float) * 2);
    memcpy(IMT_Normal     , vec.IMT_Normal   ,sizeof(float) * 3);
    memcpy(IMT_Smooth     , vec.IMT_Smooth   ,sizeof(float) * 3);
    memcpy(IMT_Tangent    , vec.IMT_Tangent  ,sizeof(float) * 3);
    memcpy(IMT_Bitangent  , vec.IMT_Bitangent,sizeof(float) * 3);
}

CIMTVertex::CIMTVertex( CIMTVector  pIMT_Position  ,
                        CIMTVector2 pIMT_TexCoord ,
                        CIMTVector  pIMT_Normal   ,
                        CIMTVector  pIMT_Smooth   ,
                        CIMTVector  pIMT_Tangent  ,
                        CIMTVector  pIMT_Bitangent)
{
    memcpy(IMT_Position ,pIMT_Position .v,sizeof(float) * 3);
    memcpy(IMT_TexCoord ,pIMT_TexCoord .v,sizeof(float) * 2);
    memcpy(IMT_Normal   ,pIMT_Normal   .v,sizeof(float) * 3);
    memcpy(IMT_Smooth   ,pIMT_Smooth   .v,sizeof(float) * 3);
    memcpy(IMT_Tangent  ,pIMT_Tangent  .v,sizeof(float) * 3);
    memcpy(IMT_Bitangent,pIMT_Bitangent.v,sizeof(float) * 3);
}

CIMTVertex& CIMTVertex::operator=  ( const CIMTVertex& vec )
{
    memcpy(IMT_Position   , vec.IMT_Position ,sizeof(float) * 3);
    memcpy(IMT_TexCoord   , vec.IMT_TexCoord ,sizeof(float) * 2);
    memcpy(IMT_Normal     , vec.IMT_Normal   ,sizeof(float) * 3);
    memcpy(IMT_Smooth     , vec.IMT_Smooth   ,sizeof(float) * 3);
    memcpy(IMT_Tangent    , vec.IMT_Tangent  ,sizeof(float) * 3);
    memcpy(IMT_Bitangent  , vec.IMT_Bitangent,sizeof(float) * 3);

    return *this;
}

CIMTVertex& CIMTVertex::operator=  ( const CIMTVector& vec )
{
    IMT_Position[0] = vec.x;
    IMT_Position[1] = vec.y;
    IMT_Position[2] = vec.z;

    return *this;
}

CIMTVertex& CIMTVertex::operator=  ( const CIMTVector2& vec )
{
    IMT_TexCoord[0] = vec.x;
    IMT_TexCoord[1] = vec.y;

    return *this;
}
