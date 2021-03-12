/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CIUTGRAFO_H
#define CIUTGRAFO_H

#include "INSMT_global.h"
#include "IMT_List.h"

template<class T>
class INSMT_EXPORT CIMTGraph : public CIMTNode
{
private:
    CIMTList IMT_Childrens;
    T*       IMT_Data ;

protected:
    CIMTGraph *IMT_Father;


public:
               CIMTGraph     (QString pIUT_NomeGrafo  );
    virtual   ~CIMTGraph     (                        )  {}
    void       AddChildren   (CIMTGraph* pIUT_Grafo   );
    void       RemChildren   (CIMTGraph* pIUT_Grafo   );
    void       AddData       (T*         pIMT_Data    );
    CIMTGraph* GetFather     (                        );
    T*         GetData       (                        );
    CIMTGraph* GetChildren   (int     pIUT_IdFilho    );
    int        GetSize       (                        );
};

template<class T>
CIMTGraph<T>::CIMTGraph(QString pIUT_NomeGrafo):
    IMT_Father(NULL),
    IMT_Childrens(pIUT_NomeGrafo)
{

}


template<class T>
void CIMTGraph<T>::AddChildren(CIMTGraph* pIUT_Grafo)
{
    IMT_Childrens.Add(pIUT_Grafo);
    pIUT_Grafo->IMT_Father = this;
}


template<class T>
void CIMTGraph<T>::RemChildren(CIMTGraph* pIUT_Grafo)
{
    IMT_Childrens.Remove(pIUT_Grafo);
    delete pIUT_Grafo;
}

template<class T>
void CIMTGraph<T>::AddData(T* pIMT_Data)
{
    IMT_Data = pIMT_Data;
}

template<class T>
int CIMTGraph<T>::GetSize()
{
    return IMT_Childrens.Size();
}

template<class T>
T* CIMTGraph<T>::GetData()
{
    return IMT_Data;
}

template<class T>
CIMTGraph<T>* CIMTGraph<T>::GetFather()
{
    return IMT_Father;
}

template<class T>
CIMTGraph<T>* CIMTGraph<T>::GetChildren(int pIUT_IdFilho)
{
    CIMTNode *pNode = IMT_Childrens.Search(pIUT_IdFilho);

    return (CIMTGraph<T>*)pNode;
}

#endif // CIUTGRAFO_H
