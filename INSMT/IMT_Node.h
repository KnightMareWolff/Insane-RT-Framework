/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef IUT_NODE_H
#define IUT_NODE_H

#include "INSMT_global.h"

class INSMT_EXPORT CIMTNode
{
public:
    CIMTNode(                   );
    CIMTNode(CIMTNode* pIMT_Node);

public:
    unsigned int  IMT_TpNode  ;
    CIMTNode     *IMT_Next    ;
    CIMTNode     *IMT_Prior   ;
    int           IMT_Priority;
    QString       IMT_Name    ;
};

#endif // IUT_NODE_H
