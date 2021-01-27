/**********************************************************************************/
/*Projeto             :Insane RT Framework                                           */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IMT_Vector.h"
#include "IMT_Plane.h"
#include "IMT_Matrix.h"


CIMTVector2 CIMTVector2::operator-  ( const CIMTVector2& vec ) const
{
    return CIMTVector2( x - vec.x, y - vec.y );
}
/*********************************************************************/
/*rotinas para Vector4                                                */
/*********************************************************************/
CIMTVector4::CIMTVector4( )
{
    // Reset required variables.
    x = 0.0f; y = 0.0f; z = 0.0f; w = 1.0f;
}

CIMTVector4::CIMTVector4( const CIMTVector4 & vec )
{
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
}

CIMTVector4::CIMTVector4( float _x, float _y, float _z, float _w)
{
    x = _x; y = _y; z = _z; w = _w;
}


CIMTVector4::operator float * ()
{
    return (float*)&x;
}

CIMTVector4::operator const float * () const
{
    return (const float*)&x;
}

CIMTVector4 CIMTVector4::operator+  () const
{
    return *this;
}

CIMTVector4 CIMTVector4::operator-  () const
{
    return CIMTVector4( -x, -y, -z, -w );
}

CIMTVector4& CIMTVector4::operator+= ( const CIMTVector4& vec )
{
    x += vec.x; y += vec.y; z += vec.z; w += vec.w;
    return *this;
}

CIMTVector4& CIMTVector4::operator-= ( const CIMTVector4& vec )
{
    x -= vec.x; y -= vec.y; z -= vec.z; w -= vec.w;
    return *this;
}

CIMTVector4& CIMTVector4::operator*= ( const float& Value  )
{
    x *= Value; y *= Value; z *= Value; w *= Value;
    return *this;
}

CIMTVector4& CIMTVector4::operator/= ( const float& Value  )
{
    float fValue = 1.0f / Value;
    x *= fValue; y *= fValue; z *= fValue; w *= fValue;
    return *this;
}

CIMTVector4 CIMTVector4::operator+  ( const CIMTVector4& vec ) const
{
    return CIMTVector4( x + vec.x, y + vec.y, z + vec.z, w + vec.w );
}

CIMTVector4 CIMTVector4::operator-  ( const CIMTVector4& vec ) const
{
    return CIMTVector4( x - vec.x, y - vec.y, z - vec.z, w - vec.w );
}

CIMTVector4 CIMTVector4::operator*  ( const float& Value  ) const
{
    return CIMTVector4( x * Value, y * Value, z * Value, w * Value );
}

CIMTVector4 CIMTVector4::operator/  ( const float& Value  ) const
{
    float fValue = 1.0f / Value;
    return CIMTVector4( x * fValue, y * fValue, z * fValue, w * fValue );
}

CIMTVector4& CIMTVector4::operator=  ( const CIMTVector4& vec )
{
    x = vec.x; y = vec.y; z = vec.z; w = vec.w;
    return *this;
}

bool CIMTVector4::operator== ( const CIMTVector4& vec ) const
{
    return (x == vec.x) && (y == vec.y) && (z == vec.z) && (w == vec.w);
}

bool CIMTVector4::operator!= ( const CIMTVector4& vec ) const
{
    return (x != vec.x) || (y != vec.y) || (z != vec.z) || (w != vec.w);
}

CIMTVector4 operator * (float Value, const CIMTVector4& vec )
{
    return CIMTVector4( vec.x * Value, vec.y * Value, vec.z * Value, vec.w * Value );
}

bool CIMTVector4::IsEmpty() const
{
    return (x == 0.0f) && (y == 0.0f) && (z == 0.0f) && (w == 0.0f);
}

bool CIMTVector4::SetBaryCentric( const CIMTVector4& V1, const CIMTVector4& V2, const CIMTVector4& V3, const float& f, const float& g )
{
    x = V1.x + f * (V2.x - V1.x) + g * (V3.x - V1.x);
    y = V1.y + f * (V2.y - V1.y) + g * (V3.y - V1.y);
    z = V1.z + f * (V2.z - V1.z) + g * (V3.z - V1.z);
    w = V1.w + f * (V2.w - V1.w) + g * (V3.w - V1.w);

    return true;
}

