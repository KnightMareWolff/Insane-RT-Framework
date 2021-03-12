/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "INSCG.h"

INSCG::INSCG()
{
    ICG_NearDistance = 1.0f;
    ICG_FarDistance  = 90000000.0f;
    ICG_FOV          = 90.0f ;
}

bool INSCG::BuildPoly(CIMTPolygon& pICG_Poly,const CIMTPlane& pICG_Plane , const CIMTBoundingBox& Bound)
{
    CIMTVector CB, CP, U, V, A;

    //Get the center of the Bound volume
    CB = Bound.GetCenter();

    //Calculate de distance from the center to the Plane.
    float DistanceToPlane = CB.PlaneDistance( pICG_Plane );

    //Calculate the center of the Plane
    CP = CB + (pICG_Plane.IMT_PlaneNormal * -DistanceToPlane );

    //Calculate The Main Axe.
    A = CIMTVector(0.0f,0.0f,0.0f);
    if( fabs(pICG_Plane.IMT_PlaneNormal.y) > fabs(pICG_Plane.IMT_PlaneNormal.z) )
    {
        if( fabs(pICG_Plane.IMT_PlaneNormal.z)  < fabs(pICG_Plane.IMT_PlaneNormal.x) )
        {
            A.z = 1;
        }
        else
        {
            A.x = 1;
        }
    }
    else
    {
        if (fabs(pICG_Plane.IMT_PlaneNormal.y) <= fabs(pICG_Plane.IMT_PlaneNormal.x) )
        {
            A.y = 1;
        }
        else
        {
            A.x = 1;
        }
    }

    //Generate the UV Vectors
    U = A.Cross(pICG_Plane.IMT_PlaneNormal);
    V = U.Cross(pICG_Plane.IMT_PlaneNormal);
    U.Normalize();
    V.Normalize();

    float Length = (Bound.IMT_MaxBound  - CB).Length();

    //Scale the UV Vectors at the Half of Bound Diameter.
    U *= Length;
    V *= Length;

    CIMTVector P[4];
    P[0] = CP + U - V; // Bottom Right
    P[1] = CP + U + V; // Top Right
    P[2] = CP - U + V; // Top Left
    P[3] = CP - U - V; // Bottom Left

    //Initialize empty Vertexes
    pICG_Poly.IMT_VertexBuffer.Initialize( 4 );

    //Insert the Vertex positions and Normals(Planar Normal)
    for ( int i = 0; i < 4; i++)
    {
        pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i].SetPosition(P[i]);
        pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i].SetNormal(pICG_Plane.IMT_PlaneNormal);
    }

    //Brute Force certification of vertices on Plane...
    for ( int v = 0; v < 4; v++ )
    {
       float Resultado = pICG_Poly.IMT_VertexBuffer.IMT_Buffer[v].GetPosition().Dot(pICG_Plane.IMT_PlaneNormal) - pICG_Plane.IMT_PlaneDistance;

       CIMTVector tPos = pICG_Poly.IMT_VertexBuffer.IMT_Buffer[v].GetPosition();

       tPos+=(pICG_Plane.IMT_PlaneNormal * -Resultado);

       pICG_Poly.IMT_VertexBuffer.IMT_Buffer[v].SetPosition(tPos);
    }

    //Triangulate the Vertex Buffer
    Triangulate(pICG_Poly.IMT_VertexBuffer);

    return true;
}

