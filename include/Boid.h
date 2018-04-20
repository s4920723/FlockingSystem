#ifndef _BOID_H_
#define _BOID_H_

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Camera.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/BBox.h>
#include <string>

class Boid{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor for the boid class
    /// @param _initPos sets the initial position for the boid
    /// @param _initVel sets the initial velocity for the boid
    //----------------------------------------------------------------------------------------------------------------------
    Boid(ngl::Vec3 _initPos, ngl::Vec3 _initVel);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief destructor for the boid class
    //----------------------------------------------------------------------------------------------------------------------
    ~Boid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns the current position of the boid
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 getPos();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns the current velocity of the boid
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 getVel();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns the current transformations of the boid
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Transformation getTransform();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief updates the position and velocity of the boid using m_acceleration
    //----------------------------------------------------------------------------------------------------------------------
    void move();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief calculates the seeking behaviour of the boid
    /// @param _targetPos is the goal position of the boid
    //----------------------------------------------------------------------------------------------------------------------
    void seek(ngl::Vec3 _targetPos);
    ///ADD THIS BEHAVIOUR INTO SEEK
    void arrive(ngl::Vec3 _tagetPos);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draws the boid geometry with the updated location
    //----------------------------------------------------------------------------------------------------------------------
    void drawBoid();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the containment behaviour that restricts the boids
    /// from exiting a bounding box
    /// @param _container a bounding box to restrict the boid
    //----------------------------------------------------------------------------------------------------------------------
    void containment(ngl::BBox _container);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the wandering behaviour of the boid which is only
    /// active if it has no neighbouring boids. Similar to seeking
    /// but has a timer which decided how often the method is called
    /// @param _randomPos the target position of the boid
    //----------------------------------------------------------------------------------------------------------------------
    void wander(ngl::Vec3 _randomPos);

  private:
    /// @brief Boid id
    int m_id;
    /// @brief Boid position
    ngl::Vec3 m_position;
    /// @brief Boid velocity
    ngl::Vec3 m_velocity;
    /// @brief Boid acceleration
    ngl::Vec3 m_acceleration;
    /// @brief The maximum velocity of a vector
    float m_maxSpeed = 0.01f;
    /// @brief Modifier that regulates the amount of force
    /// a behvaiour is exhibiting on the boid
    float m_maxForce = 0.001f;
    /// @brief The current transformation of the boid
    ngl::Transformation m_currentTransform;
    /// @brief Timer for the change in the wandering behaviour
    int m_wanderCounter;
};

#endif
