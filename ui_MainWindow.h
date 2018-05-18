/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *s_mainWindowGridLayout;
    QSpacerItem *horizontalSpacer;
    QGroupBox *addRemoveBoids;
    QGridLayout *gridLayout;
    QPushButton *removeBoidsButton;
    QPushButton *addBoidsButton;
    QLabel *totalAmount;
    QSpinBox *removeBoidsAmount;
    QLabel *totalAmountLabel;
    QSpinBox *addBoidsAmount;
    QGroupBox *behaviours;
    QGridLayout *gridLayout_2;
    QSlider *cohesionSlider;
    QLabel *separationLabel;
    QLabel *cohesionLabel;
    QLabel *alignmentLabel;
    QSlider *separationSlider;
    QLabel *label;
    QDoubleSpinBox *goalPosX;
    QDoubleSpinBox *goalPosY;
    QFrame *line;
    QCheckBox *activeGoal;
    QSlider *seekSlider;
    QDoubleSpinBox *goalPosZ;
    QLabel *seekingLabel;
    QSpacerItem *verticalSpacer;
    QSlider *alignmentSlider;
    QGroupBox *boidParams;
    QGridLayout *gridLayout_6;
    QSlider *maxSpeedSlider;
    QSlider *maxForceSlider;
    QLabel *awareRadiusLabel;
    QLabel *maxForceLabel;
    QLabel *maxspeedLabel;
    QSlider *awareRadiusSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1016, 760);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        s_mainWindowGridLayout = new QGridLayout(centralwidget);
        s_mainWindowGridLayout->setSpacing(9);
        s_mainWindowGridLayout->setObjectName(QStringLiteral("s_mainWindowGridLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        s_mainWindowGridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        addRemoveBoids = new QGroupBox(centralwidget);
        addRemoveBoids->setObjectName(QStringLiteral("addRemoveBoids"));
        gridLayout = new QGridLayout(addRemoveBoids);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        removeBoidsButton = new QPushButton(addRemoveBoids);
        removeBoidsButton->setObjectName(QStringLiteral("removeBoidsButton"));

        gridLayout->addWidget(removeBoidsButton, 1, 1, 1, 1);

        addBoidsButton = new QPushButton(addRemoveBoids);
        addBoidsButton->setObjectName(QStringLiteral("addBoidsButton"));

        gridLayout->addWidget(addBoidsButton, 0, 1, 1, 1);

        totalAmount = new QLabel(addRemoveBoids);
        totalAmount->setObjectName(QStringLiteral("totalAmount"));

        gridLayout->addWidget(totalAmount, 2, 1, 1, 1);

        removeBoidsAmount = new QSpinBox(addRemoveBoids);
        removeBoidsAmount->setObjectName(QStringLiteral("removeBoidsAmount"));
        removeBoidsAmount->setMaximum(300);

        gridLayout->addWidget(removeBoidsAmount, 1, 0, 1, 1);

        totalAmountLabel = new QLabel(addRemoveBoids);
        totalAmountLabel->setObjectName(QStringLiteral("totalAmountLabel"));

        gridLayout->addWidget(totalAmountLabel, 2, 0, 1, 1);

        addBoidsAmount = new QSpinBox(addRemoveBoids);
        addBoidsAmount->setObjectName(QStringLiteral("addBoidsAmount"));
        addBoidsAmount->setMaximum(300);

        gridLayout->addWidget(addBoidsAmount, 0, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(addRemoveBoids, 0, 1, 1, 2);

        behaviours = new QGroupBox(centralwidget);
        behaviours->setObjectName(QStringLiteral("behaviours"));
        gridLayout_2 = new QGridLayout(behaviours);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        cohesionSlider = new QSlider(behaviours);
        cohesionSlider->setObjectName(QStringLiteral("cohesionSlider"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cohesionSlider->sizePolicy().hasHeightForWidth());
        cohesionSlider->setSizePolicy(sizePolicy1);
        cohesionSlider->setMinimum(10);
        cohesionSlider->setMaximum(300);
        cohesionSlider->setSingleStep(10);
        cohesionSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(cohesionSlider, 1, 0, 1, 3);

        separationLabel = new QLabel(behaviours);
        separationLabel->setObjectName(QStringLiteral("separationLabel"));

        gridLayout_2->addWidget(separationLabel, 2, 0, 1, 2);

        cohesionLabel = new QLabel(behaviours);
        cohesionLabel->setObjectName(QStringLiteral("cohesionLabel"));

        gridLayout_2->addWidget(cohesionLabel, 0, 0, 1, 1);

        alignmentLabel = new QLabel(behaviours);
        alignmentLabel->setObjectName(QStringLiteral("alignmentLabel"));

        gridLayout_2->addWidget(alignmentLabel, 4, 0, 1, 1);

        separationSlider = new QSlider(behaviours);
        separationSlider->setObjectName(QStringLiteral("separationSlider"));
        separationSlider->setMinimum(10);
        separationSlider->setMaximum(300);
        separationSlider->setSingleStep(10);
        separationSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(separationSlider, 3, 0, 1, 3);

        label = new QLabel(behaviours);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_2->addWidget(label, 8, 0, 1, 2);

        goalPosX = new QDoubleSpinBox(behaviours);
        goalPosX->setObjectName(QStringLiteral("goalPosX"));
        goalPosX->setEnabled(false);
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(goalPosX->sizePolicy().hasHeightForWidth());
        goalPosX->setSizePolicy(sizePolicy2);
        goalPosX->setMinimum(-99);
        goalPosX->setMaximum(99);

        gridLayout_2->addWidget(goalPosX, 9, 0, 1, 1);

        goalPosY = new QDoubleSpinBox(behaviours);
        goalPosY->setObjectName(QStringLiteral("goalPosY"));
        goalPosY->setEnabled(false);
        sizePolicy2.setHeightForWidth(goalPosY->sizePolicy().hasHeightForWidth());
        goalPosY->setSizePolicy(sizePolicy2);
        goalPosY->setMinimum(-99);
        goalPosY->setMaximum(99);

        gridLayout_2->addWidget(goalPosY, 9, 1, 1, 1);

        line = new QFrame(behaviours);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line, 6, 0, 1, 3);

        activeGoal = new QCheckBox(behaviours);
        activeGoal->setObjectName(QStringLiteral("activeGoal"));

        gridLayout_2->addWidget(activeGoal, 7, 0, 1, 3);

        seekSlider = new QSlider(behaviours);
        seekSlider->setObjectName(QStringLiteral("seekSlider"));
        seekSlider->setEnabled(false);
        seekSlider->setMinimum(10);
        seekSlider->setMaximum(300);
        seekSlider->setSingleStep(10);
        seekSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(seekSlider, 11, 0, 1, 3);

        goalPosZ = new QDoubleSpinBox(behaviours);
        goalPosZ->setObjectName(QStringLiteral("goalPosZ"));
        goalPosZ->setEnabled(false);
        sizePolicy2.setHeightForWidth(goalPosZ->sizePolicy().hasHeightForWidth());
        goalPosZ->setSizePolicy(sizePolicy2);
        goalPosZ->setMinimum(-99);
        goalPosZ->setMaximum(99);

        gridLayout_2->addWidget(goalPosZ, 9, 2, 1, 1);

        seekingLabel = new QLabel(behaviours);
        seekingLabel->setObjectName(QStringLiteral("seekingLabel"));

        gridLayout_2->addWidget(seekingLabel, 10, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 12, 0, 1, 1);

        alignmentSlider = new QSlider(behaviours);
        alignmentSlider->setObjectName(QStringLiteral("alignmentSlider"));
        alignmentSlider->setMinimum(10);
        alignmentSlider->setMaximum(300);
        alignmentSlider->setSingleStep(10);
        alignmentSlider->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(alignmentSlider, 5, 0, 1, 3);


        s_mainWindowGridLayout->addWidget(behaviours, 3, 1, 1, 2);

        boidParams = new QGroupBox(centralwidget);
        boidParams->setObjectName(QStringLiteral("boidParams"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(boidParams->sizePolicy().hasHeightForWidth());
        boidParams->setSizePolicy(sizePolicy3);
        gridLayout_6 = new QGridLayout(boidParams);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        maxSpeedSlider = new QSlider(boidParams);
        maxSpeedSlider->setObjectName(QStringLiteral("maxSpeedSlider"));
        maxSpeedSlider->setMinimum(10);
        maxSpeedSlider->setMaximum(200);
        maxSpeedSlider->setSingleStep(10);
        maxSpeedSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(maxSpeedSlider, 4, 0, 1, 1);

        maxForceSlider = new QSlider(boidParams);
        maxForceSlider->setObjectName(QStringLiteral("maxForceSlider"));
        maxForceSlider->setMinimum(10);
        maxForceSlider->setMaximum(100);
        maxForceSlider->setSingleStep(10);
        maxForceSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(maxForceSlider, 6, 0, 1, 1);

        awareRadiusLabel = new QLabel(boidParams);
        awareRadiusLabel->setObjectName(QStringLiteral("awareRadiusLabel"));

        gridLayout_6->addWidget(awareRadiusLabel, 1, 0, 1, 1);

        maxForceLabel = new QLabel(boidParams);
        maxForceLabel->setObjectName(QStringLiteral("maxForceLabel"));

        gridLayout_6->addWidget(maxForceLabel, 5, 0, 1, 1);

        maxspeedLabel = new QLabel(boidParams);
        maxspeedLabel->setObjectName(QStringLiteral("maxspeedLabel"));

        gridLayout_6->addWidget(maxspeedLabel, 3, 0, 1, 1);

        awareRadiusSlider = new QSlider(boidParams);
        awareRadiusSlider->setObjectName(QStringLiteral("awareRadiusSlider"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(awareRadiusSlider->sizePolicy().hasHeightForWidth());
        awareRadiusSlider->setSizePolicy(sizePolicy4);
        awareRadiusSlider->setMinimum(0);
        awareRadiusSlider->setMaximum(1000);
        awareRadiusSlider->setSingleStep(10);
        awareRadiusSlider->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(awareRadiusSlider, 2, 0, 1, 1);


        s_mainWindowGridLayout->addWidget(boidParams, 1, 1, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1016, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Flocking System - s4920723", Q_NULLPTR));
        addRemoveBoids->setTitle(QApplication::translate("MainWindow", "Add/Remove Boids", Q_NULLPTR));
        removeBoidsButton->setText(QApplication::translate("MainWindow", "Delete Boids", Q_NULLPTR));
        addBoidsButton->setText(QApplication::translate("MainWindow", "Add Boids", Q_NULLPTR));
        totalAmount->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        totalAmountLabel->setText(QApplication::translate("MainWindow", "Total Amount of Boids:", Q_NULLPTR));
        behaviours->setTitle(QApplication::translate("MainWindow", "Behaviour Controls", Q_NULLPTR));
        separationLabel->setText(QApplication::translate("MainWindow", "Separation", Q_NULLPTR));
        cohesionLabel->setText(QApplication::translate("MainWindow", "Cohesion", Q_NULLPTR));
        alignmentLabel->setText(QApplication::translate("MainWindow", "Alignment", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Target Location", Q_NULLPTR));
        activeGoal->setText(QApplication::translate("MainWindow", "Activate Goal Seeking", Q_NULLPTR));
        seekingLabel->setText(QApplication::translate("MainWindow", "Seeking", Q_NULLPTR));
        boidParams->setTitle(QApplication::translate("MainWindow", "Boid Parameters", Q_NULLPTR));
        awareRadiusLabel->setText(QApplication::translate("MainWindow", "Awareness Radius", Q_NULLPTR));
        maxForceLabel->setText(QApplication::translate("MainWindow", "Maximum Applied Force", Q_NULLPTR));
        maxspeedLabel->setText(QApplication::translate("MainWindow", "Maximum Movement Speed", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
