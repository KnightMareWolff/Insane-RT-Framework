#ifndef CIMTVERTEX_H
#define CIMTVERTEX_H

#include "INSMT_global.h"
#include "IMT_Vector.h"

class INSMT_EXPORT CIMTVertex
{
public:
    CIMTVertex( );

    CIMTVertex( const CIMTVertex & vec );

    CIMTVertex( CIMTVector  pIMT_Position  ,
                CIMTVector2 pIMT_TexCoord  ,
                CIMTVector  pIMT_Normal    ,
                CIMTVector  pIMT_Smooth    ,
                CIMTVector  pIMT_Tangent  ,
                CIMTVector  pIMT_Bitangent);

    union {
        struct {
            float  IMT_Position[3];
            float  IMT_TexCoord[2];
            float  IMT_Normal[3];
            float  IMT_Smooth[3];
            float  IMT_Tangent[3];
            float  IMT_Bitangent[3];
        };
        float v[17];
    };

    void SetPosition (const CIMTVector & vec){IMT_Position[0] =vec.x;IMT_Position[1] =vec.y;IMT_Position[2] =vec.z;}
    void SetTexCoord (const CIMTVector2& vec){IMT_TexCoord[0] =vec.x;IMT_TexCoord[1] =vec.y;}
    void SetNormal   (const CIMTVector & vec){IMT_Normal[0]   =vec.x;IMT_Normal[1]   =vec.y;IMT_Normal[2]   =vec.z;}
    void SetSmooth   (const CIMTVector & vec){IMT_Smooth[0]   =vec.x;IMT_Smooth[1]   =vec.y;IMT_Smooth[2]   =vec.z;}
    void SetTangent  (const CIMTVector & vec){IMT_Tangent[0]  =vec.x;IMT_Tangent[1]  =vec.y;IMT_Tangent[2]  =vec.z;}
    void SetBitangent(const CIMTVector & vec){IMT_Bitangent[0]=vec.x;IMT_Bitangent[1]=vec.y;IMT_Bitangent[2]=vec.z;}

    CIMTVector  GetPosition (){return CIMTVector (IMT_Position[0],IMT_Position[1],IMT_Position[2]);}
    CIMTVector2 GetTexCoord (){return CIMTVector2(IMT_TexCoord[0],IMT_TexCoord[1]);}
    CIMTVector  GetNormal   (){return CIMTVector (IMT_Normal[0],IMT_Normal[1],IMT_Normal[2]);}
    CIMTVector  GetSmooth   (){return CIMTVector (IMT_Smooth[0],IMT_Smooth[1],IMT_Smooth[2]);}
    CIMTVector  GetTangent  (){return CIMTVector (IMT_Tangent[0],IMT_Tangent[1],IMT_Tangent[2]);}
    CIMTVector  GetBitangent(){return CIMTVector (IMT_Bitangent[0],IMT_Bitangent[1],IMT_Bitangent[2]);}

    CIMTVertex& operator=  ( const CIMTVertex & vec );
    CIMTVertex& operator=  ( const CIMTVector & vec );
    CIMTVertex& operator=  ( const CIMTVector2& vec );
};

#endif // CIMTVERTICE_H
