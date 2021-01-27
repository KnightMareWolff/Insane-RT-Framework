#include "Ex_STDMainScreen.h"

CSTDMainScreen::CSTDMainScreen(QWidget *parent)
    : QWidget(parent)
{
    vector<CIMTVertex> A;
    vector<CIMTVertex> B;

    A.push_back(CIMTVertex());
    A.push_back(CIMTVertex());
    A.push_back(CIMTVertex());

    for(uint i=0;i<A.size();i++)
    {
        if(i==0)A[i] = CIMTVertex( CIMTVector (1.0f,1.0f,1.0f),
                           CIMTVector2(1.0f,1.0f)  ,
                           CIMTVector (1.0f,1.0f,1.0f),
                           CIMTVector (1.0f,1.0f,1.0f),
                           CIMTVector (1.0f,1.0f,1.0f),
                           CIMTVector (1.0f,1.0f,1.0f));

        if(i==1)A[i] = CIMTVertex( CIMTVector (2.0f,2.0f,2.0f),
                           CIMTVector2(2.0f,2.0f)  ,
                           CIMTVector (2.0f,2.0f,2.0f),
                           CIMTVector (2.0f,2.0f,2.0f),
                           CIMTVector (2.0f,2.0f,2.0f),
                           CIMTVector (2.0f,2.0f,2.0f));

        if(i==2)A[i] = CIMTVertex( CIMTVector (3.0f,3.0f,3.0f),
                           CIMTVector2(3.0f,3.0f)  ,
                           CIMTVector (3.0f,3.0f,3.0f),
                           CIMTVector (3.0f,3.0f,3.0f),
                           CIMTVector (3.0f,3.0f,3.0f),
                           CIMTVector (3.0f,3.0f,3.0f));
    }

    B = A;

    for(uint i=0;i<B.size();i++)
    {
        B[i].IMT_Bitangent[0];
    }
}

CSTDMainScreen::~CSTDMainScreen()
{
}