bool INSCG::CreateCube (CIMTMesh &pICG_Mesh, const CIMTVector& pICG_Center, const CIMTVector& pICG_Dimension)
{
    CIMTVector   centro,dimensao,vertice0,vertice1,vertice2,vertice3;
    float        Altura,Largura,Profundidade;

    /***********************************/
    /*Fixando Dimensão e Centro        */
    /***********************************/
    centro   = pICG_Center;
    dimensao = pICG_Dimension;


    //Calcula o Diâmetro de cada dimensão do Cubo(x=Altura,y=Largura,z=Profundidade)
    Largura      = dimensao.x / 2.0f;
    Altura       = dimensao.y / 2.0f;
    Profundidade = dimensao.z / 2.0f;


    // Define vertices in counter-clockwise (CCW) order with normal pointing out
    // We dont know why, but we are creating an adittional face becouse we are lost the face 0 when we send
    // the Buffers to OpenGL...
    pICG_Mesh.Initialize(7);

    /*********************/
    /*Top Face (y = 1.0f)*/
    /*********************/
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.Initialize(4);

    vertice0 = CIMTVector(centro + CIMTVector(  Largura, Altura,  Profundidade));
    vertice1 = CIMTVector(centro + CIMTVector( -Largura, Altura,  Profundidade));
    vertice2 = CIMTVector(centro + CIMTVector( -Largura, Altura, -Profundidade));
    vertice3 = CIMTVector(centro + CIMTVector(  Largura, Altura, -Profundidade));

    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[0].SetPosition(vertice0);
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[1].SetPosition(vertice1);
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[2].SetPosition(vertice2);
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[3].SetPosition(vertice3);

    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[0].SetTexCoord(CIMTVector2(0,0));
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[1].SetTexCoord(CIMTVector2(1,0));
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[2].SetTexCoord(CIMTVector2(1,1));
    pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer.IMT_Buffer[3].SetTexCoord(CIMTVector2(0,1));

    Triangulate(pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer);
    CalcPlanarNormals(pICG_Mesh.IMT_Faces[6]);
    CalcSmoothNormals(pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer,centro);
    CalcTangents(pICG_Mesh.IMT_Faces[6].IMT_VertexBuffer);

    /*****************************/
    /*Bottom Face (y = -1.0f)    */
    /*****************************/
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.Initialize(4);

    vertice0 = CIMTVector(centro + CIMTVector(  Largura, -Altura,  Profundidade));
    vertice1 = CIMTVector(centro + CIMTVector( -Largura, -Altura,  Profundidade));
    vertice2 = CIMTVector(centro + CIMTVector( -Largura, -Altura, -Profundidade));
    vertice3 = CIMTVector(centro + CIMTVector(  Largura, -Altura, -Profundidade));

    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[0].SetPosition(vertice0);
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[1].SetPosition(vertice1);
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[2].SetPosition(vertice2);
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[3].SetPosition(vertice3);

    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[0].SetTexCoord(CIMTVector2(0,0));
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[1].SetTexCoord(CIMTVector2(1,0));
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[2].SetTexCoord(CIMTVector2(1,1));
    pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer.IMT_Buffer[3].SetTexCoord(CIMTVector2(0,1));

    Triangulate(pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer);
    CalcPlanarNormals(pICG_Mesh.IMT_Faces[1]);
    CalcSmoothNormals(pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer,centro);
    CalcTangents(pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer);

    /*****************************/
    /*Front face  (z = 1.0f)     */
    /*****************************/
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.Initialize(4);

    vertice0 = CIMTVector(centro + CIMTVector( Largura, Altura, Profundidade));
    vertice1 = CIMTVector(centro + CIMTVector(-Largura, Altura, Profundidade));
    vertice2 = CIMTVector(centro + CIMTVector(-Largura,-Altura, Profundidade));
    vertice3 = CIMTVector(centro + CIMTVector( Largura,-Altura, Profundidade));

    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[0].SetPosition(vertice0);
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[1].SetPosition(vertice1);
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[2].SetPosition(vertice2);
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[3].SetPosition(vertice3);

    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[0].SetTexCoord(CIMTVector2(0,0));
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[1].SetTexCoord(CIMTVector2(1,0));
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[2].SetTexCoord(CIMTVector2(1,1));
    pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer.IMT_Buffer[3].SetTexCoord(CIMTVector2(0,1));

    Triangulate(pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer);
    CalcPlanarNormals(pICG_Mesh.IMT_Faces[2]);
    CalcSmoothNormals(pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer,centro);
    CalcTangents(pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer);

    /*****************************/
    /*Back face (z = -1.0f)      */
    /*****************************/
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.Initialize(4);

    vertice0 = CIMTVector(centro + CIMTVector( Largura,-Altura,-Profundidade));
    vertice1 = CIMTVector(centro + CIMTVector(-Largura,-Altura,-Profundidade));
    vertice2 = CIMTVector(centro + CIMTVector(-Largura, Altura,-Profundidade));
    vertice3 = CIMTVector(centro + CIMTVector( Largura, Altura,-Profundidade));

    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[0].SetPosition(vertice0);
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[1].SetPosition(vertice1);
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[2].SetPosition(vertice2);
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[3].SetPosition(vertice3);

    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[0].SetTexCoord(CIMTVector2(0,0));
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[1].SetTexCoord(CIMTVector2(1,0));
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[2].SetTexCoord(CIMTVector2(1,1));
    pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer.IMT_Buffer[3].SetTexCoord(CIMTVector2(0,1));

    Triangulate(pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer);
    CalcPlanarNormals(pICG_Mesh.IMT_Faces[3]);
    CalcSmoothNormals(pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer,centro);
    CalcTangents(pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer);

    /*****************************/
    /*Left face (x = -1.0f)      */
    /*****************************/
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.Initialize(4);

    vertice0 = CIMTVector(centro + CIMTVector( -Largura, Altura, Profundidade));
    vertice1 = CIMTVector(centro + CIMTVector( -Largura, Altura,-Profundidade));
    vertice2 = CIMTVector(centro + CIMTVector( -Largura,-Altura,-Profundidade));
    vertice3 = CIMTVector(centro + CIMTVector( -Largura,-Altura, Profundidade));

    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[0].SetPosition(vertice0);
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[1].SetPosition(vertice1);
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[2].SetPosition(vertice2);
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[3].SetPosition(vertice3);

    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[0].SetTexCoord(CIMTVector2(0,0));
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[1].SetTexCoord(CIMTVector2(1,0));
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[2].SetTexCoord(CIMTVector2(1,1));
    pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer.IMT_Buffer[3].SetTexCoord(CIMTVector2(0,1));

    Triangulate(pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer);
    CalcPlanarNormals(pICG_Mesh.IMT_Faces[4]);
    CalcSmoothNormals(pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer,centro);
    CalcTangents(pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer);

    /*****************************/
    /*Right face (x = 1.0f)      */
    /*****************************/
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.Initialize(4);

    vertice0 = CIMTVector(centro + CIMTVector( Largura, Altura, -Profundidade));
    vertice1 = CIMTVector(centro + CIMTVector( Largura, Altura,  Profundidade));
    vertice2 = CIMTVector(centro + CIMTVector( Largura,-Altura,  Profundidade));
    vertice3 = CIMTVector(centro + CIMTVector( Largura,-Altura, -Profundidade));

    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[0].SetPosition(vertice0);
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[1].SetPosition(vertice1);
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[2].SetPosition(vertice2);
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[3].SetPosition(vertice3);

    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[0].SetTexCoord(CIMTVector2(0,0));
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[1].SetTexCoord(CIMTVector2(1,0));
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[2].SetTexCoord(CIMTVector2(1,1));
    pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer.IMT_Buffer[3].SetTexCoord(CIMTVector2(0,1));

    Triangulate(pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer);
    CalcPlanarNormals(pICG_Mesh.IMT_Faces[5]);
    CalcSmoothNormals(pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer,centro);
    CalcTangents(pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer);

    pICG_Mesh.IMT_Type = IMT_MESH_TYPE_FACETED;

    return true;
}

