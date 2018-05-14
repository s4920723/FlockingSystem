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
    void resizeGL(int _w , int _h);
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the initialize class is called once when the window is created and we have a valid GL context
    /// use this to setup any default GL stuff
    //----------------------------------------------------------------------------------------------------------------------
    void initializeGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is called everytime we want to draw the scene
    //----------------------------------------------------------------------------------------------------------------------
    void paintGL() override;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Queries the size of the flock and returns a QString with the number of boids
    //----------------------------------------------------------------------------------------------------------------------
    QString getFlockSize();

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


private:
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief Qt Event called when a key is pressed
    /// @param [in] _event the Qt event to query for size etc
    //----------------------------------------------------------------------------------------------------------------------
    void keyPressEvent(QKeyEvent *_event) override;
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

    //void timerEvent( QTimerEvent *_event) override;

    void updateScene();

    void initializeShader();
    void initializeCamera(ngl::Vec3 _from, ngl::Vec3 _to, ngl::Vec3 _up);
    void createLights();
    void loadMatrixToShader();
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

    ngl::Transformation _targetTransform;

    std::unique_ptr<ngl::BBox> m_container;

    int m_numOfAddBoids;
    int m_numOfRemoveBoids;
    float m_alignmentWeight;
    float m_separationWeight;
    float m_cohesionWeight;

};



#endif
