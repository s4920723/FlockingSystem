#ifndef FLOCK_H
#define FLOCK_H

#include "Boid.h"
#include <vector>

class Flock{
  public:
    Flock(_id);
    ~Flock();
    initFlock();
    addBoid();
    drawFlock();
  private:
    int m_flockID;
    int* flockSize = ;
    std::vector <Boid> m_flockList;
};
#endif
