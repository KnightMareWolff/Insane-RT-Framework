/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IMT_PriorityQueue.h"

/**************************************/
/*Construtor da Fila                  */
/**************************************/
CIMTPriorityQueue::CIMTPriorityQueue()
{
    IMT_Size = 0;
    IMT_Begin  = new CIMTNode();
    IMT_End    = new CIMTNode();

    //Estabelece prioridade Minima e Maxima de entrada.
    IMT_Begin->IMT_Priority = 0;
    IMT_End  ->IMT_Priority = 999;

    IMT_Begin->IMT_Next  = IMT_End;
    IMT_Begin->IMT_Prior = NULL;
    IMT_End  ->IMT_Prior = IMT_Begin;
    IMT_End  ->IMT_Next  = NULL;
}

/**************************************/
/*Destrutor da Fila                   */
/**************************************/
CIMTPriorityQueue::~CIMTPriorityQueue()
{
    Clear();
    delete IMT_Begin;
    delete IMT_End;
}

/**************************************/
/*Insere No na Fila                   */
/**************************************/
void CIMTPriorityQueue::Push(CIMTNode* pIUT_Node , int pIMT_Priority , QString pIMT_Name)
{
    CIMTNode *novo = pIUT_Node;

    novo->IMT_Name = pIMT_Name;
    /****************************************************/
    /*Os Nos sao inseridos de acordo com sua prioridade */
    /*Neste caso quanto maior for o custo menor sera sua*/
    /*prioridade.                                       */
    /****************************************************/
    CIMTNode *temp = IMT_Begin;
    while(pIMT_Priority > temp->IMT_Priority)
    {
        temp = temp->IMT_Next;
    }

    /****************************************/
    /*Insere o no na posicao anterior       */
    /****************************************/
    novo->IMT_Prior              = temp->IMT_Prior;
    novo->IMT_Next               = temp;
    temp->IMT_Prior              = novo;
    novo->IMT_Prior->IMT_Next = novo;

    IMT_Size++;
}

/**************************************/
/*Retira no da Fila                   */
/**************************************/
CIMTNode* CIMTPriorityQueue::Pop()
{

    /******************************************/
    /*Sempre sendo removido o primeiro da fila*/
    /******************************************/
    CIMTNode* item = NULL;
    CIMTNode* temp;

    if(IMT_Size > 0)
    {
        IMT_Begin->IMT_Next->IMT_Next->IMT_Prior = IMT_Begin;
        temp = IMT_Begin->IMT_Next;
        IMT_Begin->IMT_Next = IMT_Begin->IMT_Next->IMT_Next;

        item = temp;
        delete temp;
    }

    IMT_Size--;

    return item;
}

/**************************************/
/*Limpa a Fila                        */
/**************************************/
void CIMTPriorityQueue::Clear()
{
    while(!Empty())
    {
        Pop();
    }
}

/**************************************/
/*Verifica se a lista esta vazia      */
/**************************************/
bool CIMTPriorityQueue::Empty()
{
    return IMT_Size == 0;
}

/**************************************/
/*Busca pelo Nome                     */
/**************************************/
CIMTNode* CIMTPriorityQueue::Search(QString nome)
{
    CIMTNode *temp = IMT_Begin->IMT_Next;

    while(temp->IMT_Next != NULL)
    {
        if(temp->IMT_Name == nome)
        {
            return temp;
        }
        temp = temp->IMT_Next;
    }

    return NULL;
}

/**************************************/
/*Busca pelo Nome                     */
/**************************************/
CIMTNode* CIMTPriorityQueue::Search(unsigned int Id)
{
    CIMTNode *temp;

    if(Id > IMT_Size)return NULL;

    temp = IMT_Begin->IMT_Next;

    uint posicao = 0;

    while(temp->IMT_Next != NULL)
    {
        if(posicao == Id)
        {
            return temp;
        }
        temp = temp->IMT_Next;
        posicao++;
    }

    return NULL;
}

/**************************************/
/*Retorna o Tamanho da Fila           */
/**************************************/
unsigned int CIMTPriorityQueue::Size()
{
    return IMT_Size;
}
