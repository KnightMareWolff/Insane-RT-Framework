#include "Ex_GLMainScreen.h"

CGLMainScreen::CGLMainScreen()
{
    create();
    /***********************************************/
    /*Informa que teremos uma superficie OpenGL    */
    /***********************************************/
    setSurfaceType(OpenGLSurface);
    /***********************************************/
    /*Configura o nome da janela                   */
    /***********************************************/
    setTitle(tr("Insane RT Framework"));
    setCursor(mCursor);
    /***********************************************/
    /*Conecta os Slots de Janela(Ver referencias Qt*/
    /***********************************************/
    connect(this, SIGNAL(widthChanged (int)), this, SLOT(resizeGL(int,int)));
    connect(this, SIGNAL(heightChanged(int)), this, SLOT(resizeGL(int,int)));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(RenderScene()));
    timer->start();

    elapsedtimer = new QElapsedTimer();
    elapsedtimer->start();

    mouseBtnPress=false;
    setIcon(QIcon("world/Icones/insicon.png"));

}

CGLMainScreen::~CGLMainScreen()
{
}

void CGLMainScreen::initializeGL()
{
    makeCurrent();

    //mCtxt = context();
    //mCtxt->shareContext();
    //mCtxt->format().setSamples(4);

    pGLInterface = new INSGL(true);
  //pGLInterface = new INSGL(mCtxt);
    pCGInterface = new INSCG(     );

    //Set Glogal Computational Geometry Distances and Angles
    pCGInterface->SetNear(1.0f    );
    pCGInterface->SetFar (90000.0f);
    pCGInterface->Set_FOV(90.0f   );

    BuildScene();

    mInitialized = true;

    setWidth (800);
    setHeight(600);
}

void CGLMainScreen::BuildScene()
{

    //Create the Main ScreenCamera
    p3DCamera = pGLInterface->AddCamera("MainCamera");

    //Reserve space and Create the Base Objects
    p3DObjects.push_back(pGLInterface->Add3DObject(QString("Cube01" )));
    p3DObjects.push_back(pGLInterface->Add3DObject(QString("SkyBox" )));
    p3DObjects.push_back(pGLInterface->Add3DObject(QString("Terrain")));

    //Create and Add the Materials and Textures for the Cube
    uint MatId,TextId,LgtId;
    pGLInterface->AddMaterial("CubeMaterial",IGL_MATERIAL_TEXTURE,MatId);
    pGLInterface->AddTexture("CubeTexture","world/Texturas/Caixa.bmp",IGL_TEXTURE_LINEAR,TextId);

    //Create and Add the Materials and Textures for the Sky
    uint SkyMatId,SkyTextId;
    pGLInterface->AddMaterial("SkyMaterial",IGL_MATERIAL_CUBEMAP,SkyMatId);
    pGLInterface->AddCubeMapTexture("SkyTexture",
                                    "world/Sky-box/WhiteDwarf/wd-right.png",
                                    "world/Sky-box/WhiteDwarf/wd-left.png",
                                    "world/Sky-box/WhiteDwarf/wd-top.png",
                                    "world/Sky-box/WhiteDwarf/wd-bottom.png",
                                    "world/Sky-box/WhiteDwarf/wd-back.png",
                                    "world/Sky-box/WhiteDwarf/wd-front.png" ,
                                    SkyTextId);

    uint TerrainMatId,TerrainTextId;
    pGLInterface->AddMaterial("TerrainMaterial",IGL_MATERIAL_TEXTURE,TerrainMatId);
    pGLInterface->AddTexture("TerrainTexture","world/Texturas/Caixa.bmp",IGL_TEXTURE_GEN_ST,TerrainTextId);

    //Create the Lights for the Enviroment
    pGLInterface->AddLight("Light01",LgtId);

    //Now we have all the elements of the scene stored for rendering we need setup the geometry and materials
    //Properly to make possible the Render works fine....

    //Create a simple Cube and Link with the Assets(Since the main Rendering is Clockwise we create a Cube in CounterClockwise order.
    pCGInterface->CreateCube(p3DObjects[0]->IMT_Geometry,CIMTVector(0,0,10),CIMTVector(5.0f,5.0f,5.0f));
    //Translate the Cube for the created Center and link with assets...
    p3DObjects[0]->SetType(IMT_OBJECT_TYPE_CUBE);
    p3DObjects[0]->LinkMaterial(MatId);
    p3DObjects[0]->LinkTexture(TextId);

    //The Sky is a Cube with all the faces inward, so... the Computational geometry component take handle... ;)
    pCGInterface->CreateSky (p3DObjects[1]->IMT_Geometry,CIMTVector(0,0,0));
    p3DObjects[1]->SetType(IMT_OBJECT_TYPE_SKY);
    p3DObjects[1]->LinkMaterial(SkyMatId);
    p3DObjects[1]->LinkTexture(SkyTextId);

    //The Sky is a Cube with all the faces inward, so... the Computational geometry component take handle... ;)
    pCGInterface->CreateTerrain(p3DObjects[2]->IMT_Geometry,CIMTVector(0,0,0));
    p3DObjects[2]->SetType(IMT_OBJECT_TYPE_TERRAIN);
    p3DObjects[2]->LinkMaterial(TerrainMatId);
    p3DObjects[2]->LinkTexture(TerrainTextId);

    //After all geometry and resources initialization we can ask for GPU Store It!
    pGLInterface->SingleShotHWTextures();//This Store all the textures in GPU
    pGLInterface->SingleShotHWObjects ();//This Store all the geometry in GPU VBO´s

}
void CGLMainScreen::paintGL()
{
    /*************************************/
    /*Paint only initialized enviroments!*/
    /*************************************/
    if(mInitialized)
    {
       GLsync PaintID;
       //make the INSGL Context the Current Context, just to avoid too much SO Dependancy...
       pGLInterface->GetContext()->makeCurrent(this);
       pGLInterface->FenceSync(PaintID);
       /**********************************************/
       /*Send Hardware DC´s to the Optimization CL   */
       /**********************************************/
       //p3DCenario->UpdateHardwareDC();

       UpdateScene();

       /*********************************************/
       /*Render the Scene Stored in the GL Component*/
       /*********************************************/
       pGLInterface->RenderScene();

       pGLInterface->WaitSync(PaintID);
       /***********************************************/
       /*swap the framebuffers with the OpenGL Surface*/
       /***********************************************/
       pGLInterface->GetContext()->swapBuffers(this);

       //here we can get a Framebuffer if we want...
       //QImage buffer = grabFramebuffer();
       //buffer.save("teste.jpg");
    }
}

