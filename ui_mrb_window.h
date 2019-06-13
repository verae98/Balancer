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
    QGroupBox *groupBox_8;
    QGroupBox *groupBox_9;
    QWidget *layoutWidget_3;
    QHBoxLayout *horizontalLayout_5;
    QSpinBox *lower_H_spinbox;
    QSlider *lower_H_slider;
    QGroupBox *groupBox_10;
    QWidget *layoutWidget_4;
    QHBoxLayout *horizontalLayout_6;
    QSpinBox *lower_S_spinbox;
    QSlider *lower_S_slider;
    QGroupBox *groupBox_11;
    QWidget *layoutWidget_5;
    QHBoxLayout *horizontalLayout_7;
    QSpinBox *lower_V_spinbox;
    QSlider *lower_V_slider;
    QGroupBox *groupBox_12;
    QGroupBox *groupBox_13;
    QWidget *layoutWidget_6;
    QHBoxLayout *horizontalLayout_8;
    QSpinBox *upper_H_spinbox;
    QSlider *upper_H_slider;
    QGroupBox *groupBox_14;
    QWidget *layoutWidget_7;
    QHBoxLayout *horizontalLayout_9;
    QSpinBox *upper_S_spinbox;
    QSlider *upper_S_slider;
    QGroupBox *groupBox_15;
    QWidget *layoutWidget_8;
    QHBoxLayout *horizontalLayout_10;
    QSpinBox *upper_V_spinbox;
    QSlider *upper_V_slider;
    QGroupBox *groupBox_16;
    QLabel *camera_stream_2;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1576, 1021);
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
        Kp_spinbox->setValue(-1009);

        horizontalLayout_2->addWidget(Kp_spinbox);

        Kp_slider = new QSlider(layoutWidget);
        Kp_slider->setObjectName(QStringLiteral("Kp_slider"));
        Kp_slider->setMinimum(-5000);
        Kp_slider->setMaximum(5000);
        Kp_slider->setValue(-1009);
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
        Ki_spinbox->setMinimum(-1000);
        Ki_spinbox->setMaximum(1000);
        Ki_spinbox->setValue(-67);

        horizontalLayout_3->addWidget(Ki_spinbox);

        Ki_slider = new QSlider(layoutWidget1);
        Ki_slider->setObjectName(QStringLiteral("Ki_slider"));
        Ki_slider->setMinimum(-1000);
        Ki_slider->setMaximum(1000);
        Ki_slider->setValue(-67);
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
        Kd_spinbox->setValue(-537);

        horizontalLayout_4->addWidget(Kd_spinbox);

        Kd_slider = new QSlider(layoutWidget_2);
        Kd_slider->setObjectName(QStringLiteral("Kd_slider"));
        Kd_slider->setMinimum(-5000);
        Kd_slider->setMaximum(5000);
        Kd_slider->setValue(-537);
        Kd_slider->setSliderPosition(-537);
        Kd_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(Kd_slider);

        start_pid = new QPushButton(centralwidget);
        start_pid->setObjectName(QStringLiteral("start_pid"));
        start_pid->setGeometry(QRect(360, 430, 80, 25));
        stop_pid = new QPushButton(centralwidget);
        stop_pid->setObjectName(QStringLiteral("stop_pid"));
        stop_pid->setGeometry(QRect(360, 460, 80, 25));
        groupBox_8 = new QGroupBox(centralwidget);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(1140, 30, 431, 281));
        groupBox_9 = new QGroupBox(groupBox_8);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(10, 30, 411, 71));
        layoutWidget_3 = new QWidget(groupBox_9);
        layoutWidget_3->setObjectName(QStringLiteral("layoutWidget_3"));
        layoutWidget_3->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget_3);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        lower_H_spinbox = new QSpinBox(layoutWidget_3);
        lower_H_spinbox->setObjectName(QStringLiteral("lower_H_spinbox"));
        lower_H_spinbox->setMinimum(0);
        lower_H_spinbox->setMaximum(255);
        lower_H_spinbox->setValue(0);

        horizontalLayout_5->addWidget(lower_H_spinbox);

        lower_H_slider = new QSlider(layoutWidget_3);
        lower_H_slider->setObjectName(QStringLiteral("lower_H_slider"));
        lower_H_slider->setMinimum(0);
        lower_H_slider->setMaximum(255);
        lower_H_slider->setValue(20);
        lower_H_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(lower_H_slider);

        groupBox_10 = new QGroupBox(groupBox_8);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(10, 110, 411, 71));
        layoutWidget_4 = new QWidget(groupBox_10);
        layoutWidget_4->setObjectName(QStringLiteral("layoutWidget_4"));
        layoutWidget_4->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_6 = new QHBoxLayout(layoutWidget_4);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        lower_S_spinbox = new QSpinBox(layoutWidget_4);
        lower_S_spinbox->setObjectName(QStringLiteral("lower_S_spinbox"));
        lower_S_spinbox->setMinimum(0);
        lower_S_spinbox->setMaximum(255);
        lower_S_spinbox->setValue(45);

        horizontalLayout_6->addWidget(lower_S_spinbox);

        lower_S_slider = new QSlider(layoutWidget_4);
        lower_S_slider->setObjectName(QStringLiteral("lower_S_slider"));
        lower_S_slider->setMinimum(0);
        lower_S_slider->setMaximum(255);
        lower_S_slider->setValue(0);
        lower_S_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(lower_S_slider);

        groupBox_11 = new QGroupBox(groupBox_8);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(10, 190, 411, 71));
        layoutWidget_5 = new QWidget(groupBox_11);
        layoutWidget_5->setObjectName(QStringLiteral("layoutWidget_5"));
        layoutWidget_5->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_7 = new QHBoxLayout(layoutWidget_5);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(0, 0, 0, 0);
        lower_V_spinbox = new QSpinBox(layoutWidget_5);
        lower_V_spinbox->setObjectName(QStringLiteral("lower_V_spinbox"));
        lower_V_spinbox->setMinimum(0);
        lower_V_spinbox->setMaximum(255);
        lower_V_spinbox->setValue(146);

        horizontalLayout_7->addWidget(lower_V_spinbox);

        lower_V_slider = new QSlider(layoutWidget_5);
        lower_V_slider->setObjectName(QStringLiteral("lower_V_slider"));
        lower_V_slider->setMinimum(0);
        lower_V_slider->setMaximum(255);
        lower_V_slider->setValue(130);
        lower_V_slider->setSliderPosition(130);
        lower_V_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(lower_V_slider);

        groupBox_12 = new QGroupBox(centralwidget);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(1140, 320, 431, 281));
        groupBox_13 = new QGroupBox(groupBox_12);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(10, 30, 411, 71));
        layoutWidget_6 = new QWidget(groupBox_13);
        layoutWidget_6->setObjectName(QStringLiteral("layoutWidget_6"));
        layoutWidget_6->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_8 = new QHBoxLayout(layoutWidget_6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        upper_H_spinbox = new QSpinBox(layoutWidget_6);
        upper_H_spinbox->setObjectName(QStringLiteral("upper_H_spinbox"));
        upper_H_spinbox->setMinimum(0);
        upper_H_spinbox->setMaximum(255);
        upper_H_spinbox->setValue(50);

        horizontalLayout_8->addWidget(upper_H_spinbox);

        upper_H_slider = new QSlider(layoutWidget_6);
        upper_H_slider->setObjectName(QStringLiteral("upper_H_slider"));
        upper_H_slider->setMinimum(0);
        upper_H_slider->setMaximum(255);
        upper_H_slider->setValue(40);
        upper_H_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(upper_H_slider);

        groupBox_14 = new QGroupBox(groupBox_12);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setGeometry(QRect(10, 110, 411, 71));
        layoutWidget_7 = new QWidget(groupBox_14);
        layoutWidget_7->setObjectName(QStringLiteral("layoutWidget_7"));
        layoutWidget_7->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget_7);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        upper_S_spinbox = new QSpinBox(layoutWidget_7);
        upper_S_spinbox->setObjectName(QStringLiteral("upper_S_spinbox"));
        upper_S_spinbox->setMinimum(0);
        upper_S_spinbox->setMaximum(255);
        upper_S_spinbox->setValue(255);

        horizontalLayout_9->addWidget(upper_S_spinbox);

        upper_S_slider = new QSlider(layoutWidget_7);
        upper_S_slider->setObjectName(QStringLiteral("upper_S_slider"));
        upper_S_slider->setMinimum(0);
        upper_S_slider->setMaximum(255);
        upper_S_slider->setValue(230);
        upper_S_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_9->addWidget(upper_S_slider);

        groupBox_15 = new QGroupBox(groupBox_12);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        groupBox_15->setGeometry(QRect(10, 190, 411, 71));
        layoutWidget_8 = new QWidget(groupBox_15);
        layoutWidget_8->setObjectName(QStringLiteral("layoutWidget_8"));
        layoutWidget_8->setGeometry(QRect(10, 30, 381, 28));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget_8);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        upper_V_spinbox = new QSpinBox(layoutWidget_8);
        upper_V_spinbox->setObjectName(QStringLiteral("upper_V_spinbox"));
        upper_V_spinbox->setMinimum(0);
        upper_V_spinbox->setMaximum(255);
        upper_V_spinbox->setValue(255);

        horizontalLayout_10->addWidget(upper_V_spinbox);

        upper_V_slider = new QSlider(layoutWidget_8);
        upper_V_slider->setObjectName(QStringLiteral("upper_V_slider"));
        upper_V_slider->setMinimum(0);
        upper_V_slider->setMaximum(255);
        upper_V_slider->setValue(255);
        upper_V_slider->setSliderPosition(255);
        upper_V_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_10->addWidget(upper_V_slider);

        groupBox_16 = new QGroupBox(centralwidget);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        groupBox_16->setGeometry(QRect(470, 510, 631, 481));
        camera_stream_2 = new QLabel(groupBox_16);
        camera_stream_2->setObjectName(QStringLiteral("camera_stream_2"));
        camera_stream_2->setGeometry(QRect(0, 20, 611, 451));
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
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Edit lower HSV values: ", nullptr));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "H", nullptr));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "S", nullptr));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "V", nullptr));
        groupBox_12->setTitle(QApplication::translate("MainWindow", "Edit upper HSV values: ", nullptr));
        groupBox_13->setTitle(QApplication::translate("MainWindow", "H", nullptr));
        groupBox_14->setTitle(QApplication::translate("MainWindow", "S", nullptr));
        groupBox_15->setTitle(QApplication::translate("MainWindow", "V", nullptr));
        groupBox_16->setTitle(QApplication::translate("MainWindow", "HSV Stream", nullptr));
        camera_stream_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MRB_WINDOW_H