bool CIMTVector4::SetCatmullRom( const CIMTVector4& V1, const CIMTVector4& V2, const CIMTVector4& V3, const CIMTVector4& V4, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a = -0.5f * sss + ss - 0.5f * s;
    b =  1.5f * sss - 2.5f * ss + 1.0f;
    c = -1.5f * sss + 2.0f * ss + 0.5f * s;
    d =  0.5f * sss - 0.5f * ss;

    x = a * V1.x + b * V2.x + c * V3.x + d * V4.x;
    y = a * V1.y + b * V2.y + c * V3.y + d * V4.y;
    z = a * V1.z + b * V2.z + c * V3.z + d * V4.z;
    w = a * V1.w + b * V2.w + c * V3.w + d * V4.w;

    return true;
}

bool CIMTVector4::SetHermite( const CIMTVector4& V1, const CIMTVector4& T1, const CIMTVector4& V2, const CIMTVector4& T2, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a =  2.0f * sss - 3.0f * ss + 1.0f;
    b = -2.0f * sss + 3.0f * ss;
    c =  sss - 2.0f * ss + s;
    d =  sss - ss;

    x = a * V1.x + b * V2.x + c * T1.x + d * T2.x;
    y = a * V1.y + b * V2.y + c * T1.y + d * T2.y;
    z = a * V1.z + b * V2.z + c * T1.z + d * T2.z;
    w = a * V1.w + b * V2.w + c * T1.w + d * T2.w;

    return true;
}
CIMTVector4 CIMTVector4::Lerp( const CIMTVector4& V1, const float& s ) const
{
    return CIMTVector4( x + s * (V1.x - x), y + s * (V1.y - y), z + s * (V1.z - z), w + s * (V1.w - w));
}

CIMTVector4 CIMTVector4::Maximize( const CIMTVector4& V1 ) const
{
    return CIMTVector4( (x > V1.x) ? x : V1.x, (y > V1.y) ? y : V1.y, (z > V1.z) ? z : V1.z, (w > V1.w) ? w : V1.w );
}

CIMTVector4 CIMTVector4::Minimize( const CIMTVector4& V1 ) const
{
    return CIMTVector4( (x < V1.x) ? x : V1.x, (y < V1.y) ? y : V1.y, (z < V1.z) ? z : V1.z, (w < V1.w) ? w : V1.w );
}

CIMTVector4& CIMTVector4::Scale( const float &Scale )
{
    x *= Scale; y *= Scale; z *= Scale; w *= Scale;
    return *this;
}

CIMTVector4 CIMTVector4::Cross( const CIMTVector4& V1, const CIMTVector4& V2 ) const
{
    float   a, b, c, d, e, f;

    a = V1.x * V2.y - V1.y * V2.x;
    b = V1.x * V2.z - V1.z * V2.x;
    c = V1.x * V2.w - V1.w * V2.x;
    d = V1.y * V2.z - V1.z * V2.y;
    e = V1.y * V2.w - V1.w * V2.y;
    f = V1.z * V2.w - V1.w * V2.z;

    return CIMTVector4( ( f * y - e * z + d * w),
                     (-f * x - c * z + b * w),
                     ( e * x - c * y + a * w),
                     (-d * x - b * y + a * z));
}

float CIMTVector4::Dot( const CIMTVector4& vec ) const
{
    return x * vec.x + y * vec.y + z * vec.z + w * vec.w;
}

float CIMTVector4::Length() const
{
    return sqrtf(x * x + y * y + z * z + w * w);
}

float CIMTVector4::SquareLength() const
{
    return x * x + y * y + z * z + w * w;
}

CIMTVector4 CIMTVector4::Transform( const CIMTMatrix& mtx ) const
{
    return CIMTVector4( x * mtx._11 + y * mtx._21 + z * mtx._31 + w * mtx._41,
                     x * mtx._12 + y * mtx._22 + z * mtx._32 + w * mtx._42,
                     x * mtx._13 + y * mtx._23 + z * mtx._33 + w * mtx._43,
                     x * mtx._14 + y * mtx._24 + z * mtx._34 + w * mtx._44 );
}

bool CIMTVector4::FuzzyCompare( const CIMTVector4& vecCompare,  const float& Tolerance) const
{
    if ( fabsf(x - vecCompare.x) > Tolerance ) return false;
    if ( fabsf(y - vecCompare.y) > Tolerance ) return false;
    if ( fabsf(z - vecCompare.z) > Tolerance ) return false;
    if ( fabsf(w - vecCompare.w) > Tolerance ) return false;
    return true;
}

