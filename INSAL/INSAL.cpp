/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "INSAL.h"

//Inicialização da Instância Estatica
CIALSystem* INSAL::pINSMDStaticInterface=NULL;

static float  IAL_FATOR_DISTANCIA    =1.0f;    //Fator de Distancia(m/s)
static float  IAL_FATOR_DISTANCIAMIN =0.5f;    //Distancia Minima do som
static float  IAL_FATOR_DISTANCIAMAX =5000.0f; //Distancia Maxima do som
static float  IAL_FATOR_SCALADOPPLER =1.0f;    //Fator de Distancia(m/s)
static float  IAL_FATOR_SCALAROLLOFF =1.0f;    //Distancia Minima do som

unsigned int  IMDVersao;
void         *IMDDadosExtraDriver = 0;

INSAL::INSAL()
{
    pINSMDStaticInterface= new CIALSystem();
}

INSAL::~INSAL()
{
}

bool INSAL::SetaFatores3D(float pFatorDoppler,float pFatorDistancia,float pFatorRolloff)
{
    return true;
}

bool INSAL::SetaDistancias(float pDistMin,float pDistMax)
{
    IAL_FATOR_DISTANCIAMIN = pDistMin;
    IAL_FATOR_DISTANCIAMAX = pDistMax;
    return true;
}

bool INSAL::Atualiza()
{
    return true;
}