bool INSCG::CreateSky(CIMTMesh &pICG_Mesh, const CIMTVector& pICG_Center)
{
    CreateCube(pICG_Mesh,pICG_Center,CIMTVector((ICG_FarDistance/2),(ICG_FarDistance/2),(ICG_FarDistance/2)));
    //top
    InvertNormals(pICG_Mesh.IMT_Faces[0].IMT_VertexBuffer);
    InvertNormals(pICG_Mesh.IMT_Faces[1].IMT_VertexBuffer);
    InvertNormals(pICG_Mesh.IMT_Faces[2].IMT_VertexBuffer);
    InvertNormals(pICG_Mesh.IMT_Faces[3].IMT_VertexBuffer);
    InvertNormals(pICG_Mesh.IMT_Faces[4].IMT_VertexBuffer);
    InvertNormals(pICG_Mesh.IMT_Faces[5].IMT_VertexBuffer);

    return true;
}

bool INSCG::CreateTerrain(CIMTMesh &pICG_Mesh, const CIMTVector &pICG_Center)
{
    CIMTGrid tICGGrid = CIMTGrid(512);

    pICG_Mesh.Initialize(tICGGrid);

    CalcTerrainVerts(pICG_Mesh);
    TriangulateTerrain(pICG_Mesh);

    pICG_Mesh.IMT_Type = IMT_MESH_TYPE_SKINNED;
    return true;
}

