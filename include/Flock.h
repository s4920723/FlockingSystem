#ifndef FLOCK_H
#define FLOCK_H

#include <vector>
#include "Boid.h"
#include <ngl/Vec3.h>
#include <ngl/Camera.h>
#include <ngl/shaderLib.h>

class Flock{
  public:
    Flock();
    ~Flock();
    void addBoid();
    void removeBoid();
    void drawFlock(ngl::Vec3 _targetPos, ngl::ShaderLib *_shader, ngl::Camera _cam);

  private:
    std::vector<Boid*> boidArray;

};
#endif
