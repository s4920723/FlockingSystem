#ifndef NGLSCENE_H_
#define NGLSCENE_H_

#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <ngl/Camera.h>
#include <ngl/Transformation.h>
#include <ngl/Light.h>
#include <ngl/BBox.h>
#include "Boid.h"
#include "Flock.h"

#include <QString>
#include <QEvent>
#include <QResizeEvent>
#include <QOpenGLWidget>
#include "WindowParams.h"
//----------------------------------------------------------------------------------------------------------------------
/// @file NGLScene.h
/// @brief this class inherits from the Qt OpenGLWindow and allows us to use NGL to draw OpenGL
/// @author Jonathan Macey
/// @version 1.0
/// @date 10/9/13
/// Revision History :
/// This is an initial version used for the new NGL6 / Qt 5 demos
/// @class NGLScene
/// @brief our main glwindow widget for NGL applications all drawing elements are
/// put in this file
//----------------------------------------------------------------------------------------------------------------------

class NGLScene : public QOpenGLWidget
{
  Q_OBJECT
  public:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief ctor for our NGL drawing class
    /// @param [in] parent the parent window to the class
    //----------------------------------------------------------------------------------------------------------------------
    NGLScene(QWidget *_parent);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor must close down ngl and release OpenGL resources
    //----------------------------------------------------------------------------------------------------------------------
    ~NGLScene();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called whenever the window is re-sized
    /// @param[in] _w the width of the resized window
    /// @param[in] _h the height of the resized window
    //----------------------------------------------------------------------------------------------------------------------
    void resizeGL(int _w , int _h) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;

public slots:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the number of boids that will be created if the addBoids method is called
    /// @param [in] _numOfBoids the amount of boids that will be created
    //----------------------------------------------------------------------------------------------------------------------
    void setAddBoids(int _numOfBoids);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the number of boids that will be deleted if the removeBoids method is called
    /// @param [in] _numOfBoids the amount of boids that will be removed
    //----------------------------------------------------------------------------------------------------------------------
    void setRemoveBoids(int _numOfBoids);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Adds the amount of boids set by setAddBoids
    //----------------------------------------------------------------------------------------------------------------------
    void addBoids();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Removes the amount of boids set by setRemoveBoids
    //----------------------------------------------------------------------------------------------------------------------
    void removeBoids();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets how much influence the cohesion behaviour has on the boid's movement
    /// @param _weight a value assigned to the cohesion behaviour's weight
    //----------------------------------------------------------------------------------------------------------------------
    void setCohesion(int _weight);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets how much influence the separation behaviour has on the boid's movement
    /// @param _weight a value assigned to the separation behaviour's weight
    //----------------------------------------------------------------------------------------------------------------------
    void setSeparation(int _weight);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets how much influence the alignment behaviour has on the boid's movement
    /// @param _weight a value assigned to the alignment behaviour's weight
    //----------------------------------------------------------------------------------------------------------------------
    void setAlignment(int _weight);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets how much influence the seeking behaviour has on the boid's movement
    /// @param _weight a value assigned to the seeking behaviour's weight
    //----------------------------------------------------------------------------------------------------------------------
    void setSeekWeight(int _weight);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the maximum movement speed for all the boids in a flock
    /// @param _maxSpeed the value that will be used as the boids' maximum speed
    //----------------------------------------------------------------------------------------------------------------------
    void setMaxSpeed(int _maxSpeed);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the maximum turning speed for all the boids in a flock
    /// @param _maxForce the value that will be used as the boids' maximum turning speed
    //----------------------------------------------------------------------------------------------------------------------
    void setMaxForce(int _maxForce);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the radius around each boids within which it become aware other boids
    /// @param _maxForce the value that will be used as the boids' area of awareness
    //----------------------------------------------------------------------------------------------------------------------
    void setAwareness(int _awarenessRadius);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Creates a target that the boids will seek
    /// @param _active a boolean flag which determines whether the target geometry will
    /// be drawn and wheather the boids' seeking behaviour is active
    //----------------------------------------------------------------------------------------------------------------------
    void activateTarget(bool _active);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the X position of goal object that the boids will seek out
    /// @param _posX the value that will be assigned to the goal's X position
    //----------------------------------------------------------------------------------------------------------------------
    void setGoalPosX(double _posX);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the Y position of goal object that the boids will seek out
    /// @param _posX the value that will be assigned to the goal's Y position
    //----------------------------------------------------------------------------------------------------------------------
    void setGoalPosY(double _posY);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Sets the Z position of goal object that the boids will seek out
    /// @param _posZ the value that will be assigned to the goal's Z position
    //----------------------------------------------------------------------------------------------------------------------
    void setGoalPosZ(double _posZ);

private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called every time a mouse is moved
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseMoveEvent (QMouseEvent * _event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is pressed
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mousePressEvent ( QMouseEvent *_event) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse button is released
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void mouseReleaseEvent ( QMouseEvent *_event ) override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this method is called everytime the mouse wheel is moved
    /// inherited from QObject and overridden here.
    /// @param _event the Qt Event structure
    //----------------------------------------------------------------------------------------------------------------------
    void wheelEvent( QWheelEvent *_event) override;

    void timerEvent( QTimerEvent *_event) override;

    void updateScene();

    void initializeShader();
    void initializeCamera(ngl::Vec3 _from, ngl::Vec3 _to, ngl::Vec3 _up);
    void createLights();
    void loadMatrixToShader(ngl::Mat4 _modelTransform);
    /// @brief windows parameters for mouse control etc.
    WinParams m_win;
    ///Mouse transforms
    ngl::Mat4 m_mouseGlobalTX;
    /// position for our model
    ngl::Vec3 m_modelPos;
    /// camera
    ngl::Camera m_cam;
    /// Scene Light
    ngl::Light m_light01;
    ///Test Flock
    std::unique_ptr<Flock> m_testFlock;

    ngl::Transformation m_envTransform;
    ngl::Transformation m_goalTransform;

    std::unique_ptr<ngl::BBox> m_container;

    std::map<std::string, float> m_weightMap;

    std::map<std::string, float> m_attributes;
    int m_numOfAddBoids;
    int m_numOfRemoveBoids;
    bool m_targetActive;
    ngl::Vec3 m_goalPos;
    int m_updateTimer;

  signals :
    void numBoidsChanged(int);
};

#endif
