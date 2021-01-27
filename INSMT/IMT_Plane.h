/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de CriaÃ§Ã£o     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/


#ifndef IMT_PLANE_H
#define IMT_PLANE_H

#include "INSMT_global.h"
#include "IMT_Vector.h"

//em caso de problemas incluir typedef...
enum CLASSIFICATION
{
       FRONT      = 1 ,
       BACK       = 2 ,
       COPLANAR   = 3 ,
       CROSSING   = 4
};

/************************************************************/
/************************************************************/
class INSMT_EXPORT CIMTPlane
{
public:
    //------------------------------------------------------------
    //------------------------------------------------------------
     CIMTPlane(                                             );
     CIMTPlane( const CIMTVector& vecNormal, float fDistance );
     CIMTPlane( const CIMTVector& vecNormal, const CIMTVector& vecPointOnPlane );

    //------------------------------------------------------------
    //------------------------------------------------------------
    CLASSIFICATION  ClassifyPolygon( const CIMTVector pVertices[] ,
                                       unsigned long VertexCount   ,
                                       unsigned long VertexStride  ) const;

    CLASSIFICATION  ClassifyPoint  ( const CIMTVector& vecPoint   ,
                                             float *    Dist =    0) const;

    CLASSIFICATION  ClassifyRay    ( const CIMTVector& Point1     ,
                                       const CIMTVector& Point2     ) const;

    CLASSIFICATION  ClassifySphere ( const CIMTVector& i3dPosicao ,
                                       float i3dRaio               ,
                                       float *i3dDistancia         ) const;

    CIMTVector      GetPointOnPlane(                             ) const;

    bool            CrossingRay    ( const CIMTVector& RayStart    ,
                                     const CIMTVector& RayEnd      ,
                                     CIMTVector& Intersection,
                                     float *    pPercentage =    0) const;

    bool            CrossingRay    ( const CIMTVector& RayStart    ,
                                     const CIMTVector& RayDir      ,
                                     float *          Intervalo   ) const;

    bool            SameDirection  ( const CIMTVector& vecNormal ) const;

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTVector      IMT_PlaneNormal;
    float           IMT_PlaneDistance;
};

#endif // IMT_PLANE_H
