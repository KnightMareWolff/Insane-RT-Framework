/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/
#include "IGL_Camera.h"

CIGLCamera::CIGLCamera()
{
    IGL_Pos                  = CIMTVector( 0.00f, 0.00f ,0.00f);
    IGL_View                 = CIMTVector( 0.00f, 0.00f ,1.00f);
    IGL_Up                   = CIMTVector( 0.00f, 1.00f ,0.00f);
    IGL_Speed                = 25.0f;
    IGL_FrameInterval        = 0.01f;
    IGL_FPS                  = 30;
    IGL_LastTimestamp		 = 0;
    IGL_FrameTimestamp       = 0;
    IGL_ScreenWidth          = 800;
    IGL_ScreenHeight         = 600;
    IGL_FOV                  = 90.0f;
    IGL_MainCamera           = true;
}

CIGLCamera::CIGLCamera(const CIGLCamera & copy  )
{
    IGL_Name          =copy.IGL_Name ;
    IGL_Speed         =copy.IGL_Speed ;
    IGL_FrameInterval =copy.IGL_FrameInterval ;
    IGL_Pos           =copy.IGL_Pos ;
    IGL_View          =copy.IGL_View ;
    IGL_Up            =copy.IGL_Up ;
    IGL_Strafe        =copy.IGL_Strafe ;
    IGL_FPS           =copy.IGL_FPS ;
    IGL_FOV           =copy.IGL_FOV ;
    IGL_Near          =copy.IGL_Near ;
    IGL_Far           =copy.IGL_Far ;
    IGL_LastTimestamp =copy.IGL_LastTimestamp ;
    IGL_FrameTimestamp=copy.IGL_FrameTimestamp ;
    IGL_Clock         =copy.IGL_Clock ;
    IGL_ProgramId     =copy.IGL_ProgramId ;
    IGL_ScreenHeight  =copy.IGL_ScreenHeight ;
    IGL_ScreenWidth   =copy.IGL_ScreenWidth ;
    IGL_ProjectionType=copy.IGL_ProjectionType ;
    IGL_MainCamera    =copy.IGL_MainCamera ;
}

CIGLCamera &CIGLCamera::operator=(const CIGLCamera& opr)
{
    IGL_Name          =opr.IGL_Name ;
    IGL_Speed         =opr.IGL_Speed ;
    IGL_FrameInterval =opr.IGL_FrameInterval ;
    IGL_Pos           =opr.IGL_Pos ;
    IGL_View          =opr.IGL_View ;
    IGL_Up            =opr.IGL_Up ;
    IGL_Strafe        =opr.IGL_Strafe ;
    IGL_FPS           =opr.IGL_FPS ;
    IGL_FOV           =opr.IGL_FOV ;
    IGL_Near          =opr.IGL_Near ;
    IGL_Far           =opr.IGL_Far ;
    IGL_LastTimestamp =opr.IGL_LastTimestamp ;
    IGL_FrameTimestamp=opr.IGL_FrameTimestamp ;
    IGL_Clock         =opr.IGL_Clock ;
    IGL_ProgramId     =opr.IGL_ProgramId ;
    IGL_ScreenHeight  =opr.IGL_ScreenHeight ;
    IGL_ScreenWidth   =opr.IGL_ScreenWidth ;
    IGL_ProjectionType=opr.IGL_ProjectionType ;
    IGL_MainCamera    =opr.IGL_MainCamera ;

    return (*this);
}

void CIGLCamera::Initialize()
{
    IGL_Pos                  =CIMTVector(0.00f,0.00f,0.00f);
    IGL_View                 =CIMTVector(0.00f,0.00f,1.00f);
    IGL_Up                   =CIMTVector(0.00f,1.00f,0.00f);
    IGL_Speed                =25.0f;
    IGL_FrameInterval        =0.01f;
    IGL_FPS                  =0;
    IGL_LastTimestamp		 =0;
    IGL_FrameTimestamp       =0;
    IGL_ScreenWidth          =800;
    IGL_ScreenHeight         =600;
    IGL_FOV                  =90.0f;
}

