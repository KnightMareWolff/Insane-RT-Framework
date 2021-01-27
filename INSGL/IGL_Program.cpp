/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#include "IGL_Program.h"

CIGLProgram::CIGLProgram()
{
   IGL_ProgramName = "Programa Default";
   IGL_Feedback    = true;
}

void CIGLProgram::AddShader(QString pPath, int pShaderType)
{

  QOpenGLShader *shader;
  QString        log;

  switch (pShaderType)
  {
     case IGL_VERTEX_SHADER_TYPE:
     {
        shader = new CIGLVertexShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case IGL_FRAGMENT_SHADER_TYPE:
     {
        shader = new CIGLFragmentShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case IGL_GEOMETRY_SHADER_TYPE:
     {
        shader = new CIGLGeometryShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case IGL_TESSCTRL_SHADER_TYPE:
     {
        shader = new CIGLTessCtrlShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case IGL_TESSEVAL_SHADER_TYPE:
     {
        shader = new CIGLTessEvalShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
     case IGL_COMPUTE_SHADER_TYPE:
     {
        shader = new CIGLComputeShader;
        if(!shader->compileSourceFile(pPath))
        {
           log = shader->log();
        }
     }break;
  }

  if(!addShader(shader))
  {
      //mapeamento de erro;
  }
}

void CIGLProgram::AddFeedBack(bool bFeedBack)
{
    IGL_Feedback = bFeedBack;
}