bool INSCG::CalcTerrainVerts(CIMTMesh &pICG_Mesh)
{
    CIMTVertex*        pVertex   ;
    int                currVertex  = 0;
    int                size        = pICG_Mesh.IMT_Grid.Size();
    int                gridSpacing = pICG_Mesh.IMT_Grid.Quad();
    float              heightScale = pICG_Mesh.IMT_Grid.Scal();
    CIMTVector         normal;

    for (int z = 0; z < size; ++z)
    {
        for (int x = 0; x < size; ++x)
        {
            currVertex = z * size + x;

            pVertex = &pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[currVertex];

            pVertex->SetPosition(CIMTVector(static_cast<float>(z * gridSpacing),
                                            pICG_Mesh.IMT_Grid.GetTBufferValue(z, x) * heightScale,
                                            static_cast<float>(x * gridSpacing)));

            pICG_Mesh.IMT_Grid.GetTBufferNormal(z, x, normal);

            pVertex->SetNormal(normal);
            pVertex->SetTexCoord(CIMTVector2(static_cast<float>(z) / static_cast<float>(size),
                                             static_cast<float>(x) / static_cast<float>(size)));
        }
    }

    return true;
}

bool INSCG::TriangulateTerrain(CIMTMesh &pICG_Mesh)
{
    int size = pICG_Mesh.IMT_Grid.Size();

    unsigned int *pIndex = static_cast<unsigned int *>(&pICG_Mesh.IMT_VertexBuffer.IMT_Indices[0]);

    for (int z = 0; z < size - 1; ++z)
    {
        if (z % 2 == 0)
        {
            for (int x = 0; x < size; ++x)
            {
                *pIndex++ = x + z * size;
                *pIndex++ = x + (z + 1) * size;
            }

            // Add degenerate triangles to stitch strips together.
            *pIndex++ = (size - 1) + (z + 1) * size;
        }
        else
        {
            for (int x = size - 1; x >= 0; --x)
            {
                *pIndex++ = x + z * size;
                *pIndex++ = x + (z + 1) * size;
            }

            // Add degenerate triangles to stitch strips together.
            *pIndex++ = (z + 1) * size;
        }
    }

    return true;
}