/************************************************************/
/*Nome do Método      : SetaCamera                          */
/*                                                          */
/*Objetivo            : Seta a Posição em que a camera se   */
/*                      encontra.                           */
/************************************************************/
void CIGLCamera::SetCamera(CIMTVector pIGL_Pos,CIMTVector pIGL_View,CIMTVector pIGL_Up)
{
   IGL_Pos  = pIGL_Pos;
   IGL_View = pIGL_View;
   IGL_Up   = pIGL_Up;
}



/************************************************************/
/*Nome do Método      : PegaDirecao                         */
/*                                                          */
/*Objetivo            : Pega a direção onde a camera está   */
/*                      apontando.                          */
/************************************************************/
CIMTVector CIGLCamera::GetDirection()
{
    CIMTVector Direcao;

    Direcao=IGL_View - IGL_Pos;

    return Direcao;
}
/**************************************************************/
/*Nome do Método      : MoverCamera                           */
/*                                                            */
/*Objetivo            : Move a camera para a direção desejada */
/**************************************************************/
void CIGLCamera::Move(float pIGL_AxisDir)
{

   CIMTVector  i3dDir;

   i3dDir=GetDirection();
   i3dDir.Normalize ();

   Update(i3dDir,pIGL_AxisDir);
}

/************************************************************/
/*Nome do Método      : AtualizaCamera                      */
/*                                                          */
/*Objetivo            : Atualiza a camera                   */
/************************************************************/
void CIGLCamera::Update(CIMTVector pIGL_Direction, float  pIGL_AxisDir)
{
   pIGL_AxisDir = pIGL_AxisDir / IGL_FPS;

   IGL_Pos  += (pIGL_Direction * pIGL_AxisDir);
   IGL_View += (pIGL_Direction * pIGL_AxisDir);
}


/************************************************************/
/*Nome do Método      : Rodar                               */
/*                                                          */
/*Objetivo            : Roda a camera na direção desejada   */
/************************************************************/
void CIGLCamera::Rotate(float pIGL_DirAngle , CIMTVector pIGL_Axis)
{


   CIMTVector i3dDirVisao ;
   CIMTQuat qRotacao, qVisao, qNovaVisao;

   qRotacao.Rotaciona(pIGL_DirAngle, pIGL_Axis.x, pIGL_Axis.y, pIGL_Axis.z);

   i3dDirVisao     = GetDirection();

   qVisao.x = i3dDirVisao.x ;
   qVisao.y = i3dDirVisao.y ;
   qVisao.z = i3dDirVisao.z ;
   qVisao.w = 0;

   qNovaVisao = ((qRotacao * qVisao) * qRotacao.Conjugar());

   IGL_View.x = IGL_Pos.x + qNovaVisao.x;
   IGL_View.y = IGL_Pos.y + qNovaVisao.y;
   IGL_View.z = IGL_Pos.z + qNovaVisao.z;

}

void CIGLCamera::Follow(CIMTVector2 pIGL_Point)
{

    float i3dAnguloY  = 0.0f;
    float i3dAnguloZ  = 0.0f;
    float i3dRotacaoX = 0.0f;

    CIMTVector i3dVetTemp , i3dEixo;

    i3dAnguloY = -pIGL_Point.y;
    i3dAnguloZ = -pIGL_Point.x;

    i3dRotacaoX -= i3dAnguloZ;

    if(i3dRotacaoX >  1.0f){ i3dRotacaoX =  1.0f; }
    if(i3dRotacaoX < -1.0f){ i3dRotacaoX = -1.0f; }

    i3dVetTemp     = GetDirection();
    i3dEixo        = i3dVetTemp.Cross(IGL_Up);
    i3dEixo.Normalize();


    Rotate( i3dAnguloZ,i3dEixo);
    Rotate( i3dAnguloY,CIMTVector(0,1,0));

}

