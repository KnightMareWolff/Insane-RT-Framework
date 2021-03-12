/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef INSCG_GLOBAL_H
#define INSCG_GLOBAL_H

#include <QtCore/qglobal.h>

#include "INSMT.h"

#if defined(INSCG_LIBRARY)
#  define INSCG_EXPORT Q_DECL_EXPORT
#else
#  define INSCG_EXPORT Q_DECL_IMPORT
#endif

//Windingmode esta sendo configurado junto com material em função Enable para facilitar
//Portanto deve seguir a mesma sequencia de Case.
#define ICG_WINMODE_CW            10
#define ICG_WINMODE_CCW           11

//No Modo de Construção escolhemos construção RightHand ou LeftHand
#define ICG_POLYMODE_LEFT         0
#define ICG_POLYMODE_RIGHT        1

#define ICG_MESH_CLASSIC          1
#define ICG_MESH_SKINNED          2
#define ICG_MESH_HEIGHTMAP        3

#endif // INSCG_GLOBAL_H
