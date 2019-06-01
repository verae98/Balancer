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


//static void onMouseDown(int event, int x, int y, int flags, void *params) {
//    if (event == EVENT_LBUTTONDOWN) {
//        switch (clicks) {
//            case 0:
//                setpoint = Vec2i(x, y);
//                for(auto & controller : controllers){
//                    controller.updateSetpoint(setpoint);
//                }
//                break;
//            case 1:
//                controllers[0].setMotorPos(Vec2i(x, y));
//                break;
//            case 2:
//                controllers[1].setMotorPos(Vec2i(x, y));
//                break;
//            case 3:
//                controllers[2].setMotorPos(Vec2i(x, y));
//                break;
//            default:
//                setpoint = Vec2i(x, y);
//                for(auto & controller : controllers){
//                    controller.updateSetpoint(setpoint);
//                }
//                break;
//        }
//        clicks++;
//    }
//}
//
//int main(int argc, char *argv[]) {
//    controllers.emplace_back(PIDController());
//    controllers.emplace_back(PIDController());
//    controllers.emplace_back(PIDController());
//    auto ports = serial::list_ports();
//    std::string port = "/dev/ttyUSB0";
//    unsigned long baudrate = 115200;
//    serial::Serial arduino(port, baudrate, serial::Timeout::simpleTimeout(1000));
//    usleep(500000);
//    if (arduino.isOpen()) {
//        std::cout << "Connected to arduino\n";
//    } else {
//        std::cout << "Coulnd't connect to arduino\n";
//        return -1;
//    }
//
//    VideoCapture cap;
//    // open the default camera, use something different from 0 otherwise;
//    // Check VideoCapture documentation.
//    if (!cap.open(2))
//        return 0;
//
//    Mat img1;
//    cap >> img1;
//    // Create a window
//    namedWindow("ImageDisplay", 1);
//    setMouseCallback("ImageDisplay", onMouseDown);
//    Mat img;
//    while (clicks < 4) {
//        cap >> img;
//        imshow("ImageDisplay", img);
//        if (waitKey(10) == 27) {
//            return 0;
//        }
//    }
//    std::cout << "Setpoint: " << setpoint << "\n";
//    for (;;) {
//
//        // Read the image as gray-scale
//        cap >> img;
//        // Convert to gray-scale
//        Mat gray;
//        cvtColor(img, gray, COLOR_BGR2GRAY);
//
//        medianBlur(gray, gray, 5);
//        std::vector<Vec3f> circles;
//        HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
//                     20,             // change this value to detect circles with
//                // different distances to each other
//                     100, 30, 20, 50 // change the last two parameters
//                // (min_radius & max_radius) to detect larger circles
//        );
//        Mat final_output(img.rows, img.cols, CV_8UC1);
//        for (size_t i = 0; i < circles.size(); i++) {
//
//            Vec3f c = circles[i];
//            Point center = Point(c[0], c[1]);
//            int radius = c[2];
//
//            // std::cout << center << std::endl;
//            Vec3b intensity = img.at<Vec3b>(center.y, center.x);
//            // std::cout << (int)intensity[2] << " " << (int)intensity[1] << " "
//            //           << (int)intensity[0] << "\n";
//            int min = 255;
//            int max = 0;
//
//            for (int i = 0; i < 2; i++) {
//                if (intensity[i] < min) {
//                    min = intensity[i];
//                }
//                if (intensity[i] > max) {
//                    max = intensity[i];
//                }
//            }
//
//            if ((max - min) < 30 && min > 100) {
//                ball_pos[0] = center.x;
//                ball_pos[1] = center.y;
//                for(auto & controller : controllers){
//                    controller.step(ball_pos);
//                }
//
//                std::string action;
//                action += std::to_string((int) controllers[0].getMappedPIDAction());
//                action += ";";
//                action += std::to_string((int) controllers[0].getMappedPIDAction());
//                action += ";";
//                action += std::to_string((int) controllers[0].getMappedPIDAction());
//                action += ";\n";
//                if (test % 10 == 0) {
//                    arduino.write(action);
//                }
//
//                std::cout << action << std::endl;
//                action = "";
//                test++;
//                std::string rec = "";
//                std::cout << rec << std::endl;
//                circle(img, center, radius, (255, 30, 255), 3, LINE_AA);
//                break;
//            }
//        }
//        imshow("ImageDisplay", img);
//        if (waitKey(10) == 27) {
//            break;
//        }
//    }
//    return 0;
//}