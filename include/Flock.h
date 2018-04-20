#ifndef _FLOCK_H_
#define _FLOCK_H_

#include <vector>
#include "Boid.h"
#include <ngl/Vec3.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>

class Flock{
  public:
    Flock();
    ~Flock();
    float generateRandomFloat(float _min, float _max);
    void addBoid();
    void removeBoid();
    void drawFlock(ngl::Vec3 _targetPos, ngl::ShaderLib *_shader, ngl::Camera _cam, ngl::Mat4 mouseTX);
    ngl::Vec3 aligment();
    ngl::Vec3 separation();
    ngl::Vec3 cohesion();

  private:
    std::vector<Boid*> boidArray;

};
#endif
