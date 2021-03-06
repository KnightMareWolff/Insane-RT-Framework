/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#include "IMT_Node.h"

CIMTNode::CIMTNode()
{
    IMT_TpNode     = IUT_NODE_LINK_Double  ;
    IMT_Next    = 0;
    IMT_Prior   = 0;
    IMT_Priority = 0;

    switch(IMT_TpNode)
    {
       case IUT_NODE_LINK_Simple:
       {
           IMT_Name = QString("Default Simple Node");
       }break;
       case IUT_NODE_LINK_Double:
       {
           IMT_Name = QString("Default Double Linking");
       }break;
       case IUT_NODE_LINK_Priority:
       {
           IMT_Name = QString("Priority Node");
       }break;
       default:{IMT_Name = QString("Default Double Linking");}break;
    }
}

CIMTNode::CIMTNode(CIMTNode* pIMT_Node)
{
    IMT_TpNode   = pIMT_Node->IMT_TpNode  ;
    IMT_Next     = 0;
    IMT_Prior    = 0;
    IMT_Priority = pIMT_Node->IMT_Priority;
    IMT_Name     = pIMT_Node->IMT_Name;
}

