#ifndef CIMTPOLYGON_H
#define CIMTPOLYGON_H

#include "IMT_Bounds.h"
#include "IMT_VertexBuffer.h"

class INSMT_EXPORT CIMTPolygon
{
public:
    CIMTPolygon();
    CIMTPolygon( const CIMTPolygon & copy );

    CIMTPolygon& operator=  ( const CIMTPolygon& opr );

    CIMTVertexBuffer  IMT_VertexBuffer ;//The resultant vertex buffer
    CIMTBoundingBox   IMT_Bound        ;//Boundary of the Polygon
    int               IMT_WindingMode  ;//Clockwise or CounterClockwise Order?


};

#endif // CIMTPOLYGON_H
