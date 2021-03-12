/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IMT_Quaternion.h"

CIMTQuat::CIMTQuat()
{
   x = y = z = 0.0f;
   w = 1.0f;
}

CIMTQuat::CIMTQuat(float xEixo, float yEixo, float zEixo, float wEixo)
{
   x = xEixo; y = yEixo; z = zEixo;
   w = wEixo;
}

void CIMTQuat::operator=(const CIMTQuat &q)
{
   w = q.w; x = q.x; y = q.y; z = q.z;
}

CIMTQuat CIMTQuat::operator*(const CIMTQuat &q)
{
   CIMTQuat result;

   result.x = w * q.x + x * q.w + y * q.z - z * q.y;
   result.y = w * q.y - x * q.z + y * q.w + z * q.x;
   result.z = w * q.z + x * q.y - y * q.x + z * q.w;
   result.w = w * q.w - x * q.x - y * q.y - z * q.z;

   return result;
}

CIMTQuat CIMTQuat::Conjugar()
{
   return CIMTQuat(-x, -y, -z, w);
}

void CIMTQuat::Rotaciona(float grau, float xEixo, float yEixo, float zEixo)
{
   if((xEixo != 0 && xEixo != 1) ||
      (yEixo != 0 && yEixo != 1) ||
      (zEixo != 0 && zEixo != 1))
   {
      float tamanho = (float)sqrt(xEixo * xEixo + yEixo * yEixo + zEixo * zEixo);

       xEixo /= tamanho;
       yEixo /= tamanho;
       zEixo /= tamanho;
   }

   float angulo = PEGA_RADIANOS(grau);
   float seno   = (float)sin(angulo / 2.0f);

   x = xEixo * seno;
   y = yEixo * seno;
   z = zEixo * seno;
   w = (float)cos(angulo / 2.0f);

   float tamanho = 1 / (float)sqrt(x * x + y * y + z * z + w * w);
   x *=  tamanho;
   y *=  tamanho;
   z *=  tamanho;

}

void CIMTQuat::CriaMatriz(float *pMatriz)
{
   if(!pMatriz)
      return;

    pMatriz[0]  = 1.0f - 2.0f * (y * y + z * z);
    pMatriz[1]  = 2.0f * (x * y + z * w);
    pMatriz[2]  = 2.0f * (x * z - y * w);
    pMatriz[3]  = 0.0f;

    pMatriz[4]  = 2.0f * (x * y - z * w);
    pMatriz[5]  = 1.0f - 2.0f * (x * x + z * z);
    pMatriz[6]  = 2.0f * (z * y + x * w);
    pMatriz[7]  = 0.0f;

    pMatriz[8]  = 2.0f * (x * z + y * w);
    pMatriz[9]  = 2.0f * (y * z - x * w);
    pMatriz[10] = 1.0f - 2.0f * (x * x + y * y);
    pMatriz[11] = 0.0f;

    pMatriz[12] = 0;
    pMatriz[13] = 0;
    pMatriz[14] = 0;
    pMatriz[15] = 1.0f;
}
