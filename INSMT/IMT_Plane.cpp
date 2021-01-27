/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMT_Plane.h"

/************************************************************/
/************************************************************/
CIMTPlane::CIMTPlane()
{
    IMT_PlaneNormal      = CIMTVector( 0.0f, 0.0f, 0.0f );
    IMT_PlaneDistance    = 0.0f;
}

/************************************************************/
/*Nome do Método      : CIMTPlane()                         */
/*                                                          */
/*Objetivo            : Construtor Alternativo da classe    */
/*                      CIMTPlane.                          */
/*                      Seu objetivo é possibilitar criar   */
/*                      um plano tendo em mãos a distância ,*/
/*                      e a normal.                         */
/************************************************************/
CIMTPlane::CIMTPlane( const CIMTVector& vecNormal, float fDistance )
{
    IMT_PlaneNormal       = vecNormal; IMT_PlaneNormal.Normalize();
    IMT_PlaneDistance    = fDistance;
}

/**************************************************************/
/*Nome do Método      : CIMTPlane()                           */
/*                                                            */
/*Objetivo            : Construtor Alternativo da classe      */
/*                      CIMTPlane.                            */
/*                      Seu objetivo é possibilitar criar     */
/*                      um plano tendo em mãos a posicao de , */
/*                      um vertice qualquer que esteja contido*/
/*                      em um poligono qualquer e sua normal. */
/**************************************************************/
CIMTPlane::CIMTPlane( const CIMTVector& vecNormal, const CIMTVector& vecPointOnPlane )
{
    IMT_PlaneNormal       = vecNormal;

    IMT_PlaneNormal.Normalize();

    IMT_PlaneDistance    = vecPointOnPlane.Dot(IMT_PlaneNormal);
}

/*************************************************************/
/*Nome do Método      : PegaPtoNoPlano()                     */
/*                                                           */
/*Objetivo            : Retorna um ponto que esteja no plano.*/
/*************************************************************/
CIMTVector CIMTPlane::GetPointOnPlane() const
{
    return IMT_PlaneNormal * IMT_PlaneDistance;
}

/********************************************************************/
/*Nome do Método      : ClassificaPonto()                           */
/*                                                                  */
/*Objetivo            : Classifica um ponto passado com relação     */
/*                      a este plano.                               */
/*                      Ele pode estar:                             */
/*                      Na frente , Atrás ou estar no mesmo plano   */
/*                                                                  */
/*Obs:                  Opcionalmente pode-se passar o endereço de  */
/*                      uma variável float caso queira obter não a- */
/*                      penas a posição com relação a este plano mas*/
/*                      também a que distância ele fica do plano... */
/********************************************************************/
CLASSIFICATION CIMTPlane::ClassifyPoint(const CIMTVector &vecPoint, float *Dist) const
{
    float result	= vecPoint.Dot(IMT_PlaneNormal) - IMT_PlaneDistance;
    if (Dist) *Dist = result;
    if ( result < -EPSILON ) return BACK;
    if ( result > EPSILON  ) return FRONT;
    return COPLANAR;
}

