#include "Boid.h"

#include <ngl/VAOPrimitives.h>

#include <iostream>
#include <math.h>
#include <ngl/Random.h>



Boid::Boid(int _id, ngl::Vec3 _initPos, ngl::Vec3 _initVel)
{
    m_position.set(_initPos);
    m_velocity.set(_initVel);
    m_id = _id;
    m_currentTransform.setScale(0.75, 0.75, 0.75);
    m_wanderCounter = 0;
    m_maxSpeed = 0.15f;
    m_maxForce = 0.015f;
    std::cout << "CREATING BOID #" << m_id << "\n";
    std::cout << "New boid position: " << m_position.m_x << ", "
              << m_position.m_y << ", " << m_position.m_z << "\n";
    std::cout << "New boid velocity: " << m_velocity.m_x << ", "
              << m_velocity.m_y << ", " << m_velocity.m_z << "\n";
}

Boid::~Boid()
{
    std::cout << "DELETING BOID #" << m_id << "\n";
}

ngl::Vec3 Boid::getPos()
{
  return m_position;
}

ngl::Vec3 Boid::getVel()
{
  return m_velocity;
}

void Boid::setMaxSpeed(float _maxSpeed)
{
    m_maxSpeed = _maxSpeed;
}

void Boid::setMaxForce(float _maxForce)
{
    m_maxForce = _maxForce;
}

void Boid::setAwareness(float _awarenessRadius)
{
    m_awarenessRadius = _awarenessRadius;
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

void Boid::drawBoid(std::unique_ptr<ngl::Obj> &_geo)
{
    _geo->draw();
}

void Boid::move(ngl::Vec3 _force, std::unique_ptr<ngl::BBox> &_container)
{
  m_acceleration = _force;
  m_velocity += m_acceleration;
  containment(_container);
  m_velocity.clamp(m_maxSpeed);
  m_position += m_velocity;
  m_acceleration *= 0;
  m_currentTransform.setPosition(m_position);
  //Rotation update
  float yaw = -atan(m_velocity.m_y/sqrt(m_velocity.m_x * m_velocity.m_x + m_velocity.m_z * m_velocity.m_z)) * 57.295779524;
  float pitch = atan2(m_velocity.m_x, m_velocity.m_z) * 57.295779524;
  m_currentTransform.setRotation(yaw, pitch, 0);
}


ngl::Vec3 Boid::steer(ngl::Vec3 _target)
{
  ngl::Vec3 steer;
  ngl::Vec3 desired = _target - this->getPos();
  float d = desired.length();
  if (d > 0)
  {
    desired.normalize();
    if (d < 0.5f)
    {
      desired *= m_maxSpeed*(d/5.0f);
    }
    else
    {
      desired *= m_maxSpeed;
    }
    steer = desired - m_velocity;
    steer.clamp(m_maxForce);
  }
  else
  {
    steer.zero();
  }
  return steer;
}

ngl::Vec3 Boid::seek(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    desired.normalize();
    //arrive(_targetPos);
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(-m_maxForce, m_maxForce);

    return steer;


}

void Boid::arrive(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    if (desired.length() < 0.1f)
    {
      m_maxSpeed = 1/desired.length();
    }
}

void Boid::containment(std::unique_ptr<ngl::BBox> &_container)
{

  float ext[6];
  ext[0]=(_container->height());
  ext[1]=0.0;
  ext[2]=ext[3]=(_container->width()/2.0f);
  ext[4]=ext[5]=(_container->depth()/2.0f);
  float D;
  for(int i=0; i<6; ++i)
  {
    D=_container->getNormalArray()[i].dot(m_position+m_velocity+m_acceleration);
    D += 2.0f; //ojbectRadius

    if (D>=ext[i])
    {
      float x = 2*(m_velocity.dot((_container->getNormalArray()[i])));
      ngl::Vec3 d = _container->getNormalArray()[i]*x;
      m_velocity -= d;

    }
  }
}

ngl::Vec3 Boid::wander(std::vector<std::unique_ptr<Boid>>& _boidArray)
{
    m_wanderCounter++;
    if (m_wanderCounter >= 150)
    {
       m_wanderCounter = 0;
       ngl::Vec3 randPos = ngl::Random::instance()->getRandomPoint(300.0, 300.0, 300.0);
       return seek(randPos);
    }

    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 distanceVec = otherBoid->getPos() - this->getPos();
        float distance = distanceVec.length();
        if (this->m_id != otherBoid->m_id && distance < m_awarenessRadius)
        {
           return ngl::Vec3(0.0,0.0,0.0);
        }
    }
}

ngl::Vec3 Boid::alignment(std::vector<std::unique_ptr<Boid>>& _boidArray)
{
    ngl::Vec3 velocitySum;
    int neighbourCount = 0;
    velocitySum.zero();
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 distanceVec = otherBoid->getPos() - this->getPos();
        float distance = distanceVec.length();
        if (this->m_id != otherBoid->m_id && distance < m_awarenessRadius)
        {
            velocitySum += otherBoid->getVel();
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        velocitySum /= static_cast<float>(neighbourCount);
        velocitySum.normalize();
        velocitySum *= m_maxSpeed;
        ngl::Vec3 steer = velocitySum - m_velocity;
        steer.clamp(-m_maxForce, m_maxForce);
        return steer;
    }
    else
    {
      return ngl::Vec3(0.0,0.0,0.0);
    }
}

ngl::Vec3 Boid::separation(std::vector<std::unique_ptr<Boid>>& _boidArray)
{
    float desiredSeparation = m_awarenessRadius/2;
    ngl::Vec3 differenceSum;
    int neighbourCount = 0;
    differenceSum.zero();
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 difference =this->getPos() - otherBoid->getPos();
        float distance = difference.length();
        if (this->m_id != otherBoid->m_id && distance < desiredSeparation)
        {
            difference.normalize();
            difference/=distance;
            differenceSum += difference;
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        differenceSum /= (float)neighbourCount;
        differenceSum.normalize();
        differenceSum *= m_maxSpeed;
        ngl::Vec3 steer = differenceSum - m_velocity;
        steer.clamp(-m_maxForce, m_maxForce);
        return steer;
    }
    else
    {
      return ngl::Vec3(0.0,0.0,0.0);
    }
}


ngl::Vec3 Boid::cohesion(std::vector<std::unique_ptr<Boid>>& _boidArray)
{
    ngl::Vec3 positionSum;
    positionSum.zero();
    int neighbourCount = 0;
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 difference = m_position - otherBoid->getPos();
        float distance = difference.length();
        if (this->m_id != otherBoid->m_id && distance < m_awarenessRadius)
        {
            positionSum += otherBoid->getPos();
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        positionSum /= static_cast<float>(neighbourCount);
        return seek(positionSum);
    }
    else
    {
      return ngl::Vec3(0.0,0.0,0.0);
    }
}