void CGLMainScreen::resizeGL(int w, int h)
{
    /**********************************************/
    /*in the 3 overrided GL Functions we must use */
    /*the Format makecurrent function             */
    /**********************************************/
    pGLInterface->GetContext()->makeCurrent(this);

    /********************************************************/
    /*Informthe new screen size and pass CG Global Distances*/
    /*So..the GLRendering can calculate properly the camera */
    /*LookAt provided by the perspective Calculus.          */
    /********************************************************/
    if(mInitialized)
    {
        /*****************************/
        /*Set the Camera Frustrum    */
        /*****************************/
        p3DCamera->SetWidth(h);
        p3DCamera->SetHeight(w);

        //We are using the CG Distances to mantain the geometry and Rendering at the same world coordinate System as possible...
        p3DCamera->SetPerspective(pCGInterface->GetNear(),
                                  pCGInterface->GetFar(),
                                  IGL_PROJECTION_PERSP,
                                  pCGInterface->Get_FOV());
    }
}

void CGLMainScreen::RenderScene()
{
   TimeElapsed  = elapsedtimer->restart();
   TimeElapsed /= 1000;
   paintGL();
}

void CGLMainScreen::UpdateScene()
{
    int i=0;

   //p3DObjects[0]->Translate(CIMTVector(0,0,50),false);
   //p3DObjects[0]->Rotate(true,CIMTVector(0,1,0),CIMTVector(0,0,50));

}

void CGLMainScreen::keyPressEvent(QKeyEvent *event)
{
   switch(event->key())
   {
       case Qt::Key_A :{p3DCamera->Strafe(-50.0f);}break;
       case Qt::Key_D :{p3DCamera->Strafe( 50.0f);}break;
       case Qt::Key_S :{p3DCamera->Move  (-50.0f);}break;
       case Qt::Key_W :{p3DCamera->Move  ( 50.0f);}break;
       case Qt::Key_R :{p3DObjects[0]->Rotate(false,CIMTVector(0,1,0),CIMTVector(0,0,0));}break;
       case Qt::Key_T :{p3DObjects[0]->Translate(CIMTVector(0,0,-0.5),true);}break;
       case Qt::Key_Escape:
       {
          //bRodando = false;
          exit(0);
       }
   }  
   //qWarning() << "teste de recorrencia!";
}


void CGLMainScreen::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point,centro;
    centro.rx() = width ()>>1;
    centro.ry() = height()>>1;
    point= event->pos();
    actPosX = (float)(point.y() - oldPosY ) / 3.0f;
    actPosY = (float)(point.x() - oldPosX ) / 3.0f;
    if(mInitialized)
    {
       if(mouseBtnPress)
       {
          p3DCamera->Follow(CIMTVector2(actPosX,actPosY));
       }
    }
    oldPosX= point.x();
    oldPosY= point.y();
}

void CGLMainScreen::mousePressEvent(QMouseEvent *event)
{
    QPoint point;

    point = event->pos();
    //centro.rx() = width() / 2;
    //centro.ry() = height()/ 2;

    //p3DCenario->Seleciona(point.x(),point.y());

    //mCursor.setPos(centro);
    //oldPosX = centro.x();
    //oldPosY = centro.y();

    oldPosX = point.x();
    oldPosY = point.y();

    mouseBtnPress = true;
}
void CGLMainScreen::mouseReleaseEvent(QMouseEvent *event)
{
    QPoint point;

    point= event->pos();

    oldPosX= point.x();
    oldPosY= point.y();

    mouseBtnPress = false;
}

