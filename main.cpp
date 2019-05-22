#include "opencv2/opencv.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>

using namespace cv;

Vec2i setpoint = {0, 0};
Vec2i motorA = {0, 0};
Vec2i motorB = {0, 0};
Vec2i motorC = {0, 0};

int clicks = 0;



static void onMouseDown(int event, int x, int y, int flags, void *params) {
  if (event == EVENT_LBUTTONDOWN) {
    switch (clicks) {
    case 0:
      setpoint = Vec2i(x, y);
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
    }
    clicks++;
  }
}

int main(int argc, char *argv[]) {

  std::string str; 
  std::fstream f; 
  f.open("/dev/ttyUSB0"); 
  usleep(500000);

  while(1){
    f << "80;80;80;\n";
    std::cout << "f 80\n";
    usleep(500000);
    f << "100;100;100;\n";
    std::cout << "f 100\n";
    usleep(500000);
    f << "120;120;120;\n";
    std::cout << "f 120\n";
    usleep(500000);
  }
  f.close(); 

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
                 100, 30, 15, 30 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
    );
    Mat final_output(img.rows, img.cols, CV_8UC1);
    for (size_t i = 0; i < circles.size(); i++) {

      Vec3f c = circles[i];
      Point center = Point(c[0], c[1]);
      int radius = c[2];

      std::cout << center << std::endl;
      circle(img, center, radius, (255, 30, 255), 3, LINE_AA);
    }
    imshow("ImageDisplay", img);
    if (waitKey(10) == 27) {
      break;
    }
  }
  return 0;
}