/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CMTMAINSCREEN_H
#define CMTMAINSCREEN_H

#include <QWidget>
#include "INSMT.h"

class CMTMainScreen : public QWidget
{
    Q_OBJECT

public:
     CMTMainScreen(QWidget *parent = nullptr);
    ~CMTMainScreen();
private:
     CIMTBoundingBox        pBoundingBox;
     //CIMTGraph<CIMTVector>  pGraph;
     //CIMTTree               pTree;
     CIMTGrid               pGrid;
     CIMTList               pList;
     CIMTMatrix             pMatrix;
     CIMTPlane              pPlane;
     CIMTPriorityQueue      pPriorityQueue;
     CIMTQuat               pQuaternion;
     CIMTVector             pVector ;
     CIMTVector2            pVector2;
     CIMTVector4            pVector4;
     CIMTVertex             pVertex;
};
#endif // CMTMAINSCREEN_H
