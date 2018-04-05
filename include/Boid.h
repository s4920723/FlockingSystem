#ifndef BOID_H
#define BOID_H

#include <ngl/Vec3.h>
#include <ngl/Camera.h>
#include <ngl/Mat4.h>

class Boid{
  public:
    Boid();
    ~Boid();
    ngl::Vec3 getPos();
    ngl::Vec3 getVel();
    void move();
    void seek(ngl::Vec3 _targetPos);
    void drawBoid(ngl::Camera _cam, ngl::Mat4 _mouseGlobalTX);
    void loadMatrixToShader(ngl::Camera _cam, ngl::Mat4 _mouseGlobalTX);

  private:
    int m_id;
    ngl::Vec3 m_position;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_acceleration;
    float m_maxSpeed;
    float m_maxForce;
};

#endif
