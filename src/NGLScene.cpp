#include <QMouseEvent>
#include <QGuiApplication>


#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include <initializer_list>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/ShaderLib.h>
#include <ngl/Material.h>
#include <ngl/VAOPrimitives.h>

NGLScene::NGLScene( QWidget *_parent ) : QOpenGLWidget( _parent )
{
    setFocus();
    this->resize(_parent->size());
    m_numOfAddBoids = 0;
    m_numOfRemoveBoids = 0;
    m_targetActive = false;
    m_weightMap ={ {"seekWeight", 0.0f},
                   {"alignmentWeight", 0.0f},
                   {"separationWeight", 0.0f},
                   {"cohesionWeight", 0.0f} };

   m_attributes = { {"maxSpeed", 0.001f},
                    {"maxForce", 0.001f},
                    {"awarenessRadius", 0.01f} };
}


NGLScene::~NGLScene()
{
  std::cout<<"Shutting down NGL, removing VAO's and Shaders\n";
}



void NGLScene::resizeGL(int _w , int _h)
{
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
  // we need to initialise the NGL lib which will load all of the OpenGL functions, this must
  // be done once we have a valid GL context but before we call any GL commands. If we dont do
  // this everything will crash
  ngl::NGLInit::instance();
  glClearColor(0.5f, 0.5f, 0.5f, 1.0f);			   // Grey Background
  // enable depth testing for drawfing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  initializeCamera({50, 50, 50}, {0, 0, 0}, {0, 1, 0});
  initializeShader();
  createLights();
  m_container.reset(new ngl::BBox(ngl::Vec3(0.0, 25.0, 0.0), 50, 50, 50));
  m_testFlock.reset(new Flock(m_cam, "BoidShader", m_mouseGlobalTX));

  ngl::VAOPrimitives *prim = ngl::VAOPrimitives::instance();
  prim->createLineGrid("groundPlane", 100, 100, 50);

  m_updateTimer=startTimer(40);
  startTimer(10);

}

void NGLScene::initializeShader()
{
    constexpr auto shaderProgram = "BoidShader";
    constexpr auto vertShader = "BoidVert";
    constexpr auto fragShader = "BoidFrag";

    ngl::ShaderLib* boidShader = ngl::ShaderLib::instance();
    // Creating shader used for the boids, attaching source,
    // compiling, attaching to host program and linking
    boidShader->createShaderProgram(shaderProgram);
    boidShader->attachShader(vertShader, ngl::ShaderType::VERTEX);
    boidShader->attachShader(fragShader, ngl::ShaderType::FRAGMENT);
    boidShader->loadShaderSource(vertShader, "shaders/vertShader.glsl");
    boidShader->loadShaderSource(fragShader, "shaders/fragShader.glsl");
    boidShader->compileShader(vertShader);
    boidShader->compileShader(fragShader);
    boidShader->attachShaderToProgram(shaderProgram, vertShader);
    boidShader->attachShaderToProgram(shaderProgram, fragShader);
    boidShader->linkProgramObject(shaderProgram);

    (*boidShader)[shaderProgram]->use();
    ngl::Material m(ngl::STDMAT::GOLD);
    m.loadToShader("material");

    boidShader->setUniform("viewerPos", m_cam.getEye().toVec3());
}

void NGLScene::initializeCamera(ngl::Vec3 _from, ngl::Vec3 _to, ngl::Vec3 _up)
{
    m_cam.setShape(45.0f, 720.0f / 576.0f, 0.005f, 350.0f);
    m_cam.set(_from, _to, _up);
}

void NGLScene::loadMatrixToShader(ngl::Mat4 _modelTransform)
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["BoidShader"]->use();
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    //_modelTransform.addPosition(0.0, 300.0, 0.0);
    M= m_mouseGlobalTX * _modelTransform;
    MV=m_cam.getViewMatrix()*M;
    MVP=m_cam.getProjectionMatrix() *MV;
    normalMatrix=MV;
    normalMatrix.inverse();
    shader->setUniform("MV",MV);
    shader->setUniform("MVP",MVP);
    shader->setUniform("normalMatrix",normalMatrix);
    shader->setUniform("M",M);
}

