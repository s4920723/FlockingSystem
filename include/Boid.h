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
    /// @brief returns the current velocity of the boid
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
    void wander(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius, ngl::Vec3 _randomPos);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Aligns the velocity of the current boid with those
    /// of neighbouring boids
    /// @param _boidArray an array containing all the boids in
    /// the flock
    /// @param _awareRadius the radius around the boid within which it
    /// becomes aware of other boids
    //----------------------------------------------------------------------------------------------------------------------
    void alignment(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Redirects the velocity of the current boid in order to
    /// avoid neighbouring boids
    /// @param _boidArray an array containing all the boids in
    /// the flock
    /// @param _awareRadius the radius around the boid within which it
    /// becomes aware of other boids
    //----------------------------------------------------------------------------------------------------------------------
    void separation(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Redirects the velocity of the current boid in order to
    /// get closer to neighbouring boids
    /// @param _boidArray an array containing all the boids in
    /// the flock
    /// @param _awareRadius the radius around the boid within which it
    /// becomes aware of other boids
    //----------------------------------------------------------------------------------------------------------------------
    void cohesion(std::vector<std::unique_ptr<Boid>>& _boidArray, float _awareRadius);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets how much influence each behaviour has over the boid
    /// @param _seekWeight A multiplier for the seeking behaviour vector
    /// @param _wanderWeight A multiplier for the wandering behaviour vector
    /// @param _alignmentWeight A multiplier for the alignment behaviour vector
    /// @param _separationWeight A multiplier for the separation behaviour vector
    /// @param _alignmentWeight A multiplier for the cohesion behaviour vector
    //----------------------------------------------------------------------------------------------------------------------
    void weighBehaviours(float _seekWeight, float _wanderWeight, float _alignmentWeight, float _separationWeight, float _cohesionWeight);
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
    float m_maxSpeed = 0.005f;
    /// @brief Modifier that regulates the amount of force
    /// a behvaiour is exhibiting on the boid
    float m_maxForce = 0.0001f;
    /// @brief The current transformation of the boid
    ngl::Transformation m_currentTransform;
    /// @brief Timer for the change in the wandering behaviour
    int m_wanderCounter;
    /// @brief A VAO used to visualize the velocity vector
    std::unique_ptr<ngl::SimpleVAO> m_velocityLineVAO;
    /// @brief the final calculated vector for the seeking behaviour
    ngl::Vec3 m_seekForce;
    /// @brief the final calculated vector for the wandering behaviour
    ngl::Vec3 m_wanderForce;
    /// @brief the final calculated vector for the containment behaviour
    ngl::Vec3 m_containmentForce;
    /// @brief the final calculated vector for the alignment behaviour
    ngl::Vec3 m_alignmentForce;
    /// @brief the final calculated vector for the separation behaviour
    ngl::Vec3 m_separationForce;
    /// @brief the final calculated vector for the cohesion behaviour
    ngl::Vec3 m_cohesionForce;
};

#endif
