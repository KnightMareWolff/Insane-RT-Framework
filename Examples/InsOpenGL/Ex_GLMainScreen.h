/************************************************************************/
/*Project              :Insane RT Framework                             */
/*Creation Date/Author :William Wolff - 02/18/2021                      */
/*                                                                      */
/*Copyright (c) 2004 William Wolff. All rights reserved                 */
/************************************************************************/
#ifndef CGLMAINSCREEN_H
#define CGLMAINSCREEN_H

#include <QWidget>
#include "INSGL.h"
#include "INSCG.h"

class CGLMainScreen : public QOpenGLWindow
{
    Q_OBJECT

public:
     CGLMainScreen();
    ~CGLMainScreen();

     void BuildScene();

protected slots:
     void RenderScene();
     void UpdateScene();

protected:
     void initializeGL() override;
     void resizeGL(int w, int h) override;
     void paintGL() override;
     void mousePressEvent(QMouseEvent *) override;
     void mouseReleaseEvent(QMouseEvent *) override;
     void keyPressEvent(QKeyEvent *event) override;
     void mouseMoveEvent(QMouseEvent *) override;

private:
     INSGL *pGLInterface;
     INSCG *pCGInterface;

     //Example 3D Objects
     vector<CIMT3DObject *> p3DObjects;
     vector<CIGLTexture  *> p3DTextures;
     vector<CIGLMaterial *> p3DMaterials;
     vector<CIGLLight    *> p3DLights;

     CIGLCamera* p3DCamera;

     //OpenGL Control
     QOpenGLContext *mCtxt;     //ponteiro para o contexto

     QTimer        *timer;
     QElapsedTimer *elapsedtimer;
     int           elapsed;
     float         TimeElapsed;
     float         oldPosX,
                   oldPosY;
     float         actPosX,
                   actPosY;
     bool          mouseBtnPress;
     bool          mInitialized;
     QCursor       mCursor;
     int           vMinor,
                   vMajor;
     int           iCounter;
};
#endif // CGLMAINSCREEN_H
