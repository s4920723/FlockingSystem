#include "Boid.h"
#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <ngl/Transformation.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <ngl/ShaderLib.h>
#include <initializer_list>
#include <math.h>



Boid::Boid(ngl::Vec3 _initPos, ngl::Vec3 _initVel)
{
    std::cout << "Boid has been created\n";
    m_position.set(_initPos);
    m_velocity.set(_initVel);
    m_currentTransform.setScale(0.1f, 0.1f, 0.1f);
}

Boid::~Boid()
{
    std::cout << "Boid has been destroyed\n";
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
    ngl::VAOPrimitives::instance() -> draw("troll");
}

void Boid::move()
{
  ngl::Vec3 velocity_temp = m_velocity;
  m_velocity += m_acceleration;
  m_velocity.clamp(-m_maxSpeed, m_maxSpeed);
  m_position += m_velocity;
  m_acceleration *= 0;
  m_currentTransform.setPosition(m_position);
  rotate(velocity_temp, m_velocity);
}

void Boid::rotate(ngl::Vec3 _velOld, ngl::Vec3 _velNew)
{
    float rotAngle = acos((ngl::Real)(_velOld.dot(_velNew)/(_velOld.length() * _velNew.length())));
    std::cout << "Boid Rotation: " << rotAngle << "\n";

    m_currentTransform.addRotation(rotAngle, rotAngle, rotAngle);
}


void Boid::seek(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    desired.normalize();
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(m_maxForce);
    m_acceleration = steer;

    arrive(_targetPos);
}

void Boid::arrive(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    if (desired.length() < 0.25f)
    {
        std::cout << "Boid close to target";
    }
   /* else
    {
       m_maxSpeed = 5.0f;
    }*/
}