CIMTVector4& CIMTVector4::Normalize()
{
    float   denom;

    denom = sqrtf(x * x + y * y + z * z + w * w);
    if (fabsf(denom) < 1e-5f) return *this;

    denom = 1.0f / denom;

    x *= denom;
    y *= denom;
    z *= denom;
    w *= denom;

    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector::CIMTVector( )
{
    // Reset required variables.
    x = 0.0f; y = 0.0f; z = 0.0f;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector::CIMTVector( const CIMTVector & Vector )
{
    x = Vector.x; y = Vector.y; z = Vector.z;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector::CIMTVector( float _x, float _y, float _z)
{
    x = _x; y = _y; z = _z;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector::CIMTVector( float v[3])
{
    x = v[0]; y = v[1]; z = v[2];
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector::operator float * ()
{
    return (float*)&x;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector::operator const float * () const
{
    return (const float*)&x;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator+  () const
{
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator-  () const
{
    return CIMTVector( -x, -y, -z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector& CIMTVector::operator+= ( const CIMTVector& Vector )
{
    x += Vector.x; y += Vector.y; z += Vector.z;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector& CIMTVector::operator-= ( const CIMTVector& Vector )
{
    x -= Vector.x; y -= Vector.y; z -= Vector.z;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector& CIMTVector::operator*= ( const float& Valor  )
{
    x *= Valor; y *= Valor; z *= Valor;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector& CIMTVector::operator/= ( const float& Valor  )
{
    float fValor = 1.0f / Valor;
    x *= fValor; y *= fValor; z *= fValor;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator+  ( const CIMTVector& Vector ) const
{
    return CIMTVector( x + Vector.x, y + Vector.y, z + Vector.z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator-  ( const CIMTVector& Vector ) const
{
    return CIMTVector( x - Vector.x, y - Vector.y, z - Vector.z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator*  ( const float& Valor  ) const
{
    return CIMTVector( x * Valor, y * Valor, z * Valor );
}


/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator*  ( const CIMTVector& Vector  ) const
{
    return CIMTVector( x * Vector.x, y * Vector.y, z * Vector.z );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::operator/  ( const float& Valor  ) const
{
    float fValor = 1.0f / Valor;
    return CIMTVector( x * fValor, y * fValor, z * fValor );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector& CIMTVector::operator=  ( const CIMTVector& Vector )
{
    x = Vector.x; y = Vector.y; z = Vector.z;
    return *this;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVector::operator== ( const CIMTVector& Vector ) const
{
    return (x == Vector.x) && (y == Vector.y) && (z == Vector.z);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVector::operator!= ( const CIMTVector& Vector ) const
{
    return (x != Vector.x) || (y != Vector.y) || (z != Vector.z);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector operator * (float Valor, const CIMTVector& Vector )
{
    return CIMTVector( Vector.x * Valor, Vector.y * Valor, Vector.z * Valor );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVector::IsEmpty() const
{
    return (x == 0.0f) && (y == 0.0f) && (z == 0.0f);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector CIMTVector::Cross( const CIMTVector& V1 ) const
{
    return CIMTVector( y * V1.z - z * V1.y ,
                      z * V1.x - x * V1.z ,
                      x * V1.y - y * V1.x );
}

/*************************************************************/
/*                                                           */
/*************************************************************/
float CIMTVector::Dot( const CIMTVector& Vector ) const
{
    return x * Vector.x + y * Vector.y + z * Vector.z;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
float CIMTVector::Length() const
{
    return sqrtf(x * x + y * y + z * z);
}

/*************************************************************/
/*                                                           */
/*************************************************************/
float CIMTVector::SquareLength() const
{
    return x * x + y * y + z * z;
}


/*************************************************************/
/*                                                           */
/*************************************************************/
bool CIMTVector::FuzzyCompare(const CIMTVector &VectorComparacao, const float &tolerancia) const
{
    if ( fabsf(x - VectorComparacao.x) >= tolerancia ) return false;
    if ( fabsf(y - VectorComparacao.y) >= tolerancia ) return false;
    if ( fabsf(z - VectorComparacao.z) >= tolerancia ) return false;
    return true;
}

/*************************************************************/
/*                                                           */
/*************************************************************/
CIMTVector& CIMTVector::Normalize()
{
    float   denom;

    denom = sqrtf(x * x + y * y + z * z);
    if (fabsf(denom) < 1e-5f) return *this;

    denom = 1.0f / denom;

    x *= denom;
    y *= denom;
    z *= denom;

    return *this;
}

/************************************************************/
/*Nome do Método    : AnguloEntre                           */
/*                                                          */
/*Objetivo          : Retorna o angulo entre este Vector e   */
/*                    outro Vector passado.                  */
/*                                                          */
/************************************************************/
double CIMTVector::AngleBetween(const CIMTVector &kbcVector) const
{

    float  kbcProdEsc = Dot(kbcVector);

    float  kbcMags    = Length() * kbcVector.Length();

    double kbcAngulo  = acos( kbcProdEsc / kbcMags );

    // Para ter certeza que não e angulo indefinido
    //if(_isnan(kbcAngulo))
    //    return 0;

    // retorna em radianos
    return( kbcAngulo );

}

/*************************************************************/
/*Nome do Método    : Distancia                              */
/*                                                           */
/*Objetivo          : Retorna a Distancia entre este Vector e */
/*                    um Vector passado                       */
/*                                                           */
/*************************************************************/
float CIMTVector::Distance(const CIMTVector& Vector) const
{
    return sqrt((Vector.x - x) * (Vector.x - x) +
                (Vector.y - y) * (Vector.y - y) +
                (Vector.z - z) * (Vector.z - z));

}

//-----------------------------------------------------------------------------
// Name : DistanceToPlane ()
// Desc : Calculates the Distance from the position stored in this vector, and
//        the plane passed to this function.
//-----------------------------------------------------------------------------
float CIMTVector::PlaneDistance(const CIMTPlane &Plane) const
{
    return Dot( Plane.IMT_PlaneNormal) - Plane.IMT_PlaneDistance;
}

//-----------------------------------------------------------------------------
// Name : DistanceToPlane ()
// Desc : Calculates the Distance from the position stored in this vector, and
//        the plane passed to this function, along a ray direction.
//-----------------------------------------------------------------------------
float CIMTVector::PlaneDistance( const CIMTPlane& Plane, const CIMTVector& Direction ) const
{
    float PlaneDistance = Dot( -Plane.IMT_PlaneNormal) - Plane.IMT_PlaneDistance;
    return PlaneDistance * (1 / (-Plane.IMT_PlaneNormal).Dot( Direction ));
}

//-----------------------------------------------------------------------------
// Name : DistanceToLine ()
// Desc : Calculates the distance from the position stored in this vector, and
//        the line segment passed into this function.
// Note : Returns a value that is out of range if the point is outside of the
//        extents of vecStart & vecEnd.
//-----------------------------------------------------------------------------
float CIMTVector::LineDistance(const CIMTVector &vecStart, const CIMTVector &vecEnd) const
{
    CIMTVector c, v;
    float     d, t;

    // Determine t
    // (the length of the vector from ‘vecStart’ to ‘this’)
    c = *this  - vecStart;
    v = vecEnd - vecStart;
    d = v.Length();

    v.Normalize();

    t = v.Dot( c );

    // Check to see if ‘t’ is beyond the extents of the line segment
    if (t < 0.01f)     return 99999.0f;
    if (t > d - 0.01f) return 99999.0f;

    // set length of v to t. v is normalized so this is easy
    v.x = vecStart.x + (v.x * t);
    v.y = vecStart.y + (v.y * t);
    v.z = vecStart.z + (v.z * t);

    // Return the distance
    return ((*this) - v).Length();
}

CIMTVector& CIMTVector::operator*= ( const CIMTMatrix& mtx )
{
    float   rhw, _x, _y, _z;

    rhw = (x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44);
    if (fabsf(rhw) < 1e-5f) { x = 0; y = 0; z = 0; return *this; }

    rhw = 1.0f / rhw;

    _x = rhw * (x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41);
    _y = rhw * (x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42);
    _z = rhw * (x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43);

    x = _x; y = _y; z = _z;

    return *this;
}

CIMTVector CIMTVector::operator*  ( const CIMTMatrix& mtx  ) const
{
    float   rhw;

    rhw = (x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44);
    if (fabsf(rhw) < 1e-5f) return CIMTVector( 0, 0, 0 );

    rhw = 1.0f / rhw;

    return CIMTVector( rhw * (x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41),
                     rhw * (x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42),
                     rhw * (x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43));
}


bool CIMTVector::SetBaryCentric( const CIMTVector& V1, const CIMTVector& V2, const CIMTVector& V3, const float& f, const float& g )
{
    x = V1.x + f * (V2.x - V1.x) + g * (V3.x - V1.x);
    y = V1.y + f * (V2.y - V1.y) + g * (V3.y - V1.y);
    z = V1.z + f * (V2.z - V1.z) + g * (V3.z - V1.z);

    return true;
}

bool CIMTVector::SetCatmullRom( const CIMTVector& V1, const CIMTVector& V2, const CIMTVector& V3, const CIMTVector& V4, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a = -0.5f * sss + ss - 0.5f * s;
    b =  1.5f * sss - 2.5f * ss + 1.0f;
    c = -1.5f * sss + 2.0f * ss + 0.5f * s;
    d =  0.5f * sss - 0.5f * ss;

    x = a * V1.x + b * V2.x + c * V3.x + d * V4.x;
    y = a * V1.y + b * V2.y + c * V3.y + d * V4.y;
    z = a * V1.z + b * V2.z + c * V3.z + d * V4.z;

    return true;
}

bool CIMTVector::SetHermite( const CIMTVector& V1, const CIMTVector& T1, const CIMTVector& V2, const CIMTVector& T2, const float& s )
{
    float   ss, sss, a, b, c, d;

    ss  = s * s;
    sss = s * ss;

    a =  2.0f * sss - 3.0f * ss + 1.0f;
    b = -2.0f * sss + 3.0f * ss;
    c =  sss - 2.0f * ss + s;
    d =  sss - ss;

    x = a * V1.x + b * V2.x + c * T1.x + d * T2.x;
    y = a * V1.y + b * V2.y + c * T1.y + d * T2.y;
    z = a * V1.z + b * V2.z + c * T1.z + d * T2.z;

    return true;
}
CIMTVector CIMTVector::Lerp( const CIMTVector& V1, const float& s ) const
{
    return CIMTVector( x + s * (V1.x - x), y + s * (V1.y - y), z + s * (V1.z - z) );
}

CIMTVector CIMTVector::Maximize( const CIMTVector& V1 ) const
{
    return CIMTVector( (x > V1.x) ? x : V1.x, (y > V1.y) ? y : V1.y, (z > V1.z) ? z : V1.z );
}

CIMTVector CIMTVector::Minimize( const CIMTVector& V1 ) const
{
    return CIMTVector( (x < V1.x) ? x : V1.x, (y < V1.y) ? y : V1.y, (z < V1.z) ? z : V1.z );
}

CIMTVector& CIMTVector::Scale( const float &Scale )
{
    x *= Scale; y *= Scale; z *= Scale;
    return *this;
}


CIMTVector4 CIMTVector::Transform( const CIMTMatrix& mtx ) const
{
    return CIMTVector4( x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41,
                       x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42,
                       x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43,
                       x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44 );
}

CIMTVector CIMTVector::TransformCoord( const CIMTMatrix& mtx ) const
{
    float   rhw;

    rhw = (x * mtx._14 + y * mtx._24 + z * mtx._34 + mtx._44);
    if (fabsf(rhw) < 1e-5f) return CIMTVector( 0, 0, 0 );

    rhw = 1.0f / rhw;

    return CIMTVector( rhw * (x * mtx._11 + y * mtx._21 + z * mtx._31 + mtx._41),
                       rhw * (x * mtx._12 + y * mtx._22 + z * mtx._32 + mtx._42),
                       rhw * (x * mtx._13 + y * mtx._23 + z * mtx._33 + mtx._43));
}

CIMTVector CIMTVector::TransformNormal( const CIMTMatrix& mtx ) const
{
    return CIMTVector( x * mtx._11 + y * mtx._21 + z * mtx._31,
                       x * mtx._12 + y * mtx._22 + z * mtx._32,
                       x * mtx._13 + y * mtx._23 + z * mtx._33 );
}
