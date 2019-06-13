//
// Created by florian on 6/1/19.
//

#ifndef BALANCER_MRB_WINDOW_HPP
#define BALANCER_MRB_WINDOW_HPP

#include "../ui_mrb_window.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <QTimer>
#include <QtWidgets/QMessageBox>
#include "pidController.hpp"
#include "ui_CoordinatePopup.hpp"
#include <serial/serial.h>
#include <opencv2/features2d.hpp>

using namespace cv;

class mrb_window : public QMainWindow {
Q_OBJECT

public:
    explicit mrb_window(QMainWindow *parent = nullptr, ui_coordinate_popup * coordinate_popup = nullptr, serial::Serial * due = nullptr);

private slots:

    void on_load_stream_btn_clicked();
    void on_motor_a_selector_btn_clicked();
    void on_motor_b_selector_btn_clicked();
    void on_motor_c_selector_btn_clicked();
    void on_setpoint_selector_btn_clicked();
    void processNewCoordinate(Vec2i newCoordinate);
    void updatePIDControllers(int val);

    void updateHSV(int val);
    void on_start_pid_clicked();
    void on_stop_pid_clicked();
protected:
    void timerEvent(QTimerEvent *event);
private:
    Ui::MainWindow ui;
    int timerId;
    int cameraId = -1;
    int test = 0;
    VideoCapture stream;
    PIDController motorA;
    PIDController motorB;
    PIDController motorC;
    ui_coordinate_popup * popup_window;
    std::string current_target;
    serial::Serial * due;

    int upper_H = 0;
    int upper_S = 0;
    int upper_V = 0;

    int lower_H = 0;
    int lower_S = 0;
    int lower_V = 0;

    bool running = false;
    int countCameras();
    void getClickedPointOnImage();
    void connectPIDSliderWithSpinboxes();

    void connectHSVSliderWithSpinboxes();

};


#endif //BALANCER_MRB_WINDOW_HPP