/********************************************************************/
/*Nome do Método      : ClassificaPoligono()                        */
/*                                                                  */
/*Objetivo            : Classifica um poligono passado com relação  */
/*                      a este plano.                               */
/*                      Ele pode estar:                             */
/*                      Na frente , Atrás ou estar no mesmo plano   */
/********************************************************************/
CLASSIFICATION CIMTPlane::ClassifyPolygon(const CIMTVector *pVertices, unsigned long VertexCount, unsigned long VertexStride) const
{
    unsigned char  *pVerts  = (unsigned char*)pVertices;
    unsigned long   Infront = 0, Behind = 0, OnPlane=0;
    float	        result  = 0;


    for ( unsigned long i = 0; i < VertexCount; i++, pVerts += VertexStride )
    {

        result = (*(CIMTVector*)pVerts).Dot( IMT_PlaneNormal ) - IMT_PlaneDistance;

        if (result > EPSILON )
        {
            //WDW
            Infront++;
        }
        else if (result < -EPSILON)
        {
            //WDW
            Behind++;
        }
        else
        {
            OnPlane++;
            Infront++;
            Behind++;
        }
    }


    if ( OnPlane == VertexCount ) return COPLANAR;
    if ( Behind  == VertexCount ) return BACK;
    if ( Infront == VertexCount ) return FRONT;
    return CROSSING;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
CLASSIFICATION CIMTPlane::ClassifyRay(const CIMTVector &Point1, const CIMTVector &Point2) const
{
    int		Infront = 0, Behind = 0, OnPlane=0;
    float	result  = 0;

    result = Point1.Dot( IMT_PlaneNormal ) - IMT_PlaneDistance;

    if (result > EPSILON ) {
        Infront++;
    } else if (result < -EPSILON) {
        Behind++;
    } else {
        OnPlane++;
        Infront++;
        Behind++;
    }

    result = Point2.Dot( IMT_PlaneNormal ) - IMT_PlaneDistance;

    if (result > EPSILON ) {
        Infront++;
    } else if (result < -EPSILON) {
        Behind++;
    } else {
        OnPlane++;
        Infront++;
        Behind++;
    }

    if ( OnPlane == 2 ) return COPLANAR;
    if ( Behind  == 2 ) return BACK;
    if ( Infront == 2 ) return FRONT;
    return CROSSING;
}


/*****************************************************************/
/*Nome do Método      : ClassificaEsfera()                       */
/*                                                               */
/*Objetivo            : Classifica uma esfera passada com relação*/
/*                      a este plano.                            */
/*                      Ele pode estar:                          */
/*                      Na frente , Atrás ...etc....             */
/*****************************************************************/
CLASSIFICATION CIMTPlane::ClassifySphere(const CIMTVector &i3dPosicao, float i3dRaio, float *i3dDistancia) const
{
    float d = -i3dPosicao.Dot(IMT_PlaneNormal);

    *i3dDistancia = (IMT_PlaneNormal.x * i3dPosicao.x +
                     IMT_PlaneNormal.y * i3dPosicao.y +
                     IMT_PlaneNormal.z * i3dPosicao.z +
                     d               );


    if(fabsf(*i3dDistancia) < i3dRaio)
        return CROSSING;

    else if(*i3dDistancia >= i3dRaio)
        return FRONT;

    return BACK;
}

/**********************************************************************/
/*Nome do Método      : CruzamentoRaio()                              */
/*                                                                    */
/*Objetivo            : Determina se este plano cruza uma deter-      */
/*                      minada reta ou não.                           */
/*                      opcionalmente pode-se passar uma variavel     */
/*                      float para se obter a porcentagem em que      */
/*                      ocorre a interseçao , ou seja um multipli     */
/*                      cador que pode ser utilizado em cjto com      */
/*                      outras variaveis para calculos em poligonos.  */
/*                      e também um vetor onde pode se obter o ponto  */
/*                      onde a intersecção ocorre...                  */
/**********************************************************************/
bool CIMTPlane::CrossingRay(const CIMTVector &RayStart, const CIMTVector &RayEnd, CIMTVector &Intersection, float *pPercentage) const
{
    CIMTVector    Direction, L1, Point;
    float       linelength, dist_from_plane;
    float       Percent;

    Direction.x = RayEnd.x - RayStart.x;
    Direction.y = RayEnd.y - RayStart.y;
    Direction.z = RayEnd.z - RayStart.z;

    linelength = Direction.Dot(IMT_PlaneNormal);
    if (fabsf( linelength ) < EPSILON ) return false;

    Point = GetPointOnPlane();
    L1.x = Point.x - RayStart.x;
    L1.y = Point.y - RayStart.y;
    L1.z = Point.z - RayStart.z;

    dist_from_plane = L1.Dot(IMT_PlaneNormal);

    Percent = dist_from_plane / linelength;

    if ( Percent < 0.0f || Percent > 1.0f ) return false;

    Intersection.x = RayStart.x + Direction.x * Percent;
    Intersection.y = RayStart.y + Direction.y * Percent;
    Intersection.z = RayStart.z + Direction.z * Percent;

    if( pPercentage ) *pPercentage = Percent;

    return true;
}

/**********************************************************************/
/*Nome do Método      : CruzamentoRaio()                              */
/*                                                                    */
/*Objetivo            : Determina se este plano cruza uma deter-      */
/*                      minada reta ou não.                           */
/*                      opcionalmente pode-se passar uma variavel     */
/*                      float para se obter a porcentagem em que      */
/*                      ocorre a interseçao , ou seja um multipli     */
/*                      cador que pode ser utilizado em cjto com      */
/*                      outras variaveis para calculos em poligonos.  */
/*                      e também um vetor onde pode se obter o ponto  */
/*                      onde a intersecção ocorre...                  */
/**********************************************************************/
bool CIMTPlane::CrossingRay( const CIMTVector& RayStart,  const CIMTVector& RayDir, float * Intervalo ) const
{
    float ProjRayLength = RayDir.Dot(IMT_PlaneNormal);

    if ( ProjRayLength > -1e-5f ) return false;


    float Distance = CIMTVector(RayStart - GetPointOnPlane()).Dot(IMT_PlaneNormal);

    *Intervalo = Distance / -ProjRayLength;

    if ( *Intervalo < 0.0f || *Intervalo > 1.0f ) return false;

    return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
bool CIMTPlane::SameDirection(const CIMTVector &vecNormal) const
{
    if ( fabsf((IMT_PlaneNormal.x - vecNormal.x) +
               (IMT_PlaneNormal.y - vecNormal.y) +
               (IMT_PlaneNormal.z - vecNormal.z)) < 0.1f) return true;

    return false;
}
