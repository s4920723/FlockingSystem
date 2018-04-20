#include "Flock.h"

#include <iostream>
#include <time.h>
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

void Flock::addBoid()
{
    ngl::Vec3 randPos = ngl::Random::instance()->getRandomVec3();
    ngl::Vec3 randVel = ngl::Random::instance()->getRandomVec3();

    std::cout << "New boid position: " << randPos.m_x << ", "
              << randPos.m_y << ", " << randPos.m_z << "\n";
    std::cout << "New boid velocity: " << randVel.m_x << ", "
              << randVel.m_y << ", " << randVel.m_z << "\n";
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

void Flock::loadMatrixToShader(ngl::Transformation _boidTransform)
{
  ngl::ShaderLib *shader = ngl::ShaderLib::instance();
  (*shader)[m_shaderName]->use();
  ngl::Mat4 MV;
  ngl::Mat4 MVP;
  ngl::Mat3 normalMatrix;
  ngl::Mat4 M;
  M=m_mouseTX * _boidTransform.getMatrix();
  MV=m_cam.getViewMatrix()*M;
  MVP=m_cam.getProjectionMatrix() *MV;
  normalMatrix=MV;
  normalMatrix.inverse();
  shader->setUniform("MV",MV);
  shader->setUniform("MVP",MVP);
  shader->setUniform("normalMatrix",normalMatrix);
  shader->setUniform("M",M);
}
void Flock::drawFlock(ngl::Vec3 _targetPos)
{
    for (Boid* m : boidArray)
    {
        m->seek(_targetPos);
        m->wander(ngl::Random::instance()->getRandomVec3());
        m->move();
        loadMatrixToShader(m->getTransform());
        m->drawBoid();
    }
}

ngl::Vec3 Flock::aligment()
{
    for (Boid* currentBoid : boidArray)
    {
        for (std::vector<Boid*>::iterator boidIterator = boidArray.begin() ; boidIterator != boidArray.end(); ++boidIterator)
        {
            //if (ngl::Vec3(currentBoid->getPos() - *boidIterator).length() < 1.0f)
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
