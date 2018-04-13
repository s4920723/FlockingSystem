#include "Flock.h"

Flock::Flock()
{
    m_flockID = _id;
    m_flockSize
}

Flock::~Flock()
{

}

Flock::initFlock()
{
    s
}

Flock::addBoid()
{

}

Flock::drawFlock()
{
    for (Boid n : m_flockList)
    {
        n.seek();
        n.move();
        n.loadMatrixToShader();
        n.drawBoid();
    }
}
