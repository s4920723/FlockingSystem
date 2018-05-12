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


void Flock::drawFlock(ngl::Vec3 _targetPos, std::unique_ptr<ngl::BBox> &_container)
{
    for (std::unique_ptr<Boid>& boid : m_boidArray)
    {
        //boid->seek(_targetPos);
        //boid->wander(ngl::Random::instance()->getRandomVec3());
        //boid->alignment(m_boidArray, 10.0f);
        //boid->cohesion(m_boidArray, 10.0f);
        //boid->separation(m_boidArray, 10.f);
        boid ->containment(_container);
        boid->move();
        boid->loadMatrixToShader(m_shaderName, m_cam, m_mouseTX);
        boid->drawBoid();
    }
}
