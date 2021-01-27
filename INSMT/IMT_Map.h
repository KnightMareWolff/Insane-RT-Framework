/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de CriaÃƒÂ§ÃƒÂ£o     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#ifndef IMT_MAP_H
#define IMT_MAP_H

#include "INSMT_global.h"

/*************************************************/
/*Classe responsavel pela manutencao de peso em  */
/*uma determinada posicao do mapa                */
/*************************************************/
class CIMTMapCell
{
   public:

   CIMTMapCell(                        );
   CIMTMapCell(const int custo         );
   CIMTMapCell(const CIMTMapCell& copia);
   CIMTMapCell &operator=(const CIMTMapCell& opr);

   int  GetCost(               );
   void SetCost(const int custo);

   private:

   int m_cost;

};

/***************************************************/
/*Classe responsavel pela manutencao do mapa onde a*/
/*busca sera realizada                             */
/***************************************************/
class INSMT_EXPORT CIMTMap
{
public:

    CIMTMap(const int tamanho);

    virtual ~CIMTMap();

    int  GetSize();
    int  GetCost(const int x, const int y);
    void SetCost(const int x, const int y, const int custo);

    void SetStart(const int x, const int y);
    void GetStart(int &x, int &y);

    void SetFinish(const int x, const int y);
    void GetFinish(int &x, int &y);

    int  GetBlocked();

private:

    CIMTMapCell **m_grid;
    int IMT_Size;
    int IMT_StartPosX;
    int	IMT_StartPosY;
    int	IMT_FinishPosX;
    int	IMT_FinishPosY;
};


#endif // IMT_MAP_H
