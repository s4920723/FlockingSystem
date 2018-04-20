#include "Flock.h"

#include <iostream>
#include <time.h>
#include <boost/random.hpp>


Flock::Flock()
{
    std::cout << "Flock has been created\n";
}

Flock::~Flock()
{
    std::cout << "Flock has been destroyed\n";
}

float Flock::generateRandomFloat(float _min, float _max)
{
    boost::random::mt19937 rng;
    rng.seed(time(0));
    boost::random::uniform_real_distribution<float> u(_min, _max);
    boost::variate_generator<boost::mt19937&, boost::random::uniform_real_distribution<float> > gen(rng, u);
    return gen();
}

void Flock::addBoid()
{
    ngl::Vec3 randPos;
    ngl::Vec3 randVel;

    for (int i = 0; i<3; i++)
    {
        randPos[i] = generateRandomFloat(-1.0, 1.0);
    }

    for (int j = 0; j<3; j++)
    {
        randVel[j] = generateRandomFloat(-1.0, 1.0  );
    }

    std::cout << "New boid position: " << randPos.m_x << ", " << randPos.m_y << ", " << randPos.m_z << "\n";
    std::cout << "New boid velocity: " << randVel.m_x << ", " << randVel.m_y << ", " << randVel.m_z << "\n";
    boidArray.push_back(new Boid(randPos, randVel));
}

void Flock::removeBoid()
{
    if (boidArray.size())
    {
        delete boidArray.back();
        boidArray.pop_back();
    }
}

void Flock::drawFlock(ngl::Vec3 _targetPos, ngl::ShaderLib *_shader, ngl::Camera _cam, ngl::Mat4 _mouseTX)
{
    for (Boid* m : boidArray)
    {
        //m->seek(_targetPos);
        m->wander(ngl::Vec3(generateRandomFloat(-0.1, 0.1), generateRandomFloat(-0.1, 0.1), generateRandomFloat(-0.1, 0.1)));
        m->move();
        m->loadMatrixToShader(_shader, _cam, _mouseTX);
        m->drawBoid();
    }
}

ngl::Vec3 Flock::createNeighbourhood()
{
    for (Boid* currentBoid : boidArray)
    {
        for (std::vector<Boid*>::iterator boidIterator = boidArray.begin() ; boidIterator != boidArray.end(); ++boidIterator)
        {
            if (currentBoid != boidIterator && ngl::Vec3(currentBoid - boidIterator).length() < 1.0f)
            {

            }
        }
    }
}

ngl::Vec3 Flock::separation()
{

}

ngl::Vec3 Flock::cohesion()
{

}
