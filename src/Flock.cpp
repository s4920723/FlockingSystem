#include "Flock.h"

#include <iostream>
#include <cstdlib>
#include <time.h>


Flock::Flock()
{
    std::cout << "Flock has been created\n";
}

Flock::~Flock()
{
    std::cout << "Flock has been destroyed\n";
}

void Flock::addBoid()
{
    srand(time(NULL));
    ngl::Vec3 _randPos;
    ngl::Vec3 _randVel;

    for (int i = 0; i<3; i++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        _randPos[i] = r;
    }

    for (int j = 0; j<3; j++)
    {
        float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        _randVel[j] = r;
    }

    std::cout << "New boid position: " << _randPos.m_x << ", " << _randPos.m_y << ", " << _randPos.m_z << "\n";
    std::cout << "New boid velocity: " << _randVel.m_x << ", " << _randVel.m_y << ", " << _randVel.m_z << "\n";
    boidArray.push_back(new Boid(_randPos, _randVel));
}

void Flock::removeBoid()
{
    delete boidArray.back();
}

void Flock::drawFlock(ngl::Vec3 _targetPos, ngl::ShaderLib *_shader, ngl::Camera _cam)
{
    for (Boid* m : boidArray)
    {
        m->seek(_targetPos);
        m->move();
        m->loadMatrixToShader(_shader, _cam);
        m->drawBoid();
    }

}