bool INSCG::CalcPlanarNormals(CIMTPolygon  &pICG_Poly)
{
    CIMTVector  vSideA      ,
                vSideB      ,
                vBestSideA,
                vBestSideB,
                vNormal ;

    float       fBestAngle    ,
                fTempAngle;
    /******************************************/
    /*Inicializamos com um angulo absurdo     */
    /******************************************/
    fBestAngle=99999.0f;

    /******************************************/
    /*Realiza as verif. em todos os Vertices  */
    /******************************************/
    for ( uint i = 0; i < pICG_Poly.IMT_VertexBuffer.GetSize() - 2; i++ )
    {
        /******************************************/
        /*Cria os lados para o produto escalar    */
        /******************************************/
        vSideA = (CIMTVector(pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i+1].IMT_Position) - CIMTVector(pICG_Poly.IMT_VertexBuffer.IMT_Buffer[0].IMT_Position)).Normalize();
        vSideB = (CIMTVector(pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i+2].IMT_Position) - CIMTVector(pICG_Poly.IMT_VertexBuffer.IMT_Buffer[0].IMT_Position)).Normalize();

        /*******************************************/
        /*Realiza o produto escalar entre os   dois*/
        /*Lados e obtemos o angulo entre estes dois*/
        /*Lados                                    */
        /*******************************************/
        fTempAngle = fabsf(vSideA.Dot(vSideB));

        /********************************************/
        /*Quanto menor o angulo entre eles Melhor...*/
        /********************************************/
        if ( fTempAngle < fBestAngle)
        {
            fBestAngle = fTempAngle;
            vBestSideA  = vSideA;
            vBestSideB  = vSideB;
        }
    }
    /*************************************************/
    /*Cross the best vector to obtain the poly normal*/
    /*************************************************/
    vNormal = vBestSideA.Cross(vBestSideB);
    vNormal.Normalize();

    /******************************************/
    /*Update Buffer Vertexes                  */
    /******************************************/
    for ( uint i = 0; i < pICG_Poly.IMT_VertexBuffer.GetSize() ; i++ )
    {
       pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i].IMT_Normal[0] = vNormal.x;
       pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i].IMT_Normal[1] = vNormal.y;
       pICG_Poly.IMT_VertexBuffer.IMT_Buffer[i].IMT_Normal[2] = vNormal.z;
    }


    return true;
}
bool INSCG::CalcSmoothNormals(CIMTVertexBuffer &pICG_VertexBuffer,const CIMTVector& pICG_Center)
{
    /************************************************************/
    /*Calculate the Normal based on the provided object center  */
    /*Take care with convex objects! for them an average planar */
    /*sum will work better...                                   */
    /************************************************************/
    for ( uint i = 0; i < pICG_VertexBuffer.GetSize(); i++ )
    {
        CIMTVector   vNormal ;
        vNormal = ( pICG_Center - pICG_VertexBuffer.IMT_Buffer[i].GetPosition()).Normalize();
        pICG_VertexBuffer.IMT_Buffer[i].SetSmooth( -vNormal );
    }

    return true;
}

bool INSCG::InvertNormals(CIMTVertexBuffer &pICG_VertexBuffer)
{
    std::reverse(pICG_VertexBuffer.IMT_Buffer.begin(), pICG_VertexBuffer.IMT_Buffer.end());
    return true;
}

bool INSCG::InvertFaces(vector<CIMTPolygon> &pICG_faces)
{
    std::reverse(pICG_faces.begin(), pICG_faces.end());
    return true;
}

bool INSCG::CalcTangents(CIMTVertexBuffer &pICG_VertexBuffer)
{
    CIMTVector  V0, V1, V2;
    CIMTVector2 UV0,UV1,UV2;

    for ( uint i = 0; i < pICG_VertexBuffer.IMT_Indices.size(); i+=3 )
    {
        V0 = pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+0]].GetPosition();
        V1 = pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+1]].GetPosition();
        V2 = pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+2]].GetPosition();

        UV0 = CIMTVector2(pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+0]].IMT_TexCoord[0],
                          pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+0]].IMT_TexCoord[1]);

        UV1 = CIMTVector2(pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+1]].IMT_TexCoord[0],
                          pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+1]].IMT_TexCoord[1]);

        UV2 = CIMTVector2(pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+2]].IMT_TexCoord[0],
                          pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+2]].IMT_TexCoord[1]);

        CIMTVector deltaPos1 = V1-V0;
        CIMTVector deltaPos2 = V2-V0;

        CIMTVector2 deltaUV1 = UV1-UV0;
        CIMTVector2 deltaUV2 = UV2-UV0;

        float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

        CIMTVector tangente   = (deltaPos1 * deltaUV2.y   - deltaPos2 * deltaUV1.y)*r;
        CIMTVector bitangente = (deltaPos2 * deltaUV1.x   - deltaPos1 * deltaUV2.x)*r;

        pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+0]].SetTangent(tangente);
        pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+1]].SetTangent(tangente);
        pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+2]].SetTangent(tangente);

        pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+0]].SetBitangent( bitangente );
        pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+1]].SetBitangent( bitangente );
        pICG_VertexBuffer.IMT_Buffer[pICG_VertexBuffer.IMT_Indices[i+2]].SetBitangent( bitangente );

    }

    return true;
}

