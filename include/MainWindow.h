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
    void updateNumBoids(int _b);

private:
    Ui::MainWindow *m_ui;
    /// @brief our openGL widget
    NGLScene *m_gl;
};

#endif MAINWINDOW_H
