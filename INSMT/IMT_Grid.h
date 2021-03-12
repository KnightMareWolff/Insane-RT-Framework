/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CIMTGRID_H
#define CIMTGRID_H

#include "INSMT_global.h"
#include "IMT_Vector.h"

class INSMT_EXPORT CIMTGrid
{
public:

   ~CIMTGrid(         );

    CIMTGrid(                      ){}
    CIMTGrid(uint    pIMT_MapSize  );
    CIMTGrid(QString pIMT_FileName );
    CIMTGrid(const CIMTGrid &grid  );

    CIMTGrid &operator=(const CIMTGrid& opr);

    void ApplyBoxFilter  (                );
    void ApplyBlurrFilter(float pIMT_Steps);

    float* GetTBuffer ();
    QImage GetColorMap();
    uint   GetTBufferIndex (uint  pIMT_X , uint  pIMT_Y                         );
    float  GetTBufferValue (uint  pIMT_X , uint  pIMT_Z                         );
    void   GetTBufferNormal(float pIMT_X , float pIMT_Z , CIMTVector &pIMT_Normal);

    cv::Mat    IMT_GridData; //Declared Public to Make possible CV change it in other components

    int    Rows(){return IMT_GridData.rows;}
    int    Cols(){return IMT_GridData.cols;}
    int    Size(){return IMT_MapSize;}
    int    Quad(){return IMT_QuadSize;}
    float  Scal(){return IMT_Scale;}

private:

    void   GenerateFractal(float pIMT_Roughness      );
    void   GenerateColors (                          );

    void   GetPixelNormal (float pIMT_X , float pIMT_Z , CIMTVector &pIMT_Normal);

    //Support Funcions
    long floatToLong(float f);
    float random(float min, float max);

    uint               IMT_MapSize ;
    uint               IMT_MapSizeX;
    uint               IMT_MapSizeY;
    uint               IMT_QuadSize;
    float              IMT_Scale   ;
    std::vector<float> IMT_TBuffer ;
    uint               IMT_GridType;
    float              IMT_ColorMap[16][3];//Tabela de Cores(Geracao automatica de textura).
};

template <typename T>
static T bilerp(const T &a, const T &b, const T &c, const T &d, float u, float v)
{
    // Performs a bilinear interpolation.
    //  P(u,v) = e + v(f - e)
    //
    //  where
    //  e = a + u(b - a)
    //  f = c + u(d - c)
    //  u in range [0,1]
    //  v in range [0,1]

    return a * ((1.0f - u) * (1.0f - v))
           + b * (u * (1.0f - v))
           + c * (v * (1.0f - u))
           + d * (u * v);
}

#endif // CIMTGRID_H
