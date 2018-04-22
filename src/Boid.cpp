#include "Boid.h"

#include <iostream>
#include <ngl/VAOPrimitives.h>
#include <math.h>



Boid::Boid(int _id, ngl::Vec3 _initPos, ngl::Vec3 _initVel)
{
    std::cout << "Boid has been created\n";
    m_position.set(_initPos);
    m_velocity.set(_initVel);
    m_id = _id;
    m_currentTransform.setScale(0.1f, 0.1f, 0.1f);
    m_wanderCounter = 0;
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

ngl::Transformation Boid::getTransform()
{
  return m_currentTransform;
}

void Boid::loadMatrixToShader(std::string _shaderName, ngl::Camera _cam, ngl::Mat4 _mouseTX)
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  (*shader)[_shaderName]->use();
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M= _mouseTX * m_currentTransform.getMatrix();
  MV= _cam.getViewMatrix()*M;
  MVP= _cam.getProjectionMatrix() *MV;
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
  //Translation update
  ngl::Vec3 velocityTemp = m_velocity;
  m_velocity += m_acceleration;
  m_velocity.clamp(-m_maxSpeed, m_maxSpeed);
  m_position += m_velocity;
  m_acceleration *= 0;
  m_currentTransform.setPosition(m_position);

  //Rotation update
  /*float rotAngle = acos((velocityTemp.dot(m_velocity)/(velocityTemp.length() * m_velocity.length())));
  m_currentTransform.addRotation(0, rotAngle, 0);*/
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
      m_maxSpeed = 0.0f;
    }
}

void Boid::containment(ngl::BBox _container)
{
    if (m_currentTransform.getPosition().m_x > _container.maxX())
    m_acceleration = _container.getNormalArray()->left();

    if (m_currentTransform.getPosition().m_x < _container.minX())
    m_acceleration = _container.getNormalArray()->right();

    if (m_currentTransform.getPosition().m_y > _container.maxY())
    m_acceleration = _container.getNormalArray()->down();

    if (m_currentTransform.getPosition().m_y < _container.minY())
    m_acceleration = _container.getNormalArray()->up();
}

void Boid::wander(ngl::Vec3 _randomPos)
{
    m_wanderCounter++;
    if (m_wanderCounter >= 200)
    {
        seek(_randomPos);
        m_wanderCounter = 0;
    }
}

void Boid::alignment(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius)
{
    ngl::Vec3 velocitySum;
    int neighbourCount = 0;
    velocitySum.zero();
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 distanceVec = otherBoid->getPos() - this->getPos();
        float distance = distanceVec.length();
        if (this->m_id != otherBoid->m_id && distance < _awareRadius)
        {
            velocitySum += otherBoid->getPos();
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        velocitySum /= (float)neighbourCount;
        velocitySum.normalize();
        velocitySum *= m_maxSpeed;
        ngl::Vec3 steer = velocitySum - m_velocity;
        steer.clamp(m_maxForce);
        m_acceleration = steer;
    }
}

void Boid::separation(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius)
{
    ngl::Vec3 positionSum;
    int neighbourCount = 0;
    positionSum.zero();
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 distanceVec = otherBoid->getPos() - this->getPos();
        float distance = distanceVec.length();
        if (this->m_id != otherBoid->m_id && distance < _awareRadius)
        {
            positionSum += otherBoid->getPos();
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        positionSum /= (float)neighbourCount;
        positionSum.normalize();
        positionSum *= m_maxSpeed;
        ngl::Vec3 steer = (positionSum*(-1)) - m_velocity;
        steer.clamp(m_maxForce);
        m_acceleration = steer;
    }
}


void Boid::cohesion(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius)
{
    ngl::Vec3 positionSum;
    int neighbourCount = 0;
    positionSum.zero();
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 distanceVec = otherBoid->getPos() - this->getPos();
        float distance = distanceVec.length();
        if (this->m_id != otherBoid->m_id && distance < _awareRadius)
        {
            positionSum += otherBoid->getPos();
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        positionSum /= (float)neighbourCount;
        positionSum.normalize();
        positionSum *= m_maxSpeed;
        ngl::Vec3 steer = positionSum - m_velocity;
        steer.clamp(m_maxForce);
        m_acceleration = steer;
    }
}
