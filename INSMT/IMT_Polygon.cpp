/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IMT_Polygon.h"

CIMTPolygon::CIMTPolygon()
{

}

CIMTPolygon::CIMTPolygon( const CIMTPolygon & copy )
{
    IMT_VertexBuffer = copy.IMT_VertexBuffer;//The resultant vertex buffer
    IMT_Bound        = copy.IMT_Bound       ;//Boundary of the Polygon
    IMT_WindingMode  = copy.IMT_WindingMode ;//Clockwise or CounterClockwise Order?
}

CIMTPolygon& CIMTPolygon::operator=  ( const CIMTPolygon& opr )
{
    IMT_VertexBuffer = opr.IMT_VertexBuffer;//The resultant vertex buffer
    IMT_Bound        = opr.IMT_Bound       ;//Boundary of the Polygon
    IMT_WindingMode  = opr.IMT_WindingMode ;//Clockwise or CounterClockwise Order?

    return *this;
}
