#include "Flock.h"

#include <iostream>
#include <ngl/Random.h>


Flock::Flock(ngl::Camera _cam, std::string _shaderName, ngl::Mat4 _mouseTX)
{
    std::cout << "Flock has been created\n";
    m_cam = _cam;
    m_shaderName = _shaderName;
    m_mouseTX = _mouseTX;
    m_idCounter = 0;
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
        randPos.zero();
        ngl::Vec3 randVel;
        randPos.zero();
        /*while (randPos.m_x > _container->maxX() &&  randPos.m_x < _container->minX() &&
               randPos.m_y > _container->maxY() &&  randPos.m_y < _container->minY() &&
               randPos.m_z > _container->maxZ() &&  randPos.m_z < _container->minZ())
        {

            randPos = ngl::Random::instance()->getRandomVec3();
        }*/
        randPos = ngl::Random::instance()->getRandomVec3();
        randVel = ngl::Random::instance()->getRandomVec3();
        m_idCounter++;
        m_boidArray.push_back(std::unique_ptr<Boid>(new Boid(m_idCounter, randPos, randVel)));
        std::cout << "CREATING BOID #" << m_idCounter << "\n";
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
            std::cout << "DELETING BOID #" << m_idCounter << "\n";
            m_idCounter--;

            m_boidArray.pop_back();
        }
    }
}

/*void Flock::loadMatrixToShader(ngl::Transformation _boidTransform)
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
}*/

void Flock::drawFlock(ngl::Vec3 _targetPos)
{
    for (std::unique_ptr<Boid>& boid : m_boidArray)
    {
        boid->seek(_targetPos);
        //boid->wander(ngl::Random::instance()->getRandomVec3());
        //boid->cohesion(m_boidArray, 1.0f);
        boid->move();
        boid->loadMatrixToShader(m_shaderName, m_cam, m_mouseTX);
        boid->drawBoid();
    }
}
