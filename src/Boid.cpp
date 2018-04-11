#include "Boid.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <initializer_list>



Boid::Boid()
{
    std::cout << "Boid has been initialized\n";
    //m_position.set(0.0f, 0.0f, 0.0f);
    m_velocity.set(0.0f, 0.001f, 0.5f);
    //m_acceleration = 0.001f;
    m_currentTransform.setScale(0.1f, 0.1f, 0.1f);
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

void Boid::loadMatrixToShader(ngl::ShaderLib *shader, ngl::Camera _cam)
{
    (*shader)["BoidShader"]->use();
    ngl::Mat4 MV;
    ngl::Mat4 MVP;
    ngl::Mat3 normalMatrix;
    ngl::Mat4 M;
    M=m_currentTransform.getMatrix();
    MV=_cam.getViewMatrix()*M;
    MVP=_cam.getProjectionMatrix() *MV;
    normalMatrix=MV;
    normalMatrix.inverse();
    shader->setUniform("MV",MV);
    shader->setUniform("MVP",MVP);
    shader->setUniform("normalMatrix",normalMatrix);
    shader->setUniform("M",M);
}

void Boid::drawBoid()
{
    //std::cout << "Boid has been drawn\n";
    ngl::VAOPrimitives::instance() -> draw("troll");
}

void Boid::move()
{
  std::cout << "Current Boid Velocity " << m_velocity.m_x << ", " << m_velocity.m_y << ", " << m_velocity.m_z <<"\n";
  m_velocity += m_acceleration;
  m_velocity.clamp(-m_maxSpeed, m_maxSpeed);
  m_position += m_velocity;
  m_acceleration *= 0;
  m_currentTransform.setPosition(m_position);
  rotate();
}

void Boid::rotate()
{
    m_currentTransform.addRotation(0.0f, 10.0f, 0.0f);
}

void Boid::update()
{

}

void Boid::seek(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    desired.normalize();
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(m_maxForce);
    m_acceleration = steer;
}
