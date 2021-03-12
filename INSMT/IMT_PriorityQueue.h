/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CIMTPriorityQueue_H
#define CIMTPriorityQueue_H

#include "INSMT_global.h"
#include "IMT_Node.h"

class INSMT_EXPORT CIMTPriorityQueue
{
public:
     CIMTPriorityQueue();
    ~CIMTPriorityQueue();

    void  Clear ();
    bool  Empty ();

    void              Push(CIMTNode*    pIUT_Node      ,
                           int          pIMT_Priority   ,
                           QString      pIMT_Name      );

    CIMTNode*  Pop       (                            );
    CIMTNode*  Search    (QString      pIMT_Name      );
    CIMTNode*  Search    (uint pIUT_Id                );
    uint       Size      (                            );

private:

    uint         IMT_Size;
    CIMTNode    *IMT_Begin ;
    CIMTNode    *IMT_End    ;
    QString      IMT_Name   ;
};

#endif // CIMTPriorityQueue_H
