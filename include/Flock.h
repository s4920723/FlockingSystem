#ifndef _FLOCK_H_
#define _FLOCK_H_

#include "Boid.h"

#include <vector>
#include <string>
#include <ngl/Vec3.h>
#include <ngl/Mat3.h>
#include <ngl/Mat4.h>
#include <ngl/Camera.h>
#include <ngl/ShaderLib.h>
#include <ngl/BBox.h>


class Flock{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor for the flock class
    /// @param _cam sets the camera that will be used for the MVP calculations
    /// @param _shaderName sets the name of the shader program that will be used
    /// to shade the boids
    /// @param _mouseTX sets the mouse trackball transformations
    //----------------------------------------------------------------------------------------------------------------------
    Flock(ngl::Camera _cam, std::string _shaderName, ngl::Mat4 _mouseTX, ngl::BBox _container);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief destructor for the flock class
    //----------------------------------------------------------------------------------------------------------------------
    ~Flock();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief creates and adds a single boid to the flock
    /// @param _numBoids the amount of boids that will be created
    //----------------------------------------------------------------------------------------------------------------------
    void addBoid(int _numBoids);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief removes the last boid that was added to the flock
    /// @param _numBoids the amout of boids that will be removed
    //----------------------------------------------------------------------------------------------------------------------
    void removeBoid(int _numBoids);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Creates uniforms for the MVP and the normals that will
    /// be passed to the shader
    /// @param _boidTransform the updated transformations of a boid
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatrixToShader(ngl::Transformation _boidTransform);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draws the flock
    /// @param _boidTransform the updat
    //----------------------------------------------------------------------------------------------------------------------
    void drawFlock(ngl::Vec3 _targetPos);

  private:
    /// @brief an array of all the boids in the flock
    std::vector<std::unique_ptr<Boid>> m_boidArray;
    /// @brief the camera used for setting up the MVP uniform
    ngl::Camera m_cam;
    /// @brief the mouse control transformation used for MVP uniforms
    ngl::Mat4 m_mouseTX;
    /// @brief the string label of the shader program used for shading the boids
    std::string m_shaderName;
    /// @brief a counter used to assign id numbers to boids
    int m_idCounter;
    /// @brief the bounding box for the flock
    ngl::BBox m_container;

};
#endif
