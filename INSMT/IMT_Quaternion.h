/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IMT_QUATERNION_H
#define IMT_QUATERNION_H

#include "INSMT_global.h"

#define PEGA_RADIANOS(grau) (float)((grau * PI) / 180.0f)

class INSMT_EXPORT CIMTQuat
{
   public:

      CIMTQuat(              );
      CIMTQuat(float xEixo,
               float yEixo,
               float zEixo,
               float wEixo   );

      void operator=(const CIMTQuat &q);


      CIMTQuat operator*(const CIMTQuat &q);


      CIMTQuat Conjugar();


       void Rotaciona(float grau, float xEixo, float yEixo, float zEixo);

       void CriaMatriz(float *pMatriz);

       float x, y, z, w;
};

#endif // IMT_QUATERNION_H
