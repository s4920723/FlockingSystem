#include "Flock.h"

#include <iostream>
#include <ngl/Random.h>


Flock::Flock(ngl::Camera _cam, std::string _shaderName, ngl::Mat4 _mouseTX)
{
    std::cout << "Flock has been created\n";
    m_cam = _cam;
    m_shaderName = _shaderName;
    m_mouseTX = _mouseTX;
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
        randPos = ngl::Random::instance()->getRandomPoint(_container->maxX(), _container->maxY(), _container->maxZ());
        randVel = ngl::Random::instance()->getRandomVec3();
        m_boidArray.push_back(std::unique_ptr<Boid>(new Boid(m_boidArray.size(), randPos, randVel)));
        std::cout << "CREATING BOID #" << m_boidArray.size() << "\n";
        std::cout << "New boid position: " << randPos.m_x << ", "
                  << randPos.m_y << ", " << randPos.m_z << "\n";
        std::cout << "New boid velocity: " << randVel.m_x << ", "
                  << randVel.m_y << ", " << randVel.m_z << "\n";
    }
}

void Flock::removeBoid(int _numBoids)
{
    for (int i=0; i < _numBoids; i++)
    {
        if (m_boidArray.size())
        {
            std::cout << "DELETING BOID #" << m_boidArray.size() << "\n";
            m_boidArray.pop_back();
        }
    }
}

int Flock::getFlockSize()
{
    return m_boidArray.size();
}


void Flock::drawFlock(std::map<std::string, float> _attributes, std::map<std::string, float> _weights,
                      ngl::Vec3 _targetPos, std::unique_ptr<ngl::BBox> &_container)
{
    for (std::unique_ptr<Boid>& boid : m_boidArray)
    {
        //Apply attributes to the boid
        boid->setMaxSpeed(_attributes.at("maxSpeed"));
        boid->setMaxForce(_attributes.at("maxForce"));
        boid->setAwareness(_attributes.at("awarenessRadius"));

        //Calculate boids behaviours
        boid->seek(_targetPos);
        boid->wander(m_boidArray, ngl::Random::instance()->getRandomVec3());
        boid->alignment(m_boidArray);
        boid->cohesion(m_boidArray);
        boid->separation(m_boidArray);
        //boid->containment(_container);
        boid->weighBehaviours(_weights.at("seekWeight"),
                              _weights.at("alignmentWeight"),
                              _weights.at("separationWeight"),
                              _weights.at("cohesionWeight"));

        //Update and draw boid
        boid->move();
        boid->loadMatrixToShader(m_shaderName, m_cam, m_mouseTX);
        boid->drawBoid();
    }
}
