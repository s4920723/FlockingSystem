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
    ngl::VAOPrimitives::instance() ->draw("troll");
    std::vector<ngl::Vec3> velocityVerts;
    velocityVerts.push_back(m_position);
    velocityVerts.push_back(m_velocity);
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
  float yaw = -atan(m_velocity.m_y/sqrt(m_velocity.m_x * m_velocity.m_x + m_velocity.m_z * m_velocity.m_z)) * 57.295779524;
  float pitch = atan2(m_velocity.m_x, m_velocity.m_z) * 57.295779524;
  m_currentTransform.setRotation(yaw, pitch, 0);
}


void Boid::seek(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    desired.normalize();
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(m_maxForce);
    arrive(_targetPos);
    m_seekForce = steer;


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
    ngl::Vec3 desired;
    desired.set(1.0f, 1.0f, 1.0f);
    if (m_currentTransform.getPosition().m_x > _container->maxX())
    desired = _container->getNormalArray()->left();

    if (m_currentTransform.getPosition().m_x < _container->minX())
    desired = _container->getNormalArray()->right();

    if (m_currentTransform.getPosition().m_y > _container->maxY())
    desired = _container->getNormalArray()->down();

    if (m_currentTransform.getPosition().m_y < _container->minY())
    desired = _container->getNormalArray()->up();

    if (m_currentTransform.getPosition().m_z > _container->maxZ())
    desired = _container->getNormalArray()->out();

    if (m_currentTransform.getPosition().m_z < _container->minZ())
    desired = _container->getNormalArray()->in();

    /*desired -= m_position;
    desired.normalize();
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(m_maxForce);*/
    m_containmentForce += desired;
}

void Boid::wander(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius, ngl::Vec3 _randomPos)
{
    m_wanderCounter++;
    if (m_wanderCounter >= 200)
    {
        seek(_randomPos);
        m_wanderCounter = 0;
    }

    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 distanceVec = otherBoid->getPos() - this->getPos();
        float distance = distanceVec.length();
        if (this->m_id != otherBoid->m_id && distance < _awareRadius)
        {
            m_wanderForce *= 0;
            break;
        }
    }

    if (m_seekForce != ngl::Vec3(0.0f, 0.0f, 0.0f))
    {
        m_wanderForce *= 0;
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
        m_alignmentForce = steer;
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
        m_separationForce = steer;
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
        steer.clamp(-m_maxForce, m_maxForce);
        m_cohesionForce = steer;
    }
}

void Boid::weighBehaviours(float _seekWeight, float _wanderWeight, float _alignmentWeight, float _separationWeight, float _cohesionWeight)
{
    m_seekForce *= _seekWeight;
    m_acceleration += m_seekForce;

    m_wanderForce *= _wanderWeight;
    m_acceleration += m_wanderForce;

    m_alignmentForce *= _alignmentWeight;
    m_acceleration += m_alignmentForce;

    m_separationForce *= _separationWeight;
    m_acceleration += m_separationForce;

    m_cohesionForce *= _cohesionWeight;
    m_acceleration += m_cohesionForce;
}
