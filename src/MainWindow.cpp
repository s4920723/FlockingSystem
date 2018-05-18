#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_gl=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_gl, 0, 0, 4, 1);
  //Adding/Removing Boids
  connect(m_ui->addBoidsAmount,SIGNAL(valueChanged(int)),m_gl,SLOT(setAddBoids(int)));
  connect(m_ui->removeBoidsAmount,SIGNAL(valueChanged(int)),m_gl,SLOT(setRemoveBoids(int)));
  connect(m_ui->addBoidsButton, SIGNAL(clicked()),m_gl,SLOT(addBoids()));
  connect(m_ui->removeBoidsButton, SIGNAL(clicked()),m_gl,SLOT(removeBoids()));
  connect(m_gl, SIGNAL(numBoidsChanged(int)), this, SLOT(updateNumBoids(int)));

  //Behaviour Controls
  connect(m_ui->cohesionSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setCohesion(int)));
  connect(m_ui->separationSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setSeparation(int)));
  connect(m_ui->alignmentSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setAlignment(int)));
  connect(m_ui->seekSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setSeekWeight(int)));
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_ui->seekSlider, SLOT(setEnabled(bool)));
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_gl, SLOT(activateTarget(bool)));

  //Attribute Controls
  connect(m_ui->maxSpeedSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setMaxSpeed(int)));
  connect(m_ui->maxForceSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setMaxForce(int)));
  connect(m_ui->awareRadiusSlider, SIGNAL(sliderMoved(int)), m_gl, SLOT(setAwareness(int)));

  //Goal Position
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_ui->goalPosX, SLOT(setEnabled(bool)));
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_ui->goalPosY, SLOT(setEnabled(bool)));
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_ui->goalPosZ, SLOT(setEnabled(bool)));
  connect(m_ui->goalPosX, SIGNAL(valueChanged(double)), m_gl, SLOT(setGoalPosX(double)));
  connect(m_ui->goalPosY, SIGNAL(valueChanged(double)), m_gl, SLOT(setGoalPosY(double)));
  connect(m_ui->goalPosZ, SIGNAL(valueChanged(double)), m_gl, SLOT(setGoalPosZ(double)));
}

//----------------------------------------------------------------------------------------------------------------------

MainWindow::~MainWindow()
{
    delete m_ui;
}

//----------------------------------------------------------------------------------------------------------------------

void MainWindow::updateNumBoids(int _b)
{

  m_ui->totalAmount->setText(QString::number(_b));
}
