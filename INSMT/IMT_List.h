/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef IUT_LISTA_H
#define IUT_LISTA_H

#include "INSMT_global.h"
#include "IMT_Node.h"

class INSMT_EXPORT CIMTList
{
public:

     CIMTList(                      );
     CIMTList(QString pIMT_ListName );
    ~CIMTList(                      );

    void       Clear    (                    );
    bool       Empty    (                    );
    void       Add      (CIMTNode* pIMT_Node );
    void       Remove   (CIMTNode* pIMT_Node );
    void       Remove   (uint      pIMT_Id   );
    CIMTNode*  Search   (uint      pIMT_Id   );
    uint       Size     (                    );

private:

    uint          IMT_Size   ;
    CIMTNode     *IMT_Begin  ;
    CIMTNode     *IMT_End    ;
    QString       IMT_Name   ;
};

#endif // IUT_LISTA_H