void NGLScene::createLights()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["BoidShader"]->use();
    //ngl::Mat4 iv = m_cam.getViewMatrix();
    //iv.transpose();
    ngl::Light light( ngl::Vec3( -2, 5, 2 ), ngl::Colour( 1, 1, 1, 1 ), ngl::Colour( 1, 1, 1, 1 ), ngl::LightModes::POINTLIGHT );
    //light.setTransform( iv );
    // load these values to the shader as well
    light.loadToShader( "light" );
}
void NGLScene::paintGL()
{
  // clear the screen and depth buffer
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glViewport(0,0,m_win.width,m_win.height);

  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  (*shader)["BoidShader"]->use();

  //CAMERA TRANSFORMATION
  // Rotation based on the mouse position for our global transform
   ngl::Mat4 rotX;
   ngl::Mat4 rotY;
   // create the rotation matrices
   rotX.rotateX( m_win.spinXFace );
   rotY.rotateY( m_win.spinYFace );
   // multiply the rotations
   m_mouseGlobalTX = rotX * rotY;
   // add the translations
   m_mouseGlobalTX.m_m[ 3 ][ 0 ] = m_modelPos.m_x;
   m_mouseGlobalTX.m_m[ 3 ][ 1 ] = m_modelPos.m_y;
   m_mouseGlobalTX.m_m[ 3 ][ 2 ] = m_modelPos.m_z;
   // assign
   m_testFlock->m_mouseTX = m_mouseGlobalTX;

   //Environment objects
   m_envTransform.reset();
   loadMatrixToShader(m_envTransform.getMatrix());
   ngl::VAOPrimitives::instance()->draw("groundPlane");
   loadMatrixToShader(m_envTransform.getMatrix());
   m_container->draw();

   //TARGET
   if (m_targetActive)
   {
       m_goalTransform.setPosition(m_goalPos);
       loadMatrixToShader(m_goalTransform.getMatrix());
       ngl::VAOPrimitives::instance()->draw("football");
   }
   //TEST FLOCK
  m_goalTransform.getMatrix();
  m_testFlock->drawFlock(m_targetActive, m_attributes, m_weightMap, m_goalPos, m_container);

  emit numBoidsChanged(m_testFlock->getFlockSize());
}


void NGLScene::timerEvent(QTimerEvent *_event )
{
  if(_event->timerId() == m_updateTimer)
  {
    return;
  }
  update();
}


//-----------SLOTS-----------
void NGLScene::setAddBoids(int _numOfBoids)
{
    m_numOfAddBoids = _numOfBoids;
}

void NGLScene::setRemoveBoids(int _numOfBoids)
{
    m_numOfRemoveBoids = _numOfBoids;
}

void NGLScene::addBoids()
{
    m_testFlock->addBoid(m_numOfAddBoids, m_container);
    update();
}

void NGLScene::removeBoids()
{
    m_testFlock->removeBoid(m_numOfRemoveBoids);
    update();
}

void NGLScene::setSeekWeight(int _weight)
{
    m_weightMap.at("seekWeight") = static_cast<float>(_weight) * 0.01;
}

void NGLScene::setCohesion(int _weight)
{
    m_weightMap.at("cohesionWeight") = static_cast<float>(_weight) * 0.01;
}

void NGLScene::setSeparation(int _weight)
{
    m_weightMap.at("separationWeight") = static_cast<float>(_weight) * 0.01;
}

void NGLScene::setAlignment(int _weight)
{
   m_weightMap.at("alignmentWeight") = static_cast<float>(_weight) * 0.01;
}

void NGLScene::setMaxSpeed(int _maxSpeed)
{
    m_attributes.at("maxSpeed") =  static_cast<float>(_maxSpeed) * 0.001;
}

void NGLScene::setMaxForce(int _maxForce)
{
    m_attributes.at("maxForce") =  static_cast<float>(_maxForce) * 0.0001;
}

void NGLScene::setAwareness(int _awarenessRadius)
{
    m_attributes.at("awarenessRadius") =  static_cast<float>(_awarenessRadius) * 0.01;
}

void NGLScene::activateTarget(bool _active)
{
    m_targetActive = _active;
}

void NGLScene::setGoalPosX(double _posX)
{
    m_goalPos.m_x = static_cast<float>(_posX);
}

void NGLScene::setGoalPosY(double _posY)
{
    m_goalPos.m_y = static_cast<float>(_posY);
}

void NGLScene::setGoalPosZ(double _posZ)
{
    m_goalPos.m_z = static_cast<float>(_posZ);
}
