#include "Boid.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <ngl/Camera.h>


Boid::Boid()
{
  ngl::Vec3 position(0.0f, 0.5f, 0.5f);
  m_position =position;
  ngl::Vec3 velocity(0.5f, 0.5f, 0.5f);
  m_velocity = velocity;
  m_maxSpeed = 2.0f;
  m_maxForce = 1.0f;
}

Boid::~Boid()
{
}

ngl::Vec3 Boid::getPos()
{
  return m_position;
}

ngl::Vec3 Boid::getVel()
{
  return m_velocity;
}

void Boid::loadMatrixToShader(ngl::Camera _cam, ngl::Mat4 _mouseGlobalTX)
{
  ngl::ShaderLib* shader = ngl::ShaderLib::instance();

  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M            = _mouseGlobalTX;
  MV           = _cam.getViewMatrix() * M;
  MVP          = _cam.getVPMatrix() * M;

  normalMatrix = MV;
  normalMatrix.inverse().transpose();
  shader->setUniform( "MV", MV );
  shader->setUniform( "MVP", MVP );
  shader->setUniform( "normalMatrix", normalMatrix );
  shader->setUniform( "M", M );
}

void Boid::drawBoid(ngl::Camera _cam, ngl::Mat4 _mouseGlobalTX)
{
  loadMatrixToShader(_cam, _mouseGlobalTX);
  std::cout << "Boid has been drawn\n";
  ngl::VAOPrimitives::instance() -> draw("cube");
}

void Boid::move()
{
  m_velocity += m_acceleration;
  m_velocity.clamp(0, m_maxSpeed);
  m_position += m_velocity;
  m_acceleration *= 0;
}

void Boid::seek(ngl::Vec3 _targetPos)
{

}
