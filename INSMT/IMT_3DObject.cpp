#include "IMT_3DObject.h"

CIMT3DObject::CIMT3DObject()
{
    IMT_Pos   =CIMTVector( 0.0f, 0.0f, 0.0f);
    IMT_RefPos=CIMTVector( 0.0f, 0.0f, 0.0f);
    IMT_Rot   =CIMTVector( 0.0f, 0.0f, 0.0f);
    IMT_RefRot=CIMTVector( 0.0f, 0.0f, 0.0f);
    IMT_Scl   =CIMTVector( 1.0f, 1.0f, 1.0f);
    IMT_RefScl=CIMTVector( 0.0f, 0.0f, 0.0f);
    IMT_Dim   =CIMTVector( 5.0f, 5.0f, 5.0f);
}

CIMT3DObject::CIMT3DObject( const CIMT3DObject & copy )
{
    IMT_View      = copy.IMT_View ;
    IMT_Up        = copy.IMT_Up ;
    IMT_Pos       = copy.IMT_Pos ;
    IMT_Rot       = copy.IMT_Rot ;
    IMT_Scl       = copy.IMT_Scl ;
    IMT_RefPos    = copy.IMT_RefPos ;
    IMT_RefRot    = copy.IMT_RefRot ;
    IMT_RefScl    = copy.IMT_RefScl ;
    IMT_Dim       = copy.IMT_Dim ;
    IMT_MtxTransf = copy.IMT_MtxTransf ;
    IMT_MtxLocal  = copy.IMT_MtxLocal ;
    IMT_Pickable  = copy.IMT_Pickable ;
    IMT_Selected  = copy.IMT_Selected ;
    IMT_PickingId = copy.IMT_PickingId ;
    IMT_Type      = copy.IMT_Type ;
    IMT_Name      = copy.IMT_Name ;
    IMT_Geometry  = copy.IMT_Geometry ;
    IMT_Textures  = copy.IMT_Textures;
    IMT_Materials = copy.IMT_Materials;

}

CIMT3DObject& CIMT3DObject::operator=  ( const CIMT3DObject& opr )
{
    IMT_View      = opr.IMT_View ;
    IMT_Up        = opr.IMT_Up ;
    IMT_Pos       = opr.IMT_Pos ;
    IMT_Rot       = opr.IMT_Rot ;
    IMT_Scl       = opr.IMT_Scl ;
    IMT_RefPos    = opr.IMT_RefPos ;
    IMT_RefRot    = opr.IMT_RefRot ;
    IMT_RefScl    = opr.IMT_RefScl ;
    IMT_Dim       = opr.IMT_Dim ;
    IMT_MtxTransf = opr.IMT_MtxTransf ;
    IMT_MtxLocal  = opr.IMT_MtxLocal ;
    IMT_Pickable  = opr.IMT_Pickable ;
    IMT_Selected  = opr.IMT_Selected ;
    IMT_PickingId = opr.IMT_PickingId ;
    IMT_Type      = opr.IMT_Type ;
    IMT_Name      = opr.IMT_Name ;
    IMT_Geometry  = opr.IMT_Geometry ;
    IMT_Textures  = opr.IMT_Textures;
    IMT_Materials = opr.IMT_Materials;

    return *this;
}

void CIMT3DObject::Translate(CIMTVector pTransf, bool Incremento)
{
    //For Translation we dont use references, so just pass pTransf for the reference vector.
    PushTransformation(0,
                       Incremento,
                       pTransf   ,
                       pTransf   );
}

void CIMT3DObject::Rotate(bool pControlPoint,CIMTVector  pTransf,CIMTVector  pControl)
{

    PushTransformation(1,
                       pControlPoint,
                       pTransf,
                       pControl);
}

void CIMT3DObject::Scale(bool pControlPoint,CIMTVector  pTransf,CIMTVector  pControl)
{
    PushTransformation(2,
                       pControlPoint,
                       pTransf,
                       pControl);
}

void CIMT3DObject::PushTransformation(uint pIMT_Type,
                                      bool pIMT_UseReference,
                                      CIMTVector  pIMT_Amount,
                                      CIMTVector  pIMT_Reference)
{
    IMT_TransfQueue.enqueue(CIMT3DTransformation(pIMT_Type,pIMT_UseReference,pIMT_Amount,pIMT_Reference));
}

bool CIMT3DObject::PopTransformation (uint        &pIMT_Type,
                                      bool        &pIMT_UseReference,
                                      CIMTVector  &pIMT_Amount,
                                      CIMTVector  &pIMT_Reference)
{
   if(IMT_TransfQueue.empty())return false;

   CIMT3DTransformation dequeued = IMT_TransfQueue.dequeue();
   pIMT_Type          = dequeued.IMT_Type;
   pIMT_UseReference  = dequeued.IMT_UseReference;
   pIMT_Amount        = dequeued.IMT_Amount;
   pIMT_Reference     = dequeued.IMT_Reference;
   return true;
}