bool INSCG::Triangulate(CIMTVertexBuffer &pICG_VertexBuffer)
{
    uint  Index;
    uint  VertexA  ,
          VertexB  ,
          VertexC  ;

    for ( Index = 0; Index < (pICG_VertexBuffer.IMT_Indices.size()/3); Index++ )
    {
        if ( Index == 0 )
        {
            VertexA = Index;
            VertexB = Index+1;
            VertexC = Index+2;
        }
        else
        {
              VertexB   = VertexC;
              VertexC++          ;
        }

        pICG_VertexBuffer.IMT_Indices[ Index*3   ]=VertexA;
        pICG_VertexBuffer.IMT_Indices[(Index*3)+1]=VertexB;
        pICG_VertexBuffer.IMT_Indices[(Index*3)+2]=VertexC;
    }

    return true;
}

bool INSCG::AlignMeshBuffer(CIMTMesh &pICG_Mesh)
{
    uint iBufferIndexSize =0,
         iBufferVertexSize=0;

    uint Index=0;

    /******************************************************/
    /*Calculate the total number of Vertexes and Indexes  */
    /******************************************************/
    for(uint i=0;i<pICG_Mesh.IMT_Faces.size();i++)
    {
        for(uint j=0;j<pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.GetSize();j++)
        {
           iBufferVertexSize++;
        }
        for(uint k=0;k<pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Indices.size();k++)
        {
           iBufferIndexSize++;
        }
    }

    /************************************/
    /*Initialize the Mesh Vertex Buffer */
    /************************************/
    pICG_Mesh.IMT_VertexBuffer.Initialize(iBufferVertexSize,iBufferIndexSize);

    /******************************************************/
    /*Preenche o vertex buffer comos vertices da aplicação*/
    /******************************************************/
    for(uint i=0;i<pICG_Mesh.IMT_Faces.size();i++)
    {
       for(uint j=0;j<pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.GetSize();j++)
       {
          pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[Index].SetPosition (pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetPosition());
          pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[Index].SetTexCoord (pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetTexCoord());
          pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[Index].SetNormal   (pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetNormal());
          pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[Index].SetSmooth   (pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetSmooth());
          pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[Index].SetTangent  (pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetTangent());
          pICG_Mesh.IMT_VertexBuffer.IMT_Buffer[Index].SetBitangent(pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetBitangent());

          pICG_Mesh.IMT_VertexBuffer.IMT_Feedback[Index] = pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Buffer[j].GetPosition();

          Index++;
       }
    }

    Index=0;//reset Indexer

    /*****************************************************************************************/
    /*The Indexes are processed separetely, since they differ in size compared with vertexes */
    /*****************************************************************************************/
    for(uint i=0;i<pICG_Mesh.IMT_Faces.size();i++)
    {
       for(uint j=0;j<pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Indices.size();j++)
       {
          //É recuperado aqui os indices originais da Skin
          pICG_Mesh.IMT_VertexBuffer.IMT_Indices[Index] = pICG_Mesh.IMT_Faces[i].IMT_VertexBuffer.IMT_Indices[j];
          Index++;
       }
    }

    //Clean up the Faces data , since they are aligned!
    pICG_Mesh.ClearFaces();

    return true;
}
