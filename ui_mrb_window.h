/********************************************************************************
** Form generated from reading UI file 'mrb_window.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MRB_WINDOW_H
#define UI_MRB_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QComboBox *load_stream_capture_list;
    QPushButton *load_stream_btn;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QPushButton *setpoint_selector_btn;
    QPushButton *motor_b_selector_btn;
    QPushButton *motor_a_selector_btn;
    QPushButton *motor_c_selector_btn;
    QGroupBox *groupBox_3;
    QLabel *camera_stream;
    QGroupBox *groupBox_4;
    QGroupBox *groupBox_5;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpinBox *Kp_spinbox;
    QSlider *Kp_slider;
    QGroupBox *groupBox_6;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QSpinBox *Ki_spinbox;
    QSlider *Ki_slider;
    QGroupBox *groupBox_7;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QSpinBox *Kd_spinbox;
    QSlider *Kd_slider;
    QPushButton *start_pid;
    QPushButton *stop_pid;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1123, 525);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 191, 101));
        load_stream_capture_list = new QComboBox(groupBox);
        load_stream_capture_list->setObjectName(QStringLiteral("load_stream_capture_list"));
        load_stream_capture_list->setGeometry(QRect(10, 30, 171, 21));
        load_stream_btn = new QPushButton(groupBox);
        load_stream_btn->setObjectName(QStringLiteral("load_stream_btn"));
        load_stream_btn->setGeometry(QRect(100, 60, 80, 25));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(220, 10, 198, 102));
        horizontalLayout = new QHBoxLayout(groupBox_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        setpoint_selector_btn = new QPushButton(groupBox_2);
        setpoint_selector_btn->setObjectName(QStringLiteral("setpoint_selector_btn"));

        gridLayout->addWidget(setpoint_selector_btn, 1, 2, 1, 1);

        motor_b_selector_btn = new QPushButton(groupBox_2);
        motor_b_selector_btn->setObjectName(QStringLiteral("motor_b_selector_btn"));

        gridLayout->addWidget(motor_b_selector_btn, 0, 2, 1, 1);

        motor_a_selector_btn = new QPushButton(groupBox_2);
        motor_a_selector_btn->setObjectName(QStringLiteral("motor_a_selector_btn"));

        gridLayout->addWidget(motor_a_selector_btn, 0, 0, 1, 1);

        motor_c_selector_btn = new QPushButton(groupBox_2);
        motor_c_selector_btn->setObjectName(QStringLiteral("motor_c_selector_btn"));

        gridLayout->addWidget(motor_c_selector_btn, 1, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(470, 10, 631, 481));
        camera_stream = new QLabel(groupBox_3);
        camera_stream->setObjectName(QStringLiteral("camera_stream"));
        camera_stream->setGeometry(QRect(0, 20, 611, 451));
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 140, 431, 281));
        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 30, 411, 71));
        layoutWidget = new QWidget(groupBox_5);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        Kp_spinbox = new QSpinBox(layoutWidget);
        Kp_spinbox->setObjectName(QStringLiteral("Kp_spinbox"));
        Kp_spinbox->setMinimum(-5000);
        Kp_spinbox->setMaximum(5000);
        Kp_spinbox->setValue(5);

        horizontalLayout_2->addWidget(Kp_spinbox);

        Kp_slider = new QSlider(layoutWidget);
        Kp_slider->setObjectName(QStringLiteral("Kp_slider"));
        Kp_slider->setMaximum(50000);
        Kp_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(Kp_slider);

        groupBox_6 = new QGroupBox(groupBox_4);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 110, 411, 71));
        layoutWidget1 = new QWidget(groupBox_6);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        Ki_spinbox = new QSpinBox(layoutWidget1);
        Ki_spinbox->setObjectName(QStringLiteral("Ki_spinbox"));
        Ki_spinbox->setMinimum(-5000);
        Ki_spinbox->setMaximum(5000);
        Ki_spinbox->setValue(9);

        horizontalLayout_3->addWidget(Ki_spinbox);

        Ki_slider = new QSlider(layoutWidget1);
        Ki_slider->setObjectName(QStringLiteral("Ki_slider"));
        Ki_slider->setMaximum(50000);
        Ki_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(Ki_slider);

        groupBox_7 = new QGroupBox(groupBox_4);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(10, 190, 411, 71));
        layoutWidget_2 = new QWidget(groupBox_7);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        Kd_spinbox = new QSpinBox(layoutWidget_2);
        Kd_spinbox->setObjectName(QStringLiteral("Kd_spinbox"));
        Kd_spinbox->setMinimum(-5000);
        Kd_spinbox->setMaximum(5000);
        Kd_spinbox->setValue(7);

        horizontalLayout_4->addWidget(Kd_spinbox);

        Kd_slider = new QSlider(layoutWidget_2);
        Kd_slider->setObjectName(QStringLiteral("Kd_slider"));
        Kd_slider->setMaximum(50000);
        Kd_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(Kd_slider);

        start_pid = new QPushButton(centralwidget);
        start_pid->setObjectName(QStringLiteral("start_pid"));
        start_pid->setGeometry(QRect(360, 430, 80, 25));
        stop_pid = new QPushButton(centralwidget);
        stop_pid->setObjectName(QStringLiteral("stop_pid"));
        stop_pid->setGeometry(QRect(360, 460, 80, 25));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Select a camera stream:", nullptr));
        load_stream_btn->setText(QApplication::translate("MainWindow", "Load stream", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Setup different variables:", nullptr));
        setpoint_selector_btn->setText(QApplication::translate("MainWindow", "Setpoint", nullptr));
        motor_b_selector_btn->setText(QApplication::translate("MainWindow", "Motor B", nullptr));
        motor_a_selector_btn->setText(QApplication::translate("MainWindow", "Motor A", nullptr));
        motor_c_selector_btn->setText(QApplication::translate("MainWindow", "Motor C", nullptr));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Camera Stream:", nullptr));
        camera_stream->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Edit PID values: (all values are 1/1000 !) ", nullptr));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Kp", nullptr));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Ki", nullptr));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Kd", nullptr));
        start_pid->setText(QApplication::translate("MainWindow", "Start", nullptr));
        stop_pid->setText(QApplication::translate("MainWindow", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MRB_WINDOW_H
