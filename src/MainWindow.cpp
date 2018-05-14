#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent), m_ui(new Ui::MainWindow)
{
  m_ui->setupUi(this);

  m_glContext=new  NGLScene(this);

  m_ui->s_mainWindowGridLayout->addWidget(m_glContext,0,0,2,1);
  connect(m_ui->s_addBoidsAmount,SIGNAL(valueChanged(int)),m_glContext,SLOT(setAddBoids(int)));
  connect(m_ui->s_removeBoidsAmount,SIGNAL(valueChanged(int)),m_glContext,SLOT(setRemoveBoids(int)));
  connect(m_ui->s_addBoidsButton, SIGNAL(clicked()),m_glContext,SLOT(addBoids()));
  connect(m_ui->s_removeBoidsButton, SIGNAL(clicked()),m_glContext,SLOT(removeBoids()));
  m_ui->s_totalAmount->setText(m_glContext->getFlockSize());
  connect(m_ui->s_cohesionSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setCohesion(int)));
  connect(m_ui->s_separationSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setSeparation(int)));
  connect(m_ui->s_alignmentSlider, SIGNAL(sliderMoved(int)), m_glContext, SLOT(setAlignment(int)));
}

MainWindow::~MainWindow()
{
    delete m_ui;
}
