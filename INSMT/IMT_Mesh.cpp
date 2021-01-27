#include "IMT_Mesh.h"

CIMTMesh::CIMTMesh()
{

}

CIMTMesh::CIMTMesh( const CIMTMesh & copy )
{
    IMT_VertexBuffer = copy.IMT_VertexBuffer;
    IMT_Bound        = copy.IMT_Bound       ;
    IMT_Faces        = copy.IMT_Faces       ;
    IMT_Grid         = copy.IMT_Grid        ;
}

CIMTMesh& CIMTMesh::operator=  ( const CIMTMesh& opr )
{
    IMT_VertexBuffer = opr.IMT_VertexBuffer;
    IMT_Bound        = opr.IMT_Bound       ;
    IMT_Faces        = opr.IMT_Faces       ;
    IMT_Grid         = opr.IMT_Grid        ;
    return *this;
}

void CIMTMesh::Initialize(uint pIMT_NumberOfFaces)
{
    IMT_Faces  = vector<CIMTPolygon>(pIMT_NumberOfFaces ,CIMTPolygon());
}

void CIMTMesh::Initialize(CIMTGrid pIMT_Grid)
{
    int tICG_Tam              = pIMT_Grid.Size();
    int tICG_NumberOfVertices = (tICG_Tam * tICG_Tam);
    int tI3D_NumberOfIndices  = (tICG_Tam - 1) * (tICG_Tam * 2 + 1);

    IMT_Grid  = pIMT_Grid;
    IMT_VertexBuffer.Initialize(tICG_NumberOfVertices,tI3D_NumberOfIndices);
}

void CIMTMesh::ClearFaces()
{
    IMT_Faces.clear();
    IMT_Faces.shrink_to_fit();
}

