#ifndef _BOID_H_
#define _BOID_H_

#include <string>
#include <vector>
#include <memory>

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Camera.h>
#include <ngl/Transformation.h>
#include <ngl/ShaderLib.h>
#include <ngl/BBox.h>
#include <ngl/SimpleVAO.h>
#include <ngl/Obj.h>


class Boid{
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief constructor for the boid class
    /// @param _initPos sets the initial position for the boid
    /// @param _initVel sets the initial velocity for the boid
    //----------------------------------------------------------------------------------------------------------------------
    Boid(int _id, ngl::Vec3 _initPos, ngl::Vec3 _initVel);
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
    /// @brief sets the maximum movement speed of the boid
    /// @param _maxSpeed the value that will be set as the boid's
    /// maximum movement speed
    //----------------------------------------------------------------------------------------------------------------------
    void setMaxSpeed(float _maxSpeed);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief sets the maximum turning speed of the boid
    /// @param _maxForce the value that will be set as the boid's
    /// maximum turning speed
    //----------------------------------------------------------------------------------------------------------------------
    void setMaxForce(float _maxForce);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief sets the area of awareness of the boid
    /// @param _awarenessRadius the radius around the boid within which
    /// it perceives other boids
    //----------------------------------------------------------------------------------------------------------------------
    void setAwareness(float _awarenessRadius);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief returns the current velocity of the boid
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Transformation getTransform();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief updates the position and velocity of the boid using m_acceleration
    //----------------------------------------------------------------------------------------------------------------------
    void move(ngl::Vec3 _force, std::unique_ptr<ngl::BBox> &_container);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief calculates the seeking behaviour of the boid
    /// @param _targetPos is the goal position of the boid
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 seek(ngl::Vec3 _targetPos);
    ///ADD THIS BEHAVIOUR INTO SEEK
    void arrive(ngl::Vec3 _tagetPos);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief draws the boid geometry with the updated location
    //----------------------------------------------------------------------------------------------------------------------
    void drawBoid(std::unique_ptr<ngl::Obj> &_geo);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief method that sets the uniforms for the M, MV, MVP and normal matricies
    /// @param _container a bounding box to restrict the boid
    //----------------------------------------------------------------------------------------------------------------------
    void loadMatrixToShader(std::string shaderName, ngl::Camera _cam, ngl::Mat4 _mouseTX);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the containment behaviour that restricts the boids
    /// from exiting a bounding box
    /// @param _container a bounding box to restrict the boid
    //----------------------------------------------------------------------------------------------------------------------
    void containment(std::unique_ptr<ngl::BBox> &_container);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the wandering behaviour of the boid which is only
    /// active if it has no neighbouring boids. Similar to seeking
    /// but has a timer which decided how often the method is called
    /// @param _randomPos the target position of the boid
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 wander(std::vector<std::unique_ptr<Boid>>& _boidArray, ngl::Vec3 _randomPos);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Aligns the velocity of the current boid with those
    /// of neighbouring boids
    /// @param _boidArray an array containing all the boids in
    /// the flock
    /// @param _awareRadius the radius around the boid within which it
    /// becomes aware of other boids
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 alignment(std::vector<std::unique_ptr<Boid>>& _boidArray);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Redirects the velocity of the current boid in order to
    /// avoid neighbouring boids
    /// @param _boidArray an array containing all the boids in
    /// the flock
    /// @param _awareRadius the radius around the boid within which it
    /// becomes aware of other boids
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 separation(std::vector<std::unique_ptr<Boid>>& _boidArray);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Redirects the velocity of the current boid in order to
    /// get closer to neighbouring boids
    /// @param _boidArray an array containing all the boids in
    /// the flock
    /// @param _awareRadius the radius around the boid within which it
    /// becomes aware of other boids
    //----------------------------------------------------------------------------------------------------------------------
    ngl::Vec3 cohesion(std::vector<std::unique_ptr<Boid>>& _boidArray);

    ngl::Vec3 steer(ngl::Vec3 _target);
    /// @brief Boid id number
    int m_id;

  private:
    /// @brief Boid position
    ngl::Vec3 m_position;
    /// @brief Boid velocity
    ngl::Vec3 m_velocity;
    /// @brief Boid acceleration
    ngl::Vec3 m_acceleration;
    /// @brief The maximum velocity of a vector
    float m_maxSpeed;
    /// @brief Modifier that regulates the amount of force
    /// a behvaiour is exhibiting on the boid
    float m_maxForce;
    /// @brief The radius within which the boid recognizes
    /// other boids
    float m_awarenessRadius;
    /// @brief The current transformation of the boid
    ngl::Transformation m_currentTransform;
    /// @brief Timer for the change in the wandering behaviour
    int m_wanderCounter;
    /// @brief A VAO used to visualize the velocity vector
    std::unique_ptr<ngl::SimpleVAO> m_velocityLineVAO;
};

#endif
