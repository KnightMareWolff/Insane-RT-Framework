/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IMT_Bounds.h"
#include "IMT_Plane.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBoundingBox::CIMTBoundingBox( )
{
    Clear();
}

CIMTBoundingBox::CIMTBoundingBox( const CIMTBoundingBox & copy )
{
    IMT_MinBound = copy.IMT_MinBound;
    IMT_MaxBound = copy.IMT_MaxBound;
    IMT_HalfDim  = copy.IMT_HalfDim ;
}

CIMTBoundingBox& CIMTBoundingBox::operator=  ( const CIMTBoundingBox& opr )
{
    IMT_MinBound = opr.IMT_MinBound;
    IMT_MaxBound = opr.IMT_MaxBound;
    IMT_HalfDim  = opr.IMT_HalfDim ;

    return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBoundingBox::CIMTBoundingBox( const CIMTVector& vecMin, const CIMTVector& vecMax )
{
    IMT_MinBound = vecMin;
    IMT_MaxBound = vecMax;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBoundingBox::CIMTBoundingBox( float xIMT_MinBound, float yIMT_MinBound, float zIMT_MinBound, float xIMT_MaxBound, float yIMT_MaxBound, float zIMT_MaxBound )
{
    IMT_MinBound = CIMTVector( xIMT_MinBound, yIMT_MinBound, zIMT_MinBound );
    IMT_MaxBound = CIMTVector( xIMT_MaxBound, yIMT_MaxBound, zIMT_MaxBound );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CIMTBoundingBox::Clear()
{
    IMT_MinBound = CIMTVector(  9999999,  9999999,  9999999 );
    IMT_MaxBound = CIMTVector( -9999999, -9999999, -9999999 );
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTVector CIMTBoundingBox::GetDimension() const
{
    return IMT_MaxBound - IMT_MinBound;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTVector CIMTBoundingBox::GetCenter() const
{
    return (IMT_MaxBound + IMT_MinBound) / 2;
}

/***************************************************************/
/*Transforma os vetores do volume e retorna o centro atualizado*/
/***************************************************************/
CIMTVector CIMTBoundingBox::Transform(CIMTMatrix pIMT_Mtx)
{
    IMT_MaxBound = IMT_MaxBound * pIMT_Mtx;
    IMT_MinBound = IMT_MinBound * pIMT_Mtx;

    return (IMT_MaxBound + IMT_MinBound) / 2;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTPlane CIMTBoundingBox::GetPlane(unsigned long Side) const
{
    CIMTPlane BordaPlano;

    switch ( Side ) {
        case BORDAS_PLANO_TOPO:
            BordaPlano.IMT_PlaneNormal.y = 1;
            BordaPlano.IMT_PlaneDistance = IMT_MaxBound.Dot(BordaPlano.IMT_PlaneNormal);
            break;
        case BORDAS_PLANO_DIREITO:
            BordaPlano.IMT_PlaneNormal.x = 1;
            BordaPlano.IMT_PlaneDistance = IMT_MaxBound.Dot(BordaPlano.IMT_PlaneNormal);
            break;
        case BORDAS_PLANO_ATRAS:
            BordaPlano.IMT_PlaneNormal.z = 1;
            BordaPlano.IMT_PlaneDistance = IMT_MaxBound.Dot(BordaPlano.IMT_PlaneNormal);
            break;
        case BORDAS_PLANO_ABAIXO:
            BordaPlano.IMT_PlaneNormal.y = -1;
            BordaPlano.IMT_PlaneDistance = IMT_MinBound.Dot(BordaPlano.IMT_PlaneNormal);
            break;
        case BORDAS_PLANO_ESQUERDO:
            BordaPlano.IMT_PlaneNormal.x = -1;
            BordaPlano.IMT_PlaneDistance = IMT_MinBound.Dot(BordaPlano.IMT_PlaneNormal);
            break;
        case BORDAS_PLANO_FRENTE:
            BordaPlano.IMT_PlaneNormal.z = -1;
            BordaPlano.IMT_PlaneDistance = IMT_MinBound.Dot(BordaPlano.IMT_PlaneNormal);
            break;
    }

    return BordaPlano;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBoundingBox& CIMTBoundingBox::MeshBounds(const CIMTVector *pVertices, unsigned long VertexCount, unsigned long VertexStride, bool bReset)
{
    CIMTVector      * vtx;
    unsigned char  * pVerts  = (unsigned char*)pVertices;

    if ( !pVertices ) return *this;

    if ( bReset ) Clear();

    for ( unsigned long v = 0; v < VertexCount; v++, pVerts += VertexStride )
    {
        vtx = (CIMTVector*)pVerts;
        if ( vtx->x < IMT_MinBound.x ) IMT_MinBound.x = vtx->x;
        if ( vtx->y < IMT_MinBound.y ) IMT_MinBound.y = vtx->y;
        if ( vtx->z < IMT_MinBound.z ) IMT_MinBound.z = vtx->z;
        if ( vtx->x > IMT_MaxBound.x ) IMT_MaxBound.x = vtx->x;
        if ( vtx->y > IMT_MaxBound.y ) IMT_MaxBound.y = vtx->y;
        if ( vtx->z > IMT_MaxBound.z ) IMT_MaxBound.z = vtx->z;
    }

    RealProof();

    //Atribui o Raio de Volume
    IMT_HalfDim = GetDimension().x;

    return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBoundingBox& CIMTBoundingBox::PointBounds(const CIMTVector pPos, const float pDimensao, bool bReset)

{
    if ( bReset ) Clear();

    IMT_MinBound = CIMTVector(pPos + CIMTVector(-pDimensao,-pDimensao,-pDimensao));
    IMT_MaxBound = CIMTVector(pPos + CIMTVector( pDimensao, pDimensao, pDimensao));

    //Atribui o Raio de Volume
    IMT_HalfDim = pDimensao/2;

    return *this;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void CIMTBoundingBox::RealProof()
{
    float rTemp;
    if ( IMT_MaxBound.x < IMT_MinBound.x ) { rTemp = IMT_MaxBound.x; IMT_MaxBound.x = IMT_MinBound.x; IMT_MinBound.x = rTemp; }
    if ( IMT_MaxBound.y < IMT_MinBound.y ) { rTemp = IMT_MaxBound.y; IMT_MaxBound.y = IMT_MinBound.y; IMT_MinBound.y = rTemp; }
    if ( IMT_MaxBound.z < IMT_MinBound.z ) { rTemp = IMT_MaxBound.z; IMT_MaxBound.z = IMT_MinBound.z; IMT_MinBound.z = rTemp; }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::InsideBounds(const CIMTVector &Point) const
{
    if (Point.x < IMT_MinBound.x || Point.x > IMT_MaxBound.x) return false;
    if (Point.y < IMT_MinBound.y || Point.y > IMT_MaxBound.y) return false;
    if (Point.z < IMT_MinBound.z || Point.z > IMT_MaxBound.z) return false;
    return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::InsideBounds( const CIMTVector& Point, const CIMTVector& Tolerance ) const
{
    if (Point.x < IMT_MinBound.x - Tolerance.x || Point.x > IMT_MaxBound.x + Tolerance.x) return false;
    if (Point.y < IMT_MinBound.y - Tolerance.y || Point.y > IMT_MaxBound.y + Tolerance.y) return false;
    if (Point.z < IMT_MinBound.z - Tolerance.z || Point.z > IMT_MaxBound.z + Tolerance.z) return false;
    return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CIMTBoundingBox& CIMTBoundingBox::operator+= ( const CIMTVector& vecShift )
{
    IMT_MinBound += vecShift;
    IMT_MaxBound += vecShift;
    return *this;
}

float CIMTBoundingBox::Diff(float a, float b)
{
    if(a >= 0 && b >= 0)
    {
        if(a > b)
            return a-b;
        else
            return b-a;
    }
    if(a < 0 && b < 0)
    {
        if( a > b)
            return b-a;
        else
            return a-b;
    }
    if(a >= 0 && b < 0)
        return a-b;
    else
        return b-a;
}

//-----------------------------------------------------------------------------
// Name : CruzamentoRaio()
// Desc : Testa se a Borda é atingida por um Raio
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::CrossingRay(const CIMTVector &RayStart, const CIMTVector &RayDir, CIMTVector *pIntersection) const
{
    return CrossingRay( RayStart, RayDir, CIMTVector(0,0,0), pIntersection );
}

//-----------------------------------------------------------------------------
// Name : CruzamentoRaio()
// Desc : Testa se a Borda é atingida por um Raio co Margem de Tolerância
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::CrossingRay( const CIMTVector& RayStart, const CIMTVector& RayDir, const CIMTVector& Tolerance, CIMTVector * pIntersection) const
{
    bool Dentro = true;
    CIMTVector MaxT = CIMTVector( -1, -1, -1 );
    CIMTVector Intersection;

    // Procura Planos Candidatos.
    if ( RayStart.x < IMT_MinBound.x )
    {
        Intersection.x  = IMT_MinBound.x;
        Dentro          = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.x) MaxT.x = (IMT_MinBound.x - RayStart.x) / RayDir.x;
    }
    else if (RayStart.x > IMT_MaxBound.x)
    {
        Intersection.x  = IMT_MaxBound.x;
        Dentro		    = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.x) MaxT.x = (IMT_MaxBound.x - RayStart.x) / RayDir.x;
    }

    if ( RayStart.y < IMT_MinBound.y )
    {
        Intersection.y  = IMT_MinBound.y;
        Dentro          = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.y) MaxT.y = (IMT_MinBound.y - RayStart.y) / RayDir.y;
    }
    else if (RayStart.y > IMT_MaxBound.y)
    {
        Intersection.y  = IMT_MaxBound.y;
        Dentro		    = false;
        // Calcula T Dist para planos candidatos
        if ((unsigned long&)RayDir.y) MaxT.y = (IMT_MaxBound.y - RayStart.y) / RayDir.y;
    }

    if ( RayStart.z < IMT_MinBound.z )
    {
        Intersection.z = IMT_MinBound.z;
        Dentro          = false;
        // Calculate T Distances to candidate planes
        if ((unsigned long&)RayDir.z) MaxT.z = (IMT_MinBound.z - RayStart.z) / RayDir.z;
    }
    else if (RayStart.z > IMT_MaxBound.z)
    {
        Intersection.z = IMT_MaxBound.z;
        Dentro		    = false;
        // Calculate T distances to candidate planes
        if ((unsigned long&)RayDir.z) MaxT.z = (IMT_MaxBound.z - RayStart.z) / RayDir.z;
    }


    //O Raio Origem está dentro da Bounding Box
    if(Dentro) { if (pIntersection) *pIntersection = RayStart; return true; }

    //Pega o Maximo Valor T para escolha da interceccao
    float *Plane = &MaxT.x;
    if(MaxT.y > *Plane)	Plane = &MaxT.y;
    if(MaxT.z > *Plane)	Plane = &MaxT.z;

    //Checa o candidato final dentro da borda.
    if(((unsigned long&)Plane) & 0x80000000) return false;

    //Faz testes Finais
    if ( &MaxT.x != Plane )
    {
        Intersection.x = RayStart.x + *Plane * RayDir.x;

        if ( Intersection.x < IMT_MinBound.x - Tolerance.x ||
             Intersection.x > IMT_MaxBound.x + Tolerance.x ) return false;
    }
    if ( &MaxT.y != Plane )
    {
        Intersection.y = RayStart.y + *Plane * RayDir.y;
        if ( Intersection.y < IMT_MinBound.y - Tolerance.y ||
             Intersection.y > IMT_MaxBound.y + Tolerance.y ) return false;
    }
    if ( &MaxT.z != Plane )
    {
        Intersection.z = RayStart.z + *Plane * RayDir.z;
        if ( Intersection.z < IMT_MinBound.z - Tolerance.z ||
             Intersection.z > IMT_MaxBound.z + Tolerance.z ) return false;
    }

    //O Raio Atingiu a Borda, repassa o ponto de interceção...
    if (pIntersection) *pIntersection = Intersection;
    return true;
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoBorda()
// Desc : Testa a Intersecção de duas Bordas
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::CrossingBounds(const CIMTBoundingBox &Borda) const
{
    return (IMT_MinBound.x <= Borda.IMT_MaxBound.x) &&
           (IMT_MinBound.y <= Borda.IMT_MaxBound.y) &&
           (IMT_MinBound.z <= Borda.IMT_MaxBound.z) &&
           (IMT_MaxBound.x >= Borda.IMT_MinBound.x) &&
           (IMT_MaxBound.y >= Borda.IMT_MinBound.y) &&
           (IMT_MaxBound.z >= Borda.IMT_MinBound.z);
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoBorda()
// Desc : Testa a Intersecção de duas Bordas com um fator de Tolerância
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::CrossingBounds(const CIMTBoundingBox& Borda, const CIMTVector& Tolerance ) const
{
    return ((IMT_MinBound.x - Tolerance.x) <= (Borda.IMT_MaxBound.x + Tolerance.x)) &&
           ((IMT_MinBound.y - Tolerance.y) <= (Borda.IMT_MaxBound.y + Tolerance.y)) &&
           ((IMT_MinBound.z - Tolerance.z) <= (Borda.IMT_MaxBound.z + Tolerance.z)) &&
           ((IMT_MaxBound.x + Tolerance.x) >= (Borda.IMT_MinBound.x - Tolerance.x)) &&
           ((IMT_MaxBound.y + Tolerance.y) >= (Borda.IMT_MinBound.y - Tolerance.y)) &&
           ((IMT_MaxBound.z + Tolerance.z) >= (Borda.IMT_MinBound.z - Tolerance.z));
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoEsfera()
// Desc : Testa a Intersecção ESFERICA de duas Bordas
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::CrossingSphere(const CIMTBoundingBox &Borda) const
{
    CIMTVector   relPos = GetCenter() - Borda.GetCenter();

    float  dist = relPos.x * relPos.x +
                  relPos.y * relPos.y +
                  relPos.z * relPos.z;

    float  minDist = IMT_HalfDim + Borda.IMT_HalfDim;

    return dist <= minDist * minDist;
}

//-----------------------------------------------------------------------------
// Nome : CruzamentoEsfera()
// Desc : Testa a Intersecção ESFERICA de duas Bordas
//-----------------------------------------------------------------------------
bool CIMTBoundingBox::CrossingSphere( const CIMTBoundingBox& Borda ,
                                      float pIMT_TimeElapsed       ) const
{
    CIMTVector   relPos = GetCenter() - Borda.GetCenter();

    float  dist = relPos.x * relPos.x +
                  relPos.y * relPos.y +
                  relPos.z * relPos.z;

    float  minDist = IMT_HalfDim + Borda.IMT_HalfDim;

    return dist <= minDist * minDist;
}

