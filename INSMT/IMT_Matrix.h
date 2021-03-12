/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IMT_MATRIX_H
#define IMT_MATRIX_H

#include "INSMT_global.h"
#include "IMT_Vector.h"
#include "IMT_Plane.h"

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
#ifndef NULL
#define NULL 0
#endif

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class INSMT_EXPORT CIMTMatrix
{
public:

    //------------------------------------------------------------
    //------------------------------------------------------------
    CIMTMatrix( );
    CIMTMatrix( const CIMTMatrix& mtx );
    CIMTMatrix( float _m11, float _m12, float _m13, float _m14,
                float _m21, float _m22, float _m23, float _m24,
                float _m31, float _m32, float _m33, float _m34,
                float _m41, float _m42, float _m43, float _m44);

    //------------------------------------------------------------
    //------------------------------------------------------------
    float         Determinant() const;
    CIMTMatrix&   Zero();
    CIMTMatrix&   Identity();
    CIMTMatrix    GetInverse( float * pDeterminant = NULL ) const;
    CIMTMatrix&   Invert( float * pDeterminant = NULL );
    bool          IsIdentity() const;
    CIMTMatrix&   RotateAxis( const CIMTVector& vecAxis, const float& Angle, bool Reset = false );
    CIMTMatrix&   RotateX( const float& Angle, bool Reset = false );
    CIMTMatrix&   RotateX( const float& Angle, const CIMTVector& Origin,bool Reset = false );
    CIMTMatrix&   RotateY( const float& Angle, bool Reset = false );
    CIMTMatrix&   RotateY( const float& Angle, const CIMTVector& Origin,bool Reset = false );
    CIMTMatrix&   RotateZ( const float& Angle, bool Reset = false );
    CIMTMatrix&   RotateZ( const float& Angle, const CIMTVector& Origin,bool Reset = false );
    CIMTMatrix&   Rotate( const float& Yaw, const float& Pitch, const float& Roll, bool Reset = false );
    CIMTMatrix&   Scale( const float& X, const float& Y, const float& Z, bool Reset = false );
    CIMTMatrix&   Scale( const float& X, const float& Y, const float& Z, const CIMTVector& Origin, bool Reset = false );
    CIMTMatrix&   Translate( const float& X, const float& Y, const float& Z, bool Reset = false );
    CIMTMatrix&   Transpose( );

    bool          SetViewLH  ( const CIMTVector& vecPos, const CIMTVector& vecLookDir, const CIMTVector& vecUpDir, const CIMTVector& vecRightDir );
    bool          SetLookAtLH( const CIMTVector& vecPos, const CIMTVector& vecLookAt, const CIMTVector& vecUp );
    bool          SetLookAtRH( const CIMTVector& vecPos, const CIMTVector& vecLookAt, const CIMTVector& vecUp );
    bool          SetOrthoLH ( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetOrthoRH ( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetOrthoOffCenterLH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetOrthoOffCenterRH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveFovLH( const float& FovY, const float& Aspect, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveFovRH( const float& FovY, const float& Aspect, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveLH( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveRH( const float& Width, const float& Height, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveOffCenterLH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetPerspectiveOffCenterRH( const float& Left, const float& Right, const float& Bottom, const float& Top, const float& NearPlane, const float& FarPlane );
    bool          SetReflect( const CIMTPlane& Plane );
    bool          SetShadow( const CIMTVector4& Light, const CIMTPlane& Plane );


    //------------------------------------------------------------
    //------------------------------------------------------------
    static const CIMTMatrix& GetIdentity();

    //------------------------------------------------------------
    //------------------------------------------------------------
    float&          operator() (int iRow, int iColumn) ;
    float           operator() (int iRow, int iColumn) const;
    CIMTMatrix      operator*  (const CIMTMatrix & mtx ) const;
    CIMTMatrix      operator+  (const CIMTMatrix & mtx ) const;
    CIMTMatrix      operator-  (const CIMTMatrix & mtx ) const;
    CIMTMatrix      operator/  (const float& Value   ) const;
    CIMTMatrix      operator*  (const float& Value   ) const;
    CIMTMatrix&     operator*= (const CIMTMatrix & mtx );
    CIMTMatrix&     operator+= (const CIMTMatrix & mtx );
    CIMTMatrix&     operator-= (const CIMTMatrix & mtx );
    CIMTMatrix&     operator/= (const float & Value  );
    CIMTMatrix&     operator*= (const float & Value  );
    CIMTMatrix      operator-  () const;
    CIMTMatrix      operator+  () const;
    bool            operator== (const CIMTMatrix & mtx ) const;
    bool            operator!= (const CIMTMatrix & mtx ) const;
                    operator const float* () const;
                    operator       float* ();

    //------------------------------------------------------------
    //------------------------------------------------------------
    friend CIMTMatrix operator* (float Value, const CIMTMatrix& mtx);

    //------------------------------------------------------------
    //------------------------------------------------------------
    union  {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;
        };
        float m[4][4];
    };

private:
    //------------------------------------------------------------
    //------------------------------------------------------------
    static float CalculateDeterminant3( float _11, float _12, float _13, float _21, float _22, float _23, float _31, float _32, float _33);

    //------------------------------------------------------------
    //------------------------------------------------------------
    static CIMTMatrix     m_mtxStaticIdentity;

};

#endif // IMT_MATRIX_H
