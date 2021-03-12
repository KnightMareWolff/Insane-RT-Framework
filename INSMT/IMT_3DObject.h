/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CIMTOBJECT_H
#define CIMTOBJECT_H

#include "INSMT_global.h"
#include "IMT_Matrix.h"
#include "IMT_Mesh.h"

class INSMT_EXPORT CIMT3DTransformation
{
public:
    CIMT3DTransformation (){}
    CIMT3DTransformation (uint       pIMT_Type,
                          bool       pIMT_UseReference,
                          CIMTVector pIMT_Amount,
                          CIMTVector pIMT_Reference)
    {
        IMT_Type         = pIMT_Type;
        IMT_UseReference = pIMT_UseReference;
        IMT_Amount       = pIMT_Amount;
        IMT_Reference    = pIMT_Reference;
    }
    CIMT3DTransformation ( const CIMT3DTransformation &obj)
    {
        IMT_Type         = obj.IMT_Type;
        IMT_UseReference = obj.IMT_UseReference;
        IMT_Amount       = obj.IMT_Amount;
        IMT_Reference    = obj.IMT_Reference;
    }

    CIMT3DTransformation& operator=  ( const CIMT3DTransformation& opr )
    {
        IMT_Type         = opr.IMT_Type;
        IMT_UseReference = opr.IMT_UseReference;
        IMT_Amount       = opr.IMT_Amount;
        IMT_Reference    = opr.IMT_Reference;
        return *this;
    }

    ~CIMT3DTransformation(){}

    uint            IMT_Type;
    bool            IMT_UseReference;
    CIMTVector      IMT_Amount      ;//Position
    CIMTVector      IMT_Reference   ;//Reference Position
};

class INSMT_EXPORT CIMT3DObject
{
public:
    CIMT3DObject();
    CIMT3DObject( const CIMT3DObject & copy );

    CIMT3DObject& operator=  ( const CIMT3DObject& opr );

    void SetName     (QString          pIMT_Name     ){IMT_Name     =pIMT_Name;}
    void SetType     (uint             pIMT_Type     ){IMT_Type     =pIMT_Type;}
    void SetView     (CIMTVector       pIMT_View     ){IMT_View     =pIMT_View;}
    void SetUp       (CIMTVector       pIMT_Up       ){IMT_Up       =pIMT_Up;}
    void SetPos      (CIMTVector       pIMT_Pos      ){IMT_Pos      =pIMT_Pos;}
    void SetRot      (CIMTVector       pIMT_Rot      ){IMT_Rot      =pIMT_Rot;}
    void SetScl      (CIMTVector       pIMT_Scl      ){IMT_Scl      =pIMT_Scl;}
    void SetRefPos   (CIMTVector       pIMT_RefPos   ){IMT_RefPos   =pIMT_RefPos;}
    void SetRefRot   (CIMTVector       pIMT_RefRot   ){IMT_RefRot   =pIMT_RefRot;}
    void SetRefScl   (CIMTVector       pIMT_RefScl   ){IMT_RefScl   =pIMT_RefScl;}
    void SetDim      (CIMTVector       pIMT_Dim      ){IMT_Dim      =pIMT_Dim;}
    void SetTransfMtx(CIMTMatrix       pIMT_MtxTransf){IMT_MtxTransf=pIMT_MtxTransf;}
    void SetLocalMtx (CIMTMatrix       pIMT_MtxLocal ){IMT_MtxLocal =pIMT_MtxLocal;}
    void SetPickable (bool             pIMT_Pickable ){IMT_Pickable =pIMT_Pickable;}
    void SetSelected (bool             pIMT_Selected ){IMT_Selected =pIMT_Selected;}
    void SetPickId   (uint             pIMT_PickingId){IMT_PickingId=pIMT_PickingId;}
    void SetGeometry (CIMTMesh         pIMT_Geometry ){IMT_Geometry =pIMT_Geometry;}


    void Translate       (CIMTVector  pTransf,bool Incremento                          );
    void Rotate          (bool pControlPoint,CIMTVector  pTransf,CIMTVector  pControl  );
    void Scale           (bool pControlPoint,CIMTVector  pTransf,CIMTVector  pControl  );

    QString          GetName     (){return IMT_Name     ;}
    uint             GetType     (){return IMT_Type     ;}
    CIMTVector       GetView     (){return IMT_View     ;}
    CIMTVector       GetUp       (){return IMT_Up       ;}
    CIMTVector       GetPos      (){return IMT_Pos      ;}
    CIMTVector       GetRot      (){return IMT_Rot      ;}
    CIMTVector       GetScl      (){return IMT_Scl      ;}
    CIMTVector       GetRefPos   (){return IMT_RefPos   ;}
    CIMTVector       GetRefRot   (){return IMT_RefRot   ;}
    CIMTVector       GetRefScl   (){return IMT_RefScl   ;}
    CIMTVector       GetDim      (){return IMT_Dim      ;}
    CIMTMatrix       GetTransfMtx(){return IMT_MtxTransf;}
    CIMTMatrix       GetLocalMtx (){return IMT_MtxLocal ;}
    bool             GetPickable (){return IMT_Pickable ;}
    bool             GetSelected (){return IMT_Selected ;}
    uint             GetPickId   (){return IMT_PickingId;}
    CIMTMesh         GetGeometry (){return IMT_Geometry ;}

    void PushTransformation(uint        pIMT_Type,
                            bool        pIMT_UseReference,
                            CIMTVector  pIMT_Amount,
                            CIMTVector  pIMT_Reference);
    bool PopTransformation (uint       &pIMT_Type,
                            bool       &pIMT_UseReference,
                            CIMTVector &pIMT_Amount,
                            CIMTVector &pIMT_Reference);

    /*********************/
    /*Control Atributes  */
    /*********************/
    CIMTVector           IMT_View     ;//View
    CIMTVector           IMT_Up       ;//Up Vector
    CIMTVector           IMT_Pos      ;//Position
    CIMTVector           IMT_Rot      ;//Rotation in Radians
    CIMTVector           IMT_Scl      ;//Scale
    CIMTVector           IMT_RefPos   ;//Reference Point for Translation
    CIMTVector           IMT_RefRot   ;//Reference Point for Rotation
    CIMTVector           IMT_RefScl   ;//Reference Point for Scale
    CIMTVector           IMT_Dim      ;//Dimensions(x=width,y=height,z=deep)
    CIMTMatrix           IMT_MtxTransf;//Object Model View
    CIMTMatrix           IMT_MtxLocal ;//Local Transformation Matrix

    //All Objects Transformations are extracted from this queue.
    QQueue<CIMT3DTransformation> IMT_TransfQueue;

    /*********************/
    /*Selection Atributes*/
    /*********************/
    bool                 IMT_Pickable ;//This Object can be Picked during Rendering
    bool                 IMT_Selected ;//This Object are selected.
    uint                 IMT_PickingId;//Temporary ID during Picking Process

    /*****************************/
    /*Identification Atributes   */
    /*****************************/
    int                  IMT_Type      ;//Object Type
    QString              IMT_Name      ;//Object Name

    /*********************/
    /*Geometry Atributes */
    /*********************/
    CIMTMesh             IMT_Geometry ;//Standard Geometry
    vector<uint>         IMT_Textures ;//Linked Textures
    vector<uint>         IMT_Materials;//Linked Materials

    void LinkTexture (uint pIMT_TextureId ){IMT_Textures.push_back(pIMT_TextureId);}
    void LinkMaterial(uint pIMT_MaterialId){IMT_Materials.push_back(pIMT_MaterialId);}

};

#endif // CIMTOBJECT_H
