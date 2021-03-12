/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IMT_List.h"

CIMTList::CIMTList()
{
    IMT_Size = 0;
    IMT_Begin  = new CIMTNode();
    IMT_End     = new CIMTNode();

    //Estabelece os Nós Iniciais da Lista.
    IMT_Begin->IMT_Next  = IMT_End;
    IMT_Begin->IMT_Prior = NULL;
    IMT_End   ->IMT_Prior = IMT_Begin;
    IMT_End   ->IMT_Next  = NULL;

    IMT_Name = "Default";
}

CIMTList::CIMTList(QString pIMT_ListName)
{
    IMT_Size   = 0;
    IMT_Begin  = new CIMTNode();
    IMT_End    = new CIMTNode();

    //Estabelece os Nós Iniciais da Lista.
    IMT_Begin->IMT_Next  = IMT_End;
    IMT_Begin->IMT_Prior = NULL;
    IMT_End  ->IMT_Prior = IMT_Begin;
    IMT_End  ->IMT_Next  = NULL;

    IMT_Name = pIMT_ListName;
}

CIMTList::~CIMTList()
{
    Clear();
    delete IMT_Begin;
    delete IMT_End;
}

void CIMTList::Clear()
{
    int Index = 0;
    while(!Empty())
    {
        Remove(Index);
        Index++;
    }
}
bool CIMTList::Empty()
{
    return IMT_Size == 0;
}

void CIMTList::Add(CIMTNode* pIMT_Node )
{
    CIMTNode *novo = pIMT_Node;

    /****************************************************/
    /*O no é inserido no final da lista                 */
    /****************************************************/
    CIMTNode *temp = IMT_Begin;
    while(temp != IMT_End)
    {
        temp = temp->IMT_Next;
    }

    /****************************************/
    /*Insere o no na posicao anterior       */
    /****************************************/
    novo->IMT_Prior           = temp->IMT_Prior;
    novo->IMT_Next            = temp;
    temp->IMT_Prior           = novo;
    novo->IMT_Prior->IMT_Next = novo;

    IMT_Size++;
}
void  CIMTList::Remove   (CIMTNode* pIMT_Node )
{
    CIMTNode *temp  = NULL;
    int       index = 0   ;

    if(IMT_Size > 0)
    {
        temp = IMT_Begin;

        while(temp != IMT_End)
        {
            temp = temp->IMT_Next;

            if(temp == pIMT_Node)
            {
                /****************************************/
                /*Insere o no na posicao anterior       */
                /****************************************/
                temp->IMT_Next->IMT_Prior = temp->IMT_Prior;
                temp->IMT_Prior           = temp->IMT_Next;

                delete temp;

                IMT_Size--;
            }

            index++;
        }
    }
}

void CIMTList::Remove(unsigned int pIMT_Id)
{
    CIMTNode *temp  = NULL;
    uint      index = 0   ;

    if(IMT_Size > 0)
    {
        temp = IMT_Begin;

        while(temp != IMT_End)
        {
            temp = temp->IMT_Next;

            if(index == pIMT_Id)
            {
                /****************************************/
                /*Insere o no na posicao anterior       */
                /****************************************/
                temp->IMT_Next->IMT_Prior = temp->IMT_Prior;
                temp->IMT_Prior           = temp->IMT_Next;

                delete temp;

                IMT_Size--;
            }

            index++;
        }
    }
}
CIMTNode* CIMTList::Search(unsigned int pIMT_Id)
{
    CIMTNode *temp;

    if(pIMT_Id > IMT_Size)return NULL;

    temp = IMT_Begin->IMT_Next;

    uint posicao = 0;

    while(posicao<IMT_Size)
    {
        if(posicao == pIMT_Id)
        {
            return temp;
        }
        temp = temp->IMT_Next;
        posicao++;
    }

    return  NULL;
}

uint  CIMTList::Size()
{
   return IMT_Size;
}
