#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include <serial/serial.h>
#include <string>
#include <unistd.h>
#include <vector>
#include "QT/pidController.hpp"
#include "QT/ui_mrb_window.hpp"
#include "QT/ui_CoordinatePopup.hpp"
#include <QApplication>
#include <QTimer>
#include <sys/socket.h>

using namespace cv;

Vec2i setpoint = {0, 0};
Vec2i motorA = {0, 0};
Vec2i motorB = {0, 0};
Vec2i motorC = {0, 0};
Vec2i ball_pos = {0, 0};
int clicks = 0;

int test = 0;

std::vector<PIDController> controllers;

int main(int argc, char *argv[]) {
    std::string port = "/dev/ttyUSB0";
    unsigned long baudrate = 115200;
    serial::Serial arduino(port, baudrate, serial::Timeout::simpleTimeout(1000));
    usleep(500000);
    if (arduino.isOpen()) {
        std::cout << "Connected to arduino\n";
    } else {
        std::cout << "Coulnd't connect to arduino\n";
        return -1;
    }
    QApplication app(argc, argv);
    ui_coordinate_popup popup;
    mrb_window mainwindow(nullptr, &popup, &arduino);
    mainwindow.show();


    return app.exec();
}