#include "opencv2/opencv.hpp"
#include <fstream>
#include <iostream>
#include <serial/serial.h>
#include <string>
#include <unistd.h>

using namespace cv;

Vec2i setpoint = {0, 0};
Vec2i motorA = {0, 0};
Vec2i motorB = {0, 0};
Vec2i motorC = {0, 0};
Vec2i ball_pos = {0, 0};
int clicks = 0;
float distance_mA = 0;
float distance_mB = 0;
float distance_mC = 0;

float previous_error_a = 0;
float previous_error_b = 0;
float previous_error_c = 0;

float total_error_a = 0;
float total_error_b = 0;
float total_error_c = 0;

int test = 0;

float map(float error, int e_lower, int e_upper, int r_lower, int r_upper) {
  return (error - e_lower) * (r_upper - r_lower) / (e_upper - e_lower) +
         r_lower;
}

float getDistanceTo(Vec2i target, Vec2i motor) {
  return sqrt(pow(target[0] - motor[0], 2) + pow(target[1] - motor[1], 2));
}

static void onMouseDown(int event, int x, int y, int flags, void *params) {
  if (event == EVENT_LBUTTONDOWN) {
    switch (clicks) {
    case 0:
      setpoint = Vec2i(x, y);
      distance_mA = getDistanceTo(setpoint, motorA);
      distance_mB = getDistanceTo(setpoint, motorB);
      distance_mC = getDistanceTo(setpoint, motorC);
      break;
    case 1:
      motorA = Vec2i(x, y);
      break;
    case 2:
      motorB = Vec2i(x, y);
      break;
    case 3:
      motorC = Vec2i(x, y);
      break;
    default:
      setpoint = Vec2i(x, y);
      distance_mA = getDistanceTo(setpoint, motorA);
      distance_mB = getDistanceTo(setpoint, motorB);
      distance_mC = getDistanceTo(setpoint, motorC);
      break;
    }
    clicks++;
  }
}

int main(int argc, char *argv[]) {
  auto ports = serial::list_ports();
  for (auto t : ports) {
    std::cout << t.port << std::endl;
  }
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
  std::string buff;

  // while (1) {
  //   arduino.write("80;80;80;\n");
  //   arduino.read(buff, 20);
  //   std::cout << buff;
  //   usleep(2500000);
  //   arduino.write("90;90;90;\n");
  //   arduino.read(buff, 20);
  //   std::cout << buff;
  //   usleep(2500000);
  // }

  VideoCapture cap;
  // open the default camera, use something different from 0 otherwise;
  // Check VideoCapture documentation.
  if (!cap.open(2))
    return 0;

  Mat img1;
  cap >> img1;
  // Create a window
  namedWindow("ImageDisplay", 1);
  setMouseCallback("ImageDisplay", onMouseDown);
  Mat img;
  while (clicks < 4) {
    cap >> img;
    imshow("ImageDisplay", img);
    if (waitKey(10) == 27) {
      break;
    }
  }
  std::cout << "Setpoint: " << setpoint << "\n";
  std::cout << "motorA: " << motorA << "\n";
  std::cout << "motorB: " << motorB << "\n";
  std::cout << "motorC: " << motorC << "\n";
  for (;;) {

    // Read the image as gray-scale
    cap >> img;
    // Convert to gray-scale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray, 5);
    std::vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 20,             // change this value to detect circles with
                                 // different distances to each other
                 100, 30, 20, 50 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
    );
    Mat final_output(img.rows, img.cols, CV_8UC1);
    for (size_t i = 0; i < circles.size(); i++) {

      Vec3f c = circles[i];
      Point center = Point(c[0], c[1]);
      int radius = c[2];

      // std::cout << center << std::endl;
      Vec3b intensity = img.at<Vec3b>(center.y, center.x);
      // std::cout << (int)intensity[2] << " " << (int)intensity[1] << " "
      //           << (int)intensity[0] << "\n";
      int min = 255;
      int max = 0;

      for (int i = 0; i < 2; i++) {
        if (intensity[i] < min) {
          min = intensity[i];
        }
        if (intensity[i] > max) {
          max = intensity[i];
        }
      }

      if ((max - min) < 30 && min > 100) {
        ball_pos[0] = center.x;
        ball_pos[1] = center.y;

        int error_mA = 0;
        int error_mB = 0;
        int error_mC = 0;

        float ball_mA = getDistanceTo(ball_pos, motorA);
        float ball_mB = getDistanceTo(ball_pos, motorB);
        float ball_mC = getDistanceTo(ball_pos, motorC);

        error_mA = distance_mA - ball_mA;
        error_mB = distance_mB - ball_mB;
        error_mC = distance_mC - ball_mC;

        float Kp = 0.2;
        float Ki = 0;
        float Kd = 0.04;

        float action_motor_A =
            (Kp * error_mA) + (Kd * ((error_mA - previous_error_a) / 0.01));
        float action_motor_B =
            (Kp * error_mB) + (Kd * ((error_mB - previous_error_b) / 0.01));
        float action_motor_C =
            (Kp * error_mC) + (Kd * ((error_mC - previous_error_c) / 0.01));

        previous_error_a = error_mA;
        previous_error_b = error_mB;
        previous_error_c = error_mC;

        std::string action;
        action += std::to_string((int)map(action_motor_A, -300, 300, 90, 75));
        action += ";";
        action += std::to_string((int)map(action_motor_B, -300, 300, 90, 75));
        action += ";";
        action += std::to_string((int)map(action_motor_C, -300, 300, 90, 75));
        action += ";\n";
        if (test % 10 == 0) {
          arduino.write(action);
        }

        std::cout << action << std::endl;
        action = "";
        test++;
        std::string rec;
        // usleep(100000);
        // while(arduino.available()){
        // arduino.read(rec, 11);
        // }
        std::cout << rec << std::endl;
        circle(img, center, radius, (255, 30, 255), 3, LINE_AA);
        break;
      }
    }
    imshow("ImageDisplay", img);
    if (waitKey(10) == 27) {
      break;
    }
  }
  return 0;
}