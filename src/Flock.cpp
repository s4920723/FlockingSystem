#include "Flock.h"

#include <iostream>
#include <ngl/Random.h>


Flock::Flock(ngl::Camera _cam, std::string _shaderName, ngl::Mat4 _mouseTX)
{
    std::cout << "Flock has been created\n";
    m_cam = _cam;
    m_shaderName = _shaderName;
    m_mouseTX = _mouseTX;
    m_boidGeo.reset(new ngl::Obj("data/boid.obj"));
    m_boidGeo->createVAO();
}

Flock::~Flock()
{
    std::cout << "Flock has been destroyed\n";
}

void Flock::addBoid(int _numBoids, std::unique_ptr<ngl::BBox> &_container)
{
    for (int i=0; i < _numBoids; i++)
    {
        ngl::Vec3 randPos;
        ngl::Vec3 randVel;
        randPos = ngl::Random::instance()->getRandomPoint(_container->width()/2 - 5, _container->height()- 5, _container->depth()/2 - 5);
        if (randPos.m_y < 0)
            randPos.m_y *= -1.0f;
        if (randPos.m_y == 0.0f)
            randPos.m_y += 5.0f;
        randVel = ngl::Random::instance()->getRandomPoint(_container->width()/2, _container->height()/2, _container->depth()/2);
        m_boidArray.push_back(std::unique_ptr<Boid>(new Boid(m_boidArray.size(), randPos, randVel)));

    }
}

void Flock::removeBoid(int _numBoids)
{
    for (int i=0; i < _numBoids; i++)
    {
        if (m_boidArray.size())
        {
            m_boidArray.pop_back();
        }
    }
}

int Flock::getFlockSize()
{
    return static_cast<int>(m_boidArray.size());
}

void Flock::setAttributes(std::map<std::string, float> _attributes)
{
  for (std::unique_ptr<Boid>& boid : m_boidArray)
  {
    boid->setMaxSpeed(_attributes.at("maxSpeed"));
    boid->setMaxForce(_attributes.at("maxForce"));
    boid->setAwareness(_attributes.at("awarenessRadius"));
  }
}


void Flock::drawFlock(bool _activeTarget, std::map<std::string, float> _attributes, std::map<std::string, float> _weights,
                      ngl::Vec3 _targetPos, std::unique_ptr<ngl::BBox> &_container)
{
    for (std::unique_ptr<Boid>& boid : m_boidArray)
    {
        //Apply attributes to the boid
        boid->setMaxSpeed(_attributes.at("maxSpeed"));
        boid->setMaxForce(_attributes.at("maxForce"));
        boid->setAwareness(_attributes.at("awarenessRadius"));

        //Calculate boids behaviours
        ngl::Vec3 forceSum;
        if (_activeTarget)
        {
          forceSum += boid->seek(_targetPos) * _weights.at("seekWeight");
        }
        else
        {
          forceSum += boid->wander(m_boidArray);
        }
        forceSum += boid->alignment(m_boidArray) * _weights.at("alignmentWeight") * 2.0f;
        forceSum += boid->cohesion(m_boidArray) * _weights.at("cohesionWeight") * 1.0f;
        forceSum += boid->separation(m_boidArray) * _weights.at("separationWeight") * 3.0f;

        //Update and draw boid
        boid->move(forceSum, _container);
        boid->loadMatrixToShader(m_shaderName, m_cam, m_mouseTX);
        boid->drawBoid(m_boidGeo);
    }
}
