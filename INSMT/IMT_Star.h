/*********************************************************************************/
/*Projeto             :Insane RT Framework                                       */
/*Descricao           :                                                          */
/*Data de CriaÃƒÂ§ÃƒÂ£o     :                                                          */
/*                                                                               */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                 */
/*********************************************************************************/
#ifndef _IMT_STAR_H_
#define _IMT_STAR_H_

#include "INSMT_global.h"
#include "IMT_Map.h"

/********************************************************/
/*Classe responsavel pela manutensao de um no utilizado */
/*Na montagem do caminho a ser percorrido               */
/********************************************************/
class CIMTMapNode
{
public:
	
    CIMTMapNode(){ n_custo = PosNoX = PosNoY = 0;n_pai = 0;}

    CIMTMapNode(const int x,
		    const int y, 
            CIMTMapNode  *pai,
			const int custo){ PosNoX = x; PosNoY = y; n_pai = pai; n_custo = custo; }
	
    CIMTMapNode(const CIMTMapNode &copia);
	
    virtual ~CIMTMapNode() { n_pai = 0; }
    
    virtual CIMTMapNode &operator= (const CIMTMapNode &opr);
    virtual bool         operator==(const CIMTMapNode &opr);
    virtual bool         operator< (const CIMTMapNode &opr);
    virtual bool         operator> (const CIMTMapNode &opr);

    void         SetaPai  (CIMTMapNode*  pai     ) { n_pai = pai;}
	virtual void SetaCusto(const int custo   );
	virtual int  PegaCusto(                  ) const;
    bool         igual    (const CIMTMapNode &opr) const {return ((PosNoX==opr.PosNoX)&&
		                                                      (PosNoY==opr.PosNoY)); }

	int      PosNoX,
		     PosNoY;

	int      n_custo;

    CIMTMapNode *n_pai;

};

/********************************************************/
/*Classe responsavel pela manutensao de um no euristico */
/*Utilizado pelo algoritmo AEstrela                     */
/********************************************************/
class CIMTStarNode : public CIMTMapNode
{
public:
	
    CIMTStarNode() : CIMTMapNode() { g = f = h = 0; }
    CIMTStarNode(const CIMTStarNode &copia);
	
    virtual ~CIMTStarNode() { n_pai = 0; }

    virtual CIMTStarNode &operator=(const CIMTStarNode &opr);
	
	virtual void SetaCusto(const int custo);
	virtual int  PegaCusto(               )const;

	int g;
	int f;
	int h;

};

/**************************************************************/
/*Classe responsavel pela manutencao dos nos que sao incluidos*/
/*e excluidos durante o processamento do algoritmo  AEstrela  */
/*Esta Manutencao se da atraves de prioridade com relacao ao  */
/*Custo estimado de cada No.                                  */
/**************************************************************/
class CIMTStarQueue
{
public:
     CIMTStarQueue();
    ~CIMTStarQueue() { limpa(); delete ini->nofila; delete fim->nofila; delete ini; delete fim; }

    void         limpa    (                 );
    bool         vazio    (                 ) { return tam == 0; }
    void         entrafila( CIMTMapNode *no );
    CIMTMapNode* saifila  (                 );
    void         remove   ( CIMTMapNode *no );
    bool         contem   ( CIMTMapNode *no ) const;

private:
    class CIMTStarQueueNode
	{
	public:
        CIMTStarQueueNode() { nofila = 0; proximo = anterior = 0; }
        CIMTStarQueueNode(CIMTMapNode *no) { nofila = no; proximo = anterior = 0; }

        CIMTMapNode         *nofila;
        CIMTStarQueueNode   *proximo;
        CIMTStarQueueNode   *anterior;
	};

	unsigned int tam;
    CIMTStarQueueNode *ini;
    CIMTStarQueueNode *fim;
};

/*****************************************************/
/*Classe responsavel pela manutencao do processamento*/
/*Propriamente dito do algoritmo AEstrela            */
/*****************************************************/
class INSMT_EXPORT CIMTStar
{
public:
	
    CIMTMap *grid;

             CIMTStar      (                );
             CIMTStar      (CIMTMap* m_grid );
    virtual ~CIMTStar      (                );

    virtual STDWALKING  Passo      (                     );
    virtual void        reset      (                     );
    int                 estimativa (CIMTStarNode *origem);
    CIMTStarNode*       PegaCaminho(                     ){return NoAtual;}

protected:
	virtual void VisitarNo(int x, int y);

private:
    CIMTStarQueue      lista_aberta ;
    CIMTStarQueue      lista_fechada;
    CIMTStarNode *     NoInicio     ,
                 *     NoAtual      ,
                 *     NoFim        ;
    CIMTStarNode **    GridNos      ;
    float              PesoEuristica;
};

#endif
