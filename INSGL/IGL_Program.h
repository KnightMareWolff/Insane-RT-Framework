/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef ISH_PROGRAM_H
#define ISH_PROGRAM_H

#include "INSGL_global.h"
#include "IGL_VertexShader.h"
#include "IGL_FragmentShader.h"
#include "IGL_GeometryShader.h"
#include "IGL_TessCtrlShader.h"
#include "IGL_TessEvalShader.h"
#include "IGL_ComputeShader.h"

class CIGLProgram : public QOpenGLShaderProgram
{
public:
    CIGLProgram();
    void AddShader  (QString pPath  , int pShaderType );
    void AddFeedBack(bool bFeedBack                   );

    QString IGL_ProgramName;//Shader Program Identification Name
    bool    IGL_Feedback   ;//Inform if we want use Transform Feedbacks
};

#endif // ISH_PROGRAM_H
