/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IMT_VECTOR_H
#define IMT_VECTOR_H

#include "INSMT_global.h"

class CIMTPlane;
class CIMTMatrix;

class INSMT_EXPORT CIMTVector2
{
public:

    CIMTVector2( ) { }
    CIMTVector2( const CIMTVector2 & vec ) {x = vec.x; y = vec.y; }
    CIMTVector2( float _x, float _y ) { x = _x; y = _y; }

    CIMTVector2  operator-  ( const CIMTVector2& vec ) const;

    union {
        struct {
            float    x;
            float    y;
        };
        float v[2];
    };
};

class INSMT_EXPORT CIMTVector4
{
public:

    CIMTVector4( );
    CIMTVector4( const CIMTVector4 & vec );
    CIMTVector4( float _x, float _y, float _z, float _w);

    union {
        struct {
            float    x;
            float    y;
            float    z;
            float    w;
        };
        float v[4];
    };

    bool                IsEmpty() const;
    bool                SetBaryCentric( const CIMTVector4& V1, const CIMTVector4& V2, const CIMTVector4& V3, const float& f, const float& g );
    bool                SetCatmullRom( const CIMTVector4& V1, const CIMTVector4& V2, const CIMTVector4& V3, const CIMTVector4& V4, const float& s );
    bool                SetHermite( const CIMTVector4& V1, const CIMTVector4& T1, const CIMTVector4& V2, const CIMTVector4& T2, const float& s );
    CIMTVector4         Lerp( const CIMTVector4& V1, const float& s ) const;
    CIMTVector4         Maximize( const CIMTVector4& V1 ) const;
    CIMTVector4         Minimize( const CIMTVector4& V1 ) const;
    CIMTVector4&        Scale( const float &Scale );
    CIMTVector4         Cross( const CIMTVector4& V1, const CIMTVector4& V2 ) const;
    float               Dot( const CIMTVector4& vec ) const;
    float               Length() const;
    float               SquareLength() const;
    CIMTVector4         Transform( const CIMTMatrix& mtx ) const;
    bool                FuzzyCompare( const CIMTVector4& vecCompare,  const float& Tolerance) const;
    CIMTVector4&        Normalize();

    CIMTVector4  operator+  ( const CIMTVector4& vec ) const;
    CIMTVector4  operator-  ( const CIMTVector4& vec ) const;
    CIMTVector4  operator*  ( const float& Value  ) const;
    CIMTVector4  operator/  ( const float& Value  ) const;

    CIMTVector4& operator+= ( const CIMTVector4& vec );
    CIMTVector4& operator-= ( const CIMTVector4& vec );
    CIMTVector4& operator/= ( const float& Value  );
    CIMTVector4& operator*= ( const float& Value  );

    CIMTVector4  operator+  () const;
    CIMTVector4  operator-  () const;
    CIMTVector4& operator=  ( const CIMTVector4& vec );
    bool      operator== ( const CIMTVector4& vec ) const;
    bool      operator!= ( const CIMTVector4& vec ) const;

    operator float * ();
    operator const float * () const;

    friend CIMTVector4 operator * (float Value, const CIMTVector4& vec );
};

class INSMT_EXPORT CIMTVector
{
public:

    CIMTVector( );
    CIMTVector( const CIMTVector & Vector    );
    CIMTVector( float _x, float _y, float _z );
    CIMTVector( float v[3] );

    union {
        struct {
            float    x;
            float    y;
            float    z;
        };
        float v[3];
    };

    bool                 SetBaryCentric ( const CIMTVector& V1, const CIMTVector& V2, const CIMTVector& V3, const float& f, const float& g );
    bool                 SetCatmullRom  ( const CIMTVector& V1, const CIMTVector& V2, const CIMTVector& V3, const CIMTVector& V4, const float& s );
    bool                 SetHermite     ( const CIMTVector& V1, const CIMTVector& T1, const CIMTVector& V2, const CIMTVector& T2, const float& s );
    CIMTVector           Lerp           ( const CIMTVector& V1, const float& s) const;
    CIMTVector           Maximize       ( const CIMTVector& V1   ) const;
    CIMTVector           Minimize       ( const CIMTVector& V1   ) const;
    CIMTVector&          Scale          ( const float &Scale    );
    CIMTVector4          Transform      ( const CIMTMatrix& mtx ) const;
    CIMTVector           TransformCoord ( const CIMTMatrix& mtx ) const;
    CIMTVector           TransformNormal( const CIMTMatrix& mtx ) const;

    bool                IsEmpty        (                                 ) const;
    CIMTVector          Cross          ( const CIMTVector& V1             ) const;
    float               Dot            ( const CIMTVector& Vector          ) const;
    float               Length         (                                 ) const;
    float               SquareLength   (                                 ) const;
    bool                FuzzyCompare   (const CIMTVector& VectorComparacao,
                                        const float& tolerancia          ) const;
    CIMTVector&         Normalize      (                                 )      ;
    float               Distance       (const CIMTVector& Vector           ) const;
    double              AngleBetween   (const CIMTVector& kbcVector        ) const;
    float               PlaneDistance  (const CIMTPlane& Plane           ) const;
    float               PlaneDistance  (const CIMTPlane& Plane   , const CIMTVector& Direction ) const;
    float               LineDistance   (const CIMTVector& vecStart, const CIMTVector& vecEnd    ) const;

    CIMTVector  operator+  ( const CIMTVector& Vector ) const;
    CIMTVector  operator-  ( const CIMTVector& Vector ) const;
    CIMTVector  operator*  ( const CIMTVector& Vector ) const;
    CIMTVector  operator*  ( const CIMTMatrix& mtx ) const;
    CIMTVector  operator*  ( const float& Valor  ) const;
    CIMTVector  operator/  ( const float& Valor  ) const;

    CIMTVector& operator+= ( const CIMTVector& Vector );
    CIMTVector& operator-= ( const CIMTVector& Vector );
    CIMTVector& operator/= ( const float& Valor  );
    CIMTVector& operator*= ( const CIMTMatrix& mtx );
    CIMTVector& operator*= ( const float& Valor  );

    CIMTVector  operator+  () const;
    CIMTVector  operator-  () const;
    CIMTVector& operator=  ( const CIMTVector& Vector );
    bool       operator== ( const CIMTVector& Vector ) const;
    bool       operator!= ( const CIMTVector& Vector ) const;

    operator float * ();
    operator const float * () const;

    friend CIMTVector operator * (float Valor, const CIMTVector& Vector );
};


#endif // IMT_VECTOR_H
