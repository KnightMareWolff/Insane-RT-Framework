#include "IMT_Grid.h"


CIMTGrid::~CIMTGrid()
{

}

CIMTGrid::CIMTGrid(uint pIMT_MapSize )
{
    IMT_GridType = IMT_GRID_TYPE_DEPTHMAP;

    //Inicializa parametros de construção
    IMT_Scale    = 1.0f;
    IMT_MapSizeX = pIMT_MapSize;
    IMT_MapSizeY = pIMT_MapSize;
    IMT_MapSize  = IMT_MapSizeX * IMT_MapSizeY;

    //Just Fix the size depending on the Grid Type(HeightMaps and ColorMaps Filters etc...Must have Power of Two Sizes.(Todo: Fix It!)
    if(IMT_GridType != IMT_GRID_TYPE_IMAGE)IMT_MapSize = IMT_MapSizeX;

    IMT_QuadSize = 1;

    //Aloca o tamanho do Transformation Buffer
    IMT_TBuffer.resize(IMT_MapSize * IMT_MapSize);

    //Zera as alturas para inicio.
    memset(&IMT_TBuffer[0],0, IMT_TBuffer.size());

    GenerateFractal(1.2f);
    GenerateColors();
}

CIMTGrid::CIMTGrid(QString pIMT_FileName)
{

    IMT_GridType = IMT_GRID_TYPE_IMAGE;

    //Carrega dados da Imagem(Por enquanto temos apenas imagem como fonte para dados. Ex:. Expansão para Voxels ;))
    IMT_GridData = imread(pIMT_FileName.toStdString(),IMREAD_COLOR);

    //Inicializa parametros de construção
    IMT_Scale    = 1.0f;
    IMT_MapSizeX = IMT_GridData.rows;
    IMT_MapSizeY = IMT_GridData.cols;
    IMT_MapSize  = IMT_MapSizeX * IMT_MapSizeY;

    //Just Fix the size depending on the Grid Type(HeightMaps and ColorMaps Filters etc...Must have Power of Two Sizes.(Todo: Fix It!)
    if(IMT_GridType != IMT_GRID_TYPE_IMAGE)IMT_MapSize = IMT_MapSizeX;

    IMT_QuadSize = 1;

    //Aloca o tamanho do Transformation Buffer
    IMT_TBuffer.resize(IMT_MapSize);

    //Zera as alturas para inicio.
    memset(&IMT_TBuffer[0],0, IMT_TBuffer.size());
}

CIMTGrid::CIMTGrid(const CIMTGrid &grid)
{

    IMT_GridType = grid.IMT_GridType;

    //Carrega dados da Imagem(Por enquanto temos apenas imagem como fonte para dados. Ex:. Expansão para Voxels ;))
    IMT_GridData = grid.IMT_GridData;

    //Inicializa parametros de construção
    IMT_Scale    = grid.IMT_Scale;
    IMT_MapSizeX = grid.IMT_MapSizeX;
    IMT_MapSizeY = grid.IMT_MapSizeY;
    IMT_MapSize  = grid.IMT_MapSize;
    IMT_QuadSize = grid.IMT_QuadSize;

    //Aloca o tamanho do Transformation Buffer
    IMT_TBuffer = grid.IMT_TBuffer;
}

CIMTGrid &CIMTGrid::operator=(const CIMTGrid& opr)
{
    IMT_GridType = opr.IMT_GridType;

    //Carrega dados da Imagem(Por enquanto temos apenas imagem como fonte para dados. Ex:. Expansão para Voxels ;))
    IMT_GridData = opr.IMT_GridData;

    //Inicializa parametros de construção
    IMT_Scale    = opr.IMT_Scale;
    IMT_MapSizeX = opr.IMT_MapSizeX;
    IMT_MapSizeY = opr.IMT_MapSizeY;
    IMT_MapSize  = opr.IMT_MapSize;
    IMT_QuadSize = opr.IMT_QuadSize;

    //Aloca o tamanho do Transformation Buffer
    IMT_TBuffer = opr.IMT_TBuffer;

    return (*this);
}

