#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "NGLScene.h"

#include <QtWidgets/QMainWindow>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief removes the last boid that was added to the flock
    /// @param _numBoids the amout of boids that will be removed
    //----------------------------------------------------------------------------------------------------------------------
    void updateNumBoids(int _b);

private:
    /// @brief the ui
    Ui::MainWindow *m_ui;
    /// @brief our openGL widget
    NGLScene *m_gl;
};

#endif MAINWINDOW_H
