/*********************************************************************************/
/*Projeto             :Insane RT Framework                                       */
/*Descricao           :                                                          */
/*Data de Criação     :                                                          */
/*                                                                               */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                 */
/*********************************************************************************/
#include "INSMT_global.h"
#include "IMT_Map.h"

/**************************************/
/*Construtor do Mapa                  */
/**************************************/
CIMTMap::CIMTMap(const int tamanho)
{
    m_grid = NULL;
    m_grid = new CIMTMapCell*[tamanho];
    for(int i = 0 ; i < tamanho; i++)
    {
        m_grid[i] = NULL;
        m_grid[i] = new CIMTMapCell[tamanho];
    }

    IMT_Size = tamanho;

    IMT_StartPosX  = IMT_StartPosY  = 0;
    IMT_FinishPosX = IMT_FinishPosY = IMT_Size - 1;
}

/**************************************/
/*Destrutor do  Mapa                  */
/**************************************/
CIMTMap::~CIMTMap()
{
    /******************************/
    /*Limpa toda a memoria alocada*/
    /******************************/
    if(m_grid != NULL)
    {
        for(int i = 0; i < IMT_Size; i++)
        {
            if(m_grid[i] != NULL)
            {
                delete [] m_grid[i];
                m_grid[i] = NULL;
            }
        }

        delete [] m_grid;
        m_grid = NULL;
    }
}

/**************************************/
/*Retorna o tamanho do mapa           */
/**************************************/
int  CIMTMap::GetSize()
{
    return IMT_Size;
}

/**************************************/
/*Retorna o tamanho do mapa           */
/**************************************/
int CIMTMap::GetBlocked()
{
    int custo;
    int qtd=0;

    for(int i = 0; i < IMT_Size ; i++)
    {
        for(int j = 0; j < IMT_Size ; j++)
        {
            custo=GetCost(i,j);
            if(custo==CELL_BLOCKED)
            {
               qtd++;
            }
        }
    }
    return qtd;
}

/****************************************/
/*Retorna o custo de uma posicao no mapa*/
/****************************************/
int  CIMTMap::GetCost(const int x, const int y)
{
    return m_grid[x][y].GetCost();
}

/**************************************/
/*atribui um custo                    */
/**************************************/
void CIMTMap::SetCost(const int x, const int y, const int custo)
{
    m_grid[x][y].SetCost(custo);
}

/**************************************/
/*atribui a posicao inicial de busca  */
/**************************************/
void CIMTMap::SetStart(const int x, const int y)
{
    IMT_StartPosX=x;
    IMT_StartPosY=y;
}

/**************************************/
/*retorna posicao inicio              */
/**************************************/
void CIMTMap::GetStart(int &x, int &y)
{
   x=IMT_StartPosX;
   y=IMT_StartPosY;
}

/**************************************/
/*atribui posicao fim do mapa         */
/**************************************/
void CIMTMap::SetFinish(const int x, const int y)
{
    IMT_FinishPosX=x;
    IMT_FinishPosY=y;
}

/**************************************/
/*retorna posicao fim do Mapa         */
/**************************************/
void CIMTMap::GetFinish(int &x, int &y)
{
    x=IMT_FinishPosX;
    y=IMT_FinishPosY;
}


/**************************************/
/*Construtor da celula Mapa           */
/**************************************/
CIMTMapCell::CIMTMapCell()
{
    m_cost = 1;
}

/**************************************/
/*Construtor da celula Mapa           */
/**************************************/
CIMTMapCell::CIMTMapCell(const int custo)
{
    m_cost = custo;
}

/**************************************/
/*Construtor de copia                 */
/**************************************/
CIMTMapCell::CIMTMapCell(const CIMTMapCell& copia)
{
    m_cost = copia.m_cost;
}

/**************************************/
/*operador de atribuicao              */
/**************************************/
CIMTMapCell &CIMTMapCell::operator=(const CIMTMapCell& opr)
{
    m_cost = opr.m_cost;

    return (*this);
}

/**************************************/
/*retorna o custo da celula           */
/**************************************/
int  CIMTMapCell::GetCost()
{
    return m_cost;
}

/**************************************/
/*atribuit o custo na celula          */
/**************************************/
void CIMTMapCell::SetCost(const int custo)
{
    m_cost = custo;
}

