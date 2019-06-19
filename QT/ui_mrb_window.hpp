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
    /**
     * Constructor of the UI
     * @param parent QMainWindow on which this UI is drawn.
     * @param coordinate_popup The popup pointer that lets us pick our motor positions and setpoint.
     * @param due Serial stream to communicate with the DUE
     */
    explicit mrb_window(QMainWindow *parent = nullptr, ui_coordinate_popup *coordinate_popup = nullptr,
                        serial::Serial *due = nullptr);

/**
 * This is some preprocessor macro magic from QT to find the event handlers for it's events.
 */
private slots:

    /**
     * @brief Signal handler for the button 'load stream'
     * @details Opens the selected camera or shows an error popup when there is no camera selected.
     */
    void on_load_stream_btn_clicked();

    /**
     * @brief Signal handler for the button 'Motor A'
     * @details Opens the coordinate popup to let the user pick a position for the motor.
     */
    void on_motor_a_selector_btn_clicked();

    /**
     * @brief Signal handler for the button 'Motor B'
     * @details Opens the coordinate popup to let the user pick a position for the motor.
     */
    void on_motor_b_selector_btn_clicked();

    /**
     * @brief Signal handler for the button 'Motor C'
     * @details Opens the coordinate popup to let the user pick a position for the motor.
     */
    void on_motor_c_selector_btn_clicked();

    /**
     * @brief Signal handler for the button 'Setpoint'
     * @details Opens the coordinate popup to let the user pick a new setpoint.
     */
    void on_setpoint_selector_btn_clicked();

    /**
     * @brief signal handler for the 'ok' button on the coordinate popup
     * @details this sets the new position of the appropriate motor.
     * @param newCoordinate the new position of the motor or setpoint that is being updated.
     */
    void processNewCoordinate(Vec2i newCoordinate);

    /**
     * @brief signal handler for changes to the P, I or D UI elements.
     * @details updates the P I D values for the different controllers whenever there's a change to a slider or a spinbox.
     * @param val
     */
    void updatePIDControllers(int val);

    /**
     * @brief signal handler for changes the the lower & upper HSV UI elements
     * @details updates all 6 HSV values (lower and upper) directly by getting the UI element values.
     * @param val this is a placeholder, this value isn't actually used but is needed for the signature.
     */
    void updateHSV(int val);

    /**
     * @brief Signal handler for the 'start' button
     * @details Sets the flag that tells the GUI that it should send commands to the arduino.
     * while the flag is not set, the PID values are being updated but no commands get sent to the arduino.
     */
    void on_start_pid_clicked();

    /**
     * @brief Signal handler for the 'start' button
     * @details Sets the flag that tells the GUI that it should send commands to the arduino.
     * while the flag is not set, the PID values are being updated but no commands get sent to the arduino.
     */
    void on_stop_pid_clicked();

protected:
    /**
     * @brief the update loop for the PID controllers
     * @details this event is fired every time that QT is done with it's eventloop, It handles the ball detection,
     * blob detection and the PID update as well as sending the relevant servo positions to the arduino.
     */
    void timerEvent(QTimerEvent *event);

private:
    /**
     * The generated UI files
     */
    Ui::MainWindow ui;
    /**
     * The ID of the timer that we create to call our update loop.
     */
    int timerId;
    /**
     * The selected camera number
     */
    int cameraId = -1;
    /**
     * The OpenCV camera stream
     */
    VideoCapture stream;
    /**
     * PID Controller for motor A
     */
    PIDController motorA;
    /**
     * PID Controller for motor B
     */
    PIDController motorB;
    /**
     * PID Controller for motor C
     */
    PIDController motorC;
    /**
     * Pointer to the popup-window that's used to select coordinates for the motors or the setpoint.
     */
    ui_coordinate_popup *popup_window;
    /**
     * The name of the target that the coordinate popup is updating, will be either "Motor A", "Motor B", "Motor C", or "Setpoint"
     */
    std::string current_target;
    /**
     * Pointer to the serial connection handler to the DUE
     */
    serial::Serial *due;

    /**
     * Upper bound of the H value
     */
    int upper_H = 0;

    /**
     * Upper bound of the S value
     */
    int upper_S = 0;

    /**
     * Upper bound of the V value
     */
    int upper_V = 0;


    /**
     * Lower bound of the H value
     */
    int lower_H = 0;
    /**
     * Lower bound of the S value
     */
    int lower_S = 0;
    /**
     * Lower bound of the V value
     */
    int lower_V = 0;

    /**
     * Flag for telling the update loop whether or not to send the servo positions to the DUE
     */
    bool running = false;

    /**
     * @brief helper function to find the camera ID's that can be used.
     * @details this method attempts to find all connected cameras by incrementing the ID until OpenCV gives an error.
     * @return
     */
    int countCameras();

    /**
     * @brief Handler for finding the coordinates of a click on a QLabel object relative to the label instead of the screen or the mainwindow.
     */
    void getClickedPointOnImage();

    /**
     * @brief Connect signal handlers for synchronizing the so-called "spinbox" elements and the slider elements.
     */
    void connectPIDSliderWithSpinboxes();

    /**
     * @brief Connect signal handlers for synchronizing the so-called "spinbox" elements and the slider elements.
     */
    void connectHSVSliderWithSpinboxes();

};


#endif //BALANCER_MRB_WINDOW_HPP
