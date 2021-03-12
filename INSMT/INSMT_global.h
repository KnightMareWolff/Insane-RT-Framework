/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef INSMT_GLOBAL_H
#define INSMT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(INSMT_LIBRARY)
#  define INSMT_EXPORT Q_DECL_EXPORT
#else
#  define INSMT_EXPORT Q_DECL_IMPORT
#endif

// OpenCV includes
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

#include <QImage>
#include <QtGlobal>
#include <QQueue>

//EnumeraTor For the walking search process
typedef enum WALKING
{
    SEARCHING  ,
    FOUND      ,
    IMPOSSIBLE
}STDWALKING;

//Math Macros and definitions
#define EPSILON         0.001f                 //Valor de tolerancia
#define FUZZY           0.00001f               //Valor de Tolerancia
#define PI              3.1415926535897932     //PI
#define TWOPI           6.283185308
#define PiOver180		1.74532925199433E-002f
#define PiUnder180		5.72957795130823E+001f
#define SMALL_NUMBER	0.00001
#define LARGE_NUMBER	1E20
#define CELL_BLOCKED    3000
#define SQR(x) ((x) * (x))
#define DEG2RAD(a) (((a) * M_PI) / 180.0f)

#define IMT_GRID_TYPE_IMAGE    0 //Este Grid Representa uma Imagem
#define IMT_GRID_TYPE_COLORMAP 1 //Este Grid Representa um Mapeamento de Cores
#define IMT_GRID_TYPE_DEPTHMAP 2 //No com encadeamento Simples

//Algorithm Macros and definitions

#define IUT_NODE_LINK_Simple   0 //Simple Node Linking
#define IUT_NODE_LINK_Double   1 //Double Linking Nodes
#define IUT_NODE_LINK_Priority 2 //Double Linking Nodes with Priority

#define IMT_MESH_TYPE_FACETED  0
#define IMT_MESH_TYPE_SKINNED  1

#define IMT_OBJECT_TYPE_CUBE    0
#define IMT_OBJECT_TYPE_SKY     1
#define IMT_OBJECT_TYPE_TERRAIN 2


#endif // INSMT_GLOBAL_H
