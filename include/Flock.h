#ifndef _FLOCK_H_
#define _FLOCK_H_

#include "Boid.h"

#include <ngl/Vec3.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <vector>
#include <string>

class Flock{
  public:
    Flock(ngl::Camera _cam, std::string _shaderName, ngl::Mat4 _mouseTX);
    ~Flock();
    void addBoid();
    void removeBoid();
    void loadMatrixToShader(ngl::Transformation _boidTransform);
    void drawFlock(ngl::Vec3 _targetPos);
    ngl::Vec3 aligment();
    ngl::Vec3 separation();
    ngl::Vec3 cohesion();

  private:
    std::vector<Boid*> boidArray;
    ngl::Camera m_cam;
    ngl::Mat4 m_mouseTX;
    std::string m_shaderName;

};
#endif
