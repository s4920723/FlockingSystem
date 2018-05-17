#include "Boid.h"

#include <ngl/VAOPrimitives.h>

#include <iostream>
#include <math.h>



Boid::Boid(int _id, ngl::Vec3 _initPos, ngl::Vec3 _initVel)
{
    std::cout << "Boid has been created\n";
    m_position.set(_initPos);
    m_velocity.set(_initVel);
    m_id = _id;
    m_currentTransform.setScale(3.0f, 3.0f, 3.0f);
    m_wanderCounter = 0;
    m_maxSpeed = 0.01f;
    m_maxForce = 0.001f;

    //m_alignmentForce.zero();
    //m_cohesionForce.zero();
    //m_containmentForce.zero();
    //m_seekForce.zero();
    //m_separationForce.zero();
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
  m_velocity += m_acceleration;
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

void Boid::seek(ngl::Vec3 _targetPos)
{
    ngl::Vec3 desired = _targetPos - m_position;
    desired.normalize();
    //arrive(_targetPos);
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(-m_maxForce, m_maxForce);

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

    desired -= m_position;
    desired.normalize();
    desired *= m_maxSpeed;
    ngl::Vec3 steer = desired - m_velocity;
    steer.clamp(-m_maxForce, m_maxForce);
    m_containmentForce = desired;
}

void Boid::wander(std::vector<std::unique_ptr<Boid>>& _boidArray, ngl::Vec3 _randomPos)
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
        if (this->m_id != otherBoid->m_id && distance < m_awarenessRadius)
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

void Boid::alignment(std::vector<std::unique_ptr<Boid>>& _boidArray)
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
        steer.clamp(-m_maxForce, m_maxForce);
        m_alignmentForce = steer;
    }
}

void Boid::separation(std::vector<std::unique_ptr<Boid>>& _boidArray)
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
        m_separationForce = steer;
    }
}


void Boid::cohesion(std::vector<std::unique_ptr<Boid>>& _boidArray)
{
    ngl::Vec3 positionSum;
    positionSum.zero();
    int neighbourCount = 0;
    for (std::unique_ptr<Boid>& otherBoid : _boidArray)
    {
        ngl::Vec3 difference = this->getPos() - otherBoid->getPos();
        float distance = difference.length();
        if (this->m_id != otherBoid->m_id && distance < m_awarenessRadius)
        {
            positionSum += otherBoid->getPos();
            neighbourCount++;
        }
    }
    if (neighbourCount > 0)
    {
        positionSum /= (float)neighbourCount;
        std::cout << "Cohesion Position Sum" << positionSum.m_x << ", "<< positionSum.m_y << ", " << positionSum.m_z << "\n";
        positionSum.normalize();
        positionSum *= m_maxSpeed;
        ngl::Vec3 steer = positionSum - m_velocity;
        steer.clamp(-m_maxForce, m_maxForce);
        m_cohesionForce = steer;
    }
}

void Boid::weighBehaviours(bool _activeTarget, float _seekWeight, float _alignmentWeight, float _separationWeight, float _cohesionWeight)
{
    if (_activeTarget)
    {
        m_seekForce *= _seekWeight *0;
        m_acceleration += m_seekForce;
        //std::cout << "Seeking force: " << m_seekForce.m_x << ", " << m_seekForce.m_y << ", " << m_seekForce.m_z << "\n";
    }
    else
    {
        m_wanderForce *= _seekWeight *0;
        m_acceleration += m_wanderForce;
        //std::cout << "Wandering force: " << m_wanderForce.m_x << ", " << m_wanderForce.m_y << ", " << m_wanderForce.m_z << "\n";
    }

    m_alignmentForce *= _alignmentWeight *0;
    m_acceleration += m_alignmentForce;
    //std::cout << "Alignment force: " << m_alignmentForce.m_x << ", " << m_alignmentForce.m_y << ", " << m_alignmentForce.m_z << "\n";

    m_separationForce *= _separationWeight *0;
    m_acceleration += m_separationForce;
    //std::cout << "Seeking force: " << m_separationForce.m_x << ", " << m_separationForce.m_y << ", " << m_separationForce.m_z <<  "\n";

    m_cohesionForce *= _cohesionWeight;
    m_acceleration += m_cohesionForce;
    //std::cout << "Cohesion force: " << m_cohesionForce.m_x << ", " << m_cohesionForce.m_y << ", " << m_cohesionForce.m_z << "\n";
}
