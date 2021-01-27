#ifndef CIMTMESH_H
#define CIMTMESH_H

#include "IMT_Polygon.h"
#include "IMT_Grid.h"

class INSMT_EXPORT CIMTMesh
{
public:
    CIMTMesh();

    CIMTMesh( const CIMTMesh & copy );
    CIMTMesh& operator=  ( const CIMTMesh& opr );

    void Initialize(uint     pIMT_NumberOfFaces);
    void Initialize(CIMTGrid pIMT_Grid         );
    void ClearFaces(                           );

    vector<CIMTPolygon> IMT_Faces        ;//Auxiliary Polygons for Mesh Generation
    CIMTVertexBuffer    IMT_VertexBuffer ;//The resultant vertex buffer
    CIMTBoundingBox     IMT_Bound        ;//Boundary of the Polygon
    CIMTGrid            IMT_Grid         ;//The Grid Associated with the Mesh (Skinned Meshs)
    uint                IMT_Type         ;//Mesh Type (Faceted,Skinned)
};

#endif // CIMTMESH_H
