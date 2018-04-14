#ifndef _BOID_H_
#define _BOID_H_

#include <ngl/Vec3.h>
#include <ngl/Camera.h>
#include <ngl/Mat4.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>

class Boid{
  public:
    Boid(ngl::Vec3 _initPos, ngl::Vec3 _initVel);
    ~Boid();
    ngl::Vec3 getPos();
    ngl::Vec3 getVel();
    void move();
    void rotate(ngl::Vec3 _velOld, ngl::Vec3 _velNew);
    void seek(ngl::Vec3 _targetPos);
    void arrive(ngl::Vec3 _tagetPos);
    void drawBoid();
    void loadMatrixToShader(ngl::ShaderLib *shader, ngl::Camera _cam);

  private:
    int m_id;
    ngl::Vec3 m_position;
    ngl::Vec3 m_velocity;
    ngl::Vec3 m_acceleration;
    float m_maxSpeed = 0.01f;
    float m_maxForce = 0.001f;
    ngl::Transformation m_currentTransform;
};

#endif
