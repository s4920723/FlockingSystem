#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_glContext=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_glContext,0,0,3,1);
  connect(m_ui->addBoidsAmount,SIGNAL(valueChanged(int)),m_glContext,SLOT(setAddBoids(int)));
  connect(m_ui->removeBoidsAmount,SIGNAL(valueChanged(int)),m_glContext,SLOT(setRemoveBoids(int)));
  connect(m_ui->addBoidsButton, SIGNAL(clicked()),m_glContext,SLOT(addBoids()));
  //connect(m_ui->addBoidsButton, SIGNAL(clicked()), m_ui->totalAmount, SLOT(setText(m_glContext->getFlockSize())));
  connect(m_ui->removeBoidsButton, SIGNAL(clicked()),m_glContext,SLOT(removeBoids()));
  connect(m_ui->cohesionSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setCohesion(int)));
  connect(m_ui->separationSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setSeparation(int)));
  connect(m_ui->alignmentSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setAlignment(int)));
  connect(m_ui->seekSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setSeekWeight(int)));
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_ui->seekSlider, SLOT(setEnabled(bool)));
  connect(m_ui->activeGoal, SIGNAL(toggled(bool)), m_glContext, SLOT(activateTarget(bool)));
  connect(m_ui->maxSpeedSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setMaxSpeed(int)));
  connect(m_ui->maxForceSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setMaxForce(int)));
  connect(m_ui->awareRadiusSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setAwareness(int)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