/************************************************************/
/*Nome do Método      : CameraStrafe                        */
/*                                                          */
/*Objetivo            : Realiza o strafing da camera        */
/*                                                          */
/************************************************************/
void CIGLCamera::Strafe(float pIGL_Strafe)
{

   CIMTVector Direcao;

   Direcao=GetDirection();
   Direcao.Normalize ();

   IGL_Strafe=Direcao.Cross(IGL_Up);

   Update(IGL_Strafe,pIGL_Strafe);
}


/***************************************************************/
/*Nome do Método      : PosicionaCamera                        */
/*                                                             */
/*Objetivo            : Posiciona a camera levando-se em con-  */
/*                      ideração todas as suas coordenadas     */
/*                                                             */
/***************************************************************/
//void CIGLCamera::PosicionaCamera()
//{
//    execGL(IGL_SH_LOOKAT,I3D_CameraProgramId,IGL_Pos,IGL_View,IGL_Up);
//    CalculaTempo();
//}

/****************************************************************/
/*Nome do Método      : PosicionaCamera                         */
/*                                                              */
/*Objetivo            : Posiciona a camera levando-se em con-   */
/*                      ideração todas as suas coordenadas      */
/*                                                              */
/****************************************************************/
//void CIGLCamera::PosicionaCamera(float &pI3D_CurrentTime, float &pI3D_TimeLapsed)
//{
//    execGL(IGL_SH_LOOKAT,I3D_CameraProgramId,IGL_Pos,IGL_View,IGL_Up);
//    CalculaTempo();
//
//    pI3D_CurrentTime = IGL_FrameTimestamp;
//    pI3D_TimeLapsed  = IGL_FrameInterval;
//
//}


/*****************************************************************/
/*Nome do Método      : CalculaFrameRate                         */
/*                                                               */
/*Objetivo            : Calcula nosso FPS , neste caso estamos   */
/*                      utilizando para calcular a velocidade    */
/*                      em algumas situações...                  */
/*                                                               */
/*****************************************************************/
void CIGLCamera::CalcTime()
{
    float i3dTempoAtual = (float)clock()/CLOCKS_PER_SEC;

    IGL_FrameInterval       =  i3dTempoAtual - IGL_FrameTimestamp;
    IGL_FPS                 =  1.0f / IGL_FrameInterval;
    IGL_FrameTimestamp      =  i3dTempoAtual;

    //qWarning() << QString("FPS: %1 POS: X-%2 Y-%3 Z-%4").arg(IGL_FPS).arg(IGL_Pos.x).arg(IGL_Pos.y).arg(IGL_Pos.z);
}

/*****************************************************************/
/*Nome do Método      : ResetaCamera                             */
/*                                                               */
/*Objetivo            : Inicializa as variaveis responsaveis     */
/*                      pelos valores de tempo utilizados para   */
/*                      o calculo da velocidade.                 */
/*                                                               */
/*****************************************************************/
void CIGLCamera::Reset()
{
   IGL_Pos              = CIMTVector(100.00f,300.00f,100.00f);
   IGL_View             = CIMTVector(0.00f,0.00f,0.00f);
   IGL_Up               = CIMTVector(0.00f,1.00f,0.00f);
   IGL_Speed            = 0.5f;
   IGL_FrameInterval    = 0.0f;
   IGL_FPS              = 0;
   IGL_LastTimestamp	= 0;
   IGL_FrameTimestamp   = 0;
   IGL_FOV              = 90.0f;
   IGL_MainCamera       = false;
}


void CIGLCamera::SetPerspective(float pIGL_Near,float pIGL_Far,int pIGL_Projection,float pFOV)
{
    if(IGL_ScreenWidth == 0)IGL_ScreenWidth = 1;
    IGL_Near           = pIGL_Near;
    IGL_Far            = pIGL_Far;
    IGL_ProjectionType = pIGL_Projection;
    IGL_FOV            = pFOV;
}

