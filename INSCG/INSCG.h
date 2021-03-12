/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef INSCG_H
#define INSCG_H

#include "INSCG_global.h"

class INSCG_EXPORT INSCG
{
public:
    INSCG();

    bool BuildPoly(CIMTPolygon& pICG_Poly,const CIMTPlane& pICG_Plane , const CIMTBoundingBox& Bound);

    bool CreateCube   (CIMTMesh &pICG_Mesh, const CIMTVector& pICG_Center, const CIMTVector& pICG_Dimension);
    bool CreateSky    (CIMTMesh &pICG_Mesh, const CIMTVector& pICG_Center);
    bool CreateTerrain(CIMTMesh &pICG_Mesh, const CIMTVector& pICG_Center);

    bool CalcPlanarNormals(CIMTPolygon         &pICG_Poly                                      );
    bool CalcSmoothNormals(CIMTVertexBuffer    &pICG_VertexBuffer,const CIMTVector& pICG_Center);
    bool CalcTangents     (CIMTVertexBuffer    &pICG_VertexBuffer                              );
    bool CalcTerrainVerts (CIMTMesh            &pICG_Mesh                                      );
    bool InvertNormals    (CIMTVertexBuffer    &pICG_VertexBuffer                              );
    bool InvertFaces      (vector<CIMTPolygon> &pICG_faces                                     );

    bool AlignMeshBuffer   (CIMTMesh         &pICG_Mesh        );
    bool Triangulate       (CIMTVertexBuffer &pICG_VertexBuffer);
    bool TriangulateTerrain(CIMTMesh         &pICG_Mesh        );

    float GetNear(){return ICG_NearDistance;}
    float GetFar (){return ICG_FarDistance;}
    float Get_FOV(){return ICG_FOV;}

    void  SetNear(float pICG_NearDistance){ICG_NearDistance = pICG_NearDistance;}
    void  SetFar (float pICG_FarDistance ){ICG_FarDistance  = pICG_FarDistance;}
    void  Set_FOV(float pICG_FOV         ){ICG_FOV          = pICG_FOV;}

private:
    float ICG_NearDistance;
    float ICG_FarDistance;
    float ICG_FOV;
};

#endif // INSCG_H
