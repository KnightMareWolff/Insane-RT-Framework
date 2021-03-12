/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IMT_BOUNDS_H
#define IMT_BOUNDS_H

#include "INSMT_global.h"
#include "IMT_Vector.h"
#include "IMT_Matrix.h"

#define BORDAS_PLANO_TOPO       0
#define BORDAS_PLANO_ABAIXO     1
#define BORDAS_PLANO_ESQUERDO   2
#define BORDAS_PLANO_DIREITO    3
#define BORDAS_PLANO_FRENTE     4
#define BORDAS_PLANO_ATRAS      5

/************************************************************/
/************************************************************/
class INSMT_EXPORT CIMTBoundingBox
{
public:

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTBoundingBox(                              );
    CIMTBoundingBox( const CIMTBoundingBox & copy );

    CIMTBoundingBox( const CIMTVector& vecMin,
                     const CIMTVector& vecMax );
    CIMTBoundingBox( float xIMT_MinVetorBorda,
                     float yIMT_MinVetorBorda,
                     float zIMT_MinVetorBorda,
                     float xIMT_MaxVetorBorda,
                     float yIMT_MaxVetorBorda,
                     float zIMT_MaxVetorBorda );

    //------------------------------------------------------------
    //Bounding Box Data
    //------------------------------------------------------------
    CIMTVector        IMT_MinBound;
    CIMTVector        IMT_MaxBound;
    float             IMT_HalfDim ;

    //------------------------------------------------------------
    //Data Collection Functions
    //------------------------------------------------------------
    CIMTVector       GetDimension     (                       ) const;
    CIMTVector       GetCenter        (                       ) const;
    CIMTPlane        GetPlane         ( unsigned long Side    ) const;


    CIMTVector       Transform        (CIMTMatrix     pIMT_Mtx);



    CIMTBoundingBox&      MeshBounds ( const CIMTVector pVertices[],
                                           unsigned long VertexCount ,
                                           unsigned long VertexStride,
                                           bool bReset = true );

    CIMTBoundingBox&      PointBounds( const CIMTVector pPos,
                                       const float     pDimensao,
                                       bool            bReset = true );

    bool            InsideBounds ( const CIMTVector& Point           ) const;

    bool            InsideBounds ( const CIMTVector& Point                  ,
                                       const CIMTVector& Tolerance       ) const;

    bool            CrossingRay  ( const CIMTVector& RayStart,
                                   const CIMTVector& RayDir,
                                   CIMTVector * pIntersection = NULL ) const;

    bool            CrossingRay  ( const CIMTVector& RayStart ,
                                   const CIMTVector& RayDir   ,
                                   const CIMTVector& Tolerance,
                                   CIMTVector * pIntersection = NULL ) const;

    bool            CrossingBounds  ( const CIMTBoundingBox& Borda           ) const;
    bool            CrossingBounds  ( const CIMTBoundingBox& Borda                 ,
                                      const CIMTVector& Tolerance       ) const;

    bool            CrossingSphere ( const CIMTBoundingBox& Borda           ) const;
    bool            CrossingSphere ( const CIMTBoundingBox& Borda                 ,
                                     float pIMT_TimeElapsed           ) const;

    void            RealProof      (                                  )      ;
    void            Clear          (                                  )      ;

    float           Diff           (float a, float b                  )      ;


    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTBoundingBox& operator  = ( const CIMTBoundingBox& opr );
    CIMTBoundingBox& operator += ( const CIMTVector& vecShift );
    CIMTBoundingBox& operator -= ( const CIMTVector& vecShift );

};
#endif // IMT_BOUNDS_H
