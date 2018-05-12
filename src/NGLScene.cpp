#include <QMouseEvent>
#include <QGuiApplication>

#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <iostream>
#include <ngl/Camera.h>
#include <ngl/Light.h>
#include <ngl/ShaderLib.h>
#include <ngl/Material.h>
#include <initializer_list>
#include <ngl/VAOPrimitives.h>

NGLScene::NGLScene()
{
  // re-size the widget to that of the parent (in this case the GLFrame passed in on construction)
  setTitle("Flocking System s4920723");
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
  // enable depth testing for drawing
  glEnable(GL_DEPTH_TEST);
  // enable multisampling for smoother drawing
  glEnable(GL_MULTISAMPLE);
  initializeCamera({1, 1, 1}, {0, 0, 0}, {0, 1, 0});
  initializeShader();
  createLights();
  m_container.reset(new ngl::BBox(-0.5, 0.5, -0.5, 0.5, -0.5, 0.5));
  m_testFlock.reset(new Flock(m_cam, "BoidShader", m_mouseGlobalTX));
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
    m_cam.setShape(45.0f, 720.0f / 576.0f, 0.05f, 350.0f);
    m_cam.set(_from, _to, _up);
}

void NGLScene::loadMatrixToShader()
{
    ngl::ShaderLib *shader=ngl::ShaderLib::instance();
    (*shader)["BoidShader"]->use();
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M= m_mouseGlobalTX * _targetTransform.getMatrix();
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
   //TARGET
   _targetTransform.setScale(0.03f, 0.03f, 0.03f);
   loadMatrixToShader();
   ngl::VAOPrimitives::instance()->draw("football");

  //TEST FLOCK
  m_testFlock->drawFlock(_targetTransform.getPosition(), m_container);

  _targetTransform.reset();
  loadMatrixToShader();
  m_container->draw();
  update();
}


/*void NGLScene::timerEvent(QTimerEvent *_event )
{
  if(_event->timerId() == m_sphereUpdateTimer)
  {
    if (m_animate !=true)
    {
      return;
    }
  }
  updateScene();
  update();
}*/

//----------------------------------------------------------------------------------------------------------------------

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  // this method is called every time the main window recives a key event.
  // we then switch on the key value and set the camera in the GLWindow
  switch (_event->key())
  {
  // escape key to quite
  case Qt::Key_Escape : QGuiApplication::exit(EXIT_SUCCESS); break;
  case Qt::Key_Space :
      m_win.spinXFace=0;
      m_win.spinYFace=0;
      m_modelPos.set(ngl::Vec3::zero());
  break;
  //Test Target controls
  case Qt::Key_Up : _targetTransform.addPosition(0.0f, 0.0f, -0.01f); break;
  case Qt::Key_Down : _targetTransform.addPosition(0.0f, 0.0f, 0.01f); break;
  case Qt::Key_Right : _targetTransform.addPosition(0.01f, 0.0f, 0.0f); break;
  case Qt::Key_Left : _targetTransform.addPosition(-0.01f, 0.0f, 0.0f); break;
  //Test Flock controls
  case Qt::Key_Plus : m_testFlock->addBoid(1, m_container); break;
  case Qt::Key_Minus : m_testFlock->removeBoid(1); break;
  default : break;
  }
  // finally update the GLWindow and re-draw

    update();
}