long CIMTGrid::floatToLong(float f)
{
    // Converts a floating point number into an integer.
    // Fractional values are truncated as in ANSI C.
    // About 5 to 6 times faster than a standard typecast to an integer.

    long fpBits = *reinterpret_cast<const long*>(&f);
    long shift = 23 - (((fpBits & 0x7fffffff) >> 23) - 127);
    long result = ((fpBits & 0x7fffff) | (1 << 23)) >> shift;

    result = (result ^ (fpBits >> 31)) - (fpBits >> 31);
    result &= ~((((fpBits & 0x7fffffff) >> 23) - 127) >> 31);

    return result;
}

float CIMTGrid::random(float min, float max)
{
    // Returns a random number in range [min,max].
    return min + (max - min) * (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}


void CIMTGrid::GenerateFractal(float pIMT_Roughness)
{
    // Generates a fractal height field using the diamond-square (midpoint
    // displacement) algorithm. Note that only square height fields work with
    // this algorithm.
    //
    // Based on article and associated code:
    // "Fractal Terrain Generation - Midpoint Displacement" by Jason Shankel
    // (Game Programming Gems I, pp.503-507).

    srand(static_cast<unsigned int>(time(0)));

    std::fill(IMT_TBuffer.begin(), IMT_TBuffer.end(), 0.0f);

    int p1, p2, p3, p4, mid;
    float dH = IMT_MapSize * 0.5f;
    float dHFactor = powf(2.0f, -pIMT_Roughness);
    float minH = 0.0f, maxH = 0.0f;

    for (int w = IMT_MapSize; w > 0; dH *= dHFactor, w /= 2)
    {
        // Diamond Step.
        for (uint z = 0; z < IMT_MapSize; z += w)
        {
            for (uint x = 0; x < IMT_MapSize; x += w)
            {
                p1  = GetTBufferIndex(x, z);
                p2  = GetTBufferIndex(x + w, z);
                p3  = GetTBufferIndex(x + w, z + w);
                p4  = GetTBufferIndex(x, z + w);
                mid = GetTBufferIndex(x + w / 2, z + w / 2);

                IMT_TBuffer[mid] = random(-dH, dH) + (IMT_TBuffer[p1] + IMT_TBuffer[p2] + IMT_TBuffer[p3] + IMT_TBuffer[p4]) * 0.25f;

                minH = min(minH, IMT_TBuffer[mid]);
                maxH = max(maxH, IMT_TBuffer[mid]);
            }
        }

        // Square step.
        for (uint z = 0; z < IMT_MapSize; z += w)
        {
            for (uint x = 0; x < IMT_MapSize; x += w)
            {
                p1  = GetTBufferIndex(x, z);
                p2  = GetTBufferIndex(x + w, z);
                p3  = GetTBufferIndex(x + w / 2, z - w / 2);
                p4  = GetTBufferIndex(x + w / 2, z + w / 2);
                mid = GetTBufferIndex(x + w / 2, z);

                IMT_TBuffer[mid] = random(-dH, dH) + (IMT_TBuffer[p1] + IMT_TBuffer[p2] + IMT_TBuffer[p3] + IMT_TBuffer[p4]) * 0.25f;

                minH = min(minH, IMT_TBuffer[mid]);
                maxH = max(maxH, IMT_TBuffer[mid]);

                p1  = GetTBufferIndex(x, z);
                p2  = GetTBufferIndex(x, z + w);
                p3  = GetTBufferIndex(x + w / 2, z + w / 2);
                p3  = GetTBufferIndex(x - w / 2, z + w / 2);
                mid = GetTBufferIndex(x, z + w / 2);

                IMT_TBuffer[mid] = random(-dH, dH) + (IMT_TBuffer[p1] + IMT_TBuffer[p2] + IMT_TBuffer[p3] + IMT_TBuffer[p4]) * 0.25f;

                minH = min(minH, IMT_TBuffer[mid]);
                maxH = max(maxH, IMT_TBuffer[mid]);
            }
        }
    }

    ApplyBoxFilter();

    // Normalize height field so altitudes fall into range [0,255].
    for (uint i = 0; i < IMT_MapSize * IMT_MapSize; ++i)
        IMT_TBuffer[i] = 255.0f * (IMT_TBuffer[i] - minH) / (maxH - minH);

}

uint CIMTGrid::GetTBufferIndex(uint pIMT_X , uint pIMT_Y)
{
    return (((pIMT_X + IMT_MapSize) % IMT_MapSize) + ((pIMT_Y + IMT_MapSize) % IMT_MapSize) * IMT_MapSize);
}

float CIMTGrid::GetTBufferValue(uint pIMT_X , uint pIMT_Z)
{
    return IMT_TBuffer[pIMT_Z * IMT_MapSize + pIMT_X];
}

float * CIMTGrid::GetTBuffer()
{
    return &IMT_TBuffer[0];
}

void CIMTGrid::GetTBufferNormal(float pIMT_X, float pIMT_Z, CIMTVector &pIMT_Normal)
{
    // Given a (x, z) position on the rendered height map this method
    // calculates the exact normal of the height map at that (x, z) position
    // using bilinear interpolation.

    pIMT_X /= static_cast<float>(IMT_QuadSize);
    pIMT_Z /= static_cast<float>(IMT_QuadSize);

    assert(pIMT_X >= 0.0f && pIMT_X < float(IMT_MapSize));
    assert(pIMT_Z >= 0.0f && pIMT_Z < float(IMT_MapSize));

    long ix = floatToLong(pIMT_X);
    long iz = floatToLong(pIMT_Z);

    float percentX = pIMT_X - static_cast<float>(ix);
    float percentZ = pIMT_Z - static_cast<float>(iz);

    CIMTVector topLeft;
    CIMTVector topRight;
    CIMTVector bottomLeft;
    CIMTVector bottomRight;

    GetPixelNormal(ix, iz, topLeft);
    GetPixelNormal(ix + 1, iz, topRight);
    GetPixelNormal(ix, iz + 1, bottomLeft);
    GetPixelNormal(ix + 1, iz + 1, bottomRight);

    pIMT_Normal = bilerp(topLeft, topRight, bottomLeft, bottomRight, percentX, percentZ);
    pIMT_Normal.Normalize();
}

void CIMTGrid::GetPixelNormal(float pIMT_X , float pIMT_Z , CIMTVector &pIMT_Normal)
{
    // Returns the normal at the specified location on the height map.
    // The normal is calculated using the properties of the height map.
    // This approach is much quicker and more elegant than triangulating the
    // height map and averaging triangle surface normals.

    if (pIMT_X > 0 && pIMT_X < IMT_MapSize - 1)
        pIMT_Normal.x = GetTBufferValue(pIMT_X - 1, pIMT_Z) - GetTBufferValue(pIMT_X + 1, pIMT_Z);
    else if (pIMT_X > 0)
        pIMT_Normal.x = 2.0f * (GetTBufferValue(pIMT_X - 1, pIMT_Z) - GetTBufferValue(pIMT_X, pIMT_Z));
    else
        pIMT_Normal.x = 2.0f * (GetTBufferValue(pIMT_X, pIMT_Z) - GetTBufferValue(pIMT_X + 1, pIMT_Z));

    if (pIMT_Z > 0 && pIMT_Z < IMT_MapSize - 1)
        pIMT_Normal.z = GetTBufferValue(pIMT_X, pIMT_Z - 1) - GetTBufferValue(pIMT_X, pIMT_Z + 1);
    else if (pIMT_Z > 0)
        pIMT_Normal.z = 2.0f * (GetTBufferValue(pIMT_X, pIMT_Z - 1) - GetTBufferValue(pIMT_X, pIMT_Z));
    else
        pIMT_Normal.z = 2.0f * (GetTBufferValue(pIMT_X, pIMT_Z) - GetTBufferValue(pIMT_X, pIMT_Z + 1));

    pIMT_Normal.y = 2.0f * IMT_QuadSize;
    pIMT_Normal.Normalize();

}

QImage CIMTGrid::GetColorMap()
{
    int   pAlturaPixel=0;
    float shade;
    float heightPct;
    QRgb  value;
    float r,g,b;

    QImage ImgColor;//Imagem Base para Texturização(Geracao automatica de textura).

    ImgColor = QImage(IMT_MapSize,IMT_MapSize, QImage::Format_RGB32);

    /****************************************/
    /*Adiciona o Total de Vertices do Painel*/
    /****************************************/
    for ( uint X = 0;  X < (IMT_MapSize); X ++)
    {
       for ( uint Y = 0; Y < (IMT_MapSize); Y ++ )
       {
           shade=0.6f + (0.3f * rand())/RAND_MAX;	// Cria um padraozinho randomico(noise) para o pixel
           heightPct    = pAlturaPixel / 16.0f;
           pAlturaPixel = GetTBufferValue(X,Y);
           pAlturaPixel/=16;
           if ( shade        > 1 )  shade = 1;
           if ( shade        < 0 )  shade = 0;
           if ( pAlturaPixel > 0 )
           {
              r  = (shade * ((heightPct * IMT_ColorMap[pAlturaPixel][0]) + ((1.0f-heightPct) * IMT_ColorMap[pAlturaPixel-1][0])));
              g  = (shade * ((heightPct * IMT_ColorMap[pAlturaPixel][1]) + ((1.0f-heightPct) * IMT_ColorMap[pAlturaPixel-1][1])));
              b  = (shade * ((heightPct * IMT_ColorMap[pAlturaPixel][2]) + ((1.0f-heightPct) * IMT_ColorMap[pAlturaPixel-1][2])));
              value = qRgb(r,g,b);
           }
           else	// Special case for sea.
           {
              r = (shade * IMT_ColorMap[0][0]);
              g = (shade * IMT_ColorMap[0][1]);
              b = (shade * IMT_ColorMap[0][2]);
              value = qRgb(r,g,b);
           }

           ImgColor.setPixel(X,Y,value);
       }
    }

    return ImgColor;
}

void CIMTGrid::GenerateColors()
{
    IMT_ColorMap[0] [0]=72;  IMT_ColorMap[0] [1]=68;  IMT_ColorMap[0] [2]=154;
    IMT_ColorMap[1] [0]=84;  IMT_ColorMap[1] [1]=125; IMT_ColorMap[1] [2]=228;
    IMT_ColorMap[2] [0]=120; IMT_ColorMap[2] [1]=202; IMT_ColorMap[2] [2]=172;
    IMT_ColorMap[3] [0]=248; IMT_ColorMap[3] [1]=205; IMT_ColorMap[3] [2]=136;
    IMT_ColorMap[4] [0]=223; IMT_ColorMap[4] [1]=130; IMT_ColorMap[4] [2]=47;
    IMT_ColorMap[5] [0]=237; IMT_ColorMap[5] [1]=149; IMT_ColorMap[5] [2]=91;
    IMT_ColorMap[6] [0]=156; IMT_ColorMap[6] [1]=193; IMT_ColorMap[6] [2]=9;
    IMT_ColorMap[7] [0]=180; IMT_ColorMap[7] [1]=213; IMT_ColorMap[7] [2]=47;
    IMT_ColorMap[8] [0]=163; IMT_ColorMap[8] [1]=176; IMT_ColorMap[8] [2]=112;
    IMT_ColorMap[9] [0]=163; IMT_ColorMap[9] [1]=176; IMT_ColorMap[9] [2]=112;
    IMT_ColorMap[10][0]=194; IMT_ColorMap[10][1]=161; IMT_ColorMap[10][2]=118;
    IMT_ColorMap[11][0]=165; IMT_ColorMap[11][1]=120; IMT_ColorMap[11][2]=71;
    IMT_ColorMap[12][0]=183; IMT_ColorMap[12][1]=154; IMT_ColorMap[12][2]=125;
    IMT_ColorMap[13][0]=195; IMT_ColorMap[13][1]=189; IMT_ColorMap[13][2]=181;
    IMT_ColorMap[14][0]=235; IMT_ColorMap[14][1]=232; IMT_ColorMap[14][2]=227;
    IMT_ColorMap[15][0]=225; IMT_ColorMap[15][1]=225; IMT_ColorMap[15][2]=225;
}

void CIMTGrid::ApplyBoxFilter()
{
    // Applies a box filter to the height map to smooth it out.
    std::vector<float> source(IMT_TBuffer);
    float value = 0.0f;
    float cellAverage = 0.0f;
    uint i = 0;
    uint bounds = IMT_MapSize * IMT_MapSize;

    for (uint y = 0; y < IMT_MapSize; ++y)
    {
        for (uint x = 0; x < IMT_MapSize; ++x)
        {
            value = 0.0f;
            cellAverage = 0.0f;

            i = (y - 1) * IMT_MapSize + (x - 1);
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = (y - 1) * IMT_MapSize + x;
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = (y - 1) * IMT_MapSize + (x + 1);
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = y * IMT_MapSize + (x - 1);
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = y * IMT_MapSize + x;
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = y * IMT_MapSize + (x + 1);
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = (y + 1) * IMT_MapSize + (x - 1);
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = (y + 1) * IMT_MapSize + x;
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            i = (y + 1) * IMT_MapSize + (x + 1);
            if (i < bounds)
            {
                value += source[i];
                cellAverage += 1.0f;
            }

            IMT_TBuffer[y * IMT_MapSize + x] = value / cellAverage;
        }
    }
}

void CIMTGrid::ApplyBlurrFilter(float pIMT_Steps)
{
    // Applies a simple FIR (Finite Impulse Response) filter across the height
    // map to blur it. 'amount' is in range [0,1]. 0 is no blurring, and 1 is
    // very strong blurring.
    float *pPixel     = 0;
    float *pPrevPixel = 0;
    uint width         = IMT_MapSize;
    uint height        = IMT_MapSize;
    uint pitch         = IMT_MapSize;

    // Blur horizontally. Both left-to-right, and right-to-left.
    for (uint i = 0; i < height; ++i)
    {
        pPrevPixel = &IMT_TBuffer[i * pitch];
        // Left-to-right.
        for (uint j = 1; j < width; ++j)
        {
            pPixel = &IMT_TBuffer[(i * pitch) + j];
           *pPixel = (*pPrevPixel * pIMT_Steps) + (*pPixel * (1.0f - pIMT_Steps));
            pPrevPixel = pPixel;
        }

        pPrevPixel = &IMT_TBuffer[(i * pitch) + (width - 1)];

        // Right-to-left.
        for (int j = width - 2; j >= 0; --j)
        {
            pPixel = &IMT_TBuffer[(i * pitch) + j];
           *pPixel = (*pPrevPixel * pIMT_Steps) + (*pPixel * (1.0f - pIMT_Steps));
            pPrevPixel = pPixel;
        }
    }

    // Blur vertically. Both top-to-bottom, and bottom-to-top.
    for (uint i = 0; i < width; ++i)
    {
        pPrevPixel = &IMT_TBuffer[i];

        // Top-to-bottom.
        for (uint j = 1; j < height; ++j)
        {
            pPixel = &IMT_TBuffer[(j * pitch) + i];
           *pPixel = (*pPrevPixel * pIMT_Steps) + (*pPixel * (1.0f - pIMT_Steps));
            pPrevPixel = pPixel;
        }

        pPrevPixel = &IMT_TBuffer[((height - 1) * pitch) + i];

        // Bottom-to-top.
        for (int j = height - 2; j >= 0; --j)
        {
            pPixel = &IMT_TBuffer[(j * pitch) + i];
           *pPixel = (*pPrevPixel * pIMT_Steps) + (*pPixel * (1.0f - pIMT_Steps));
            pPrevPixel = pPixel;
        }
    }
}
