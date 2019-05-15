#include "opencv2/opencv.hpp"
using namespace cv;

int main(int argc, char *argv[]) {
  VideoCapture cap;
  // open the default camera, use something different from 0 otherwise;
  // Check VideoCapture documentation.
  if (!cap.open(2))
    return 0;
  for (;;) {
    Mat img;
    cap >> img;
    // Read the image as gray-scale

    // Convert to gray-scale
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);
    medianBlur(gray, gray, 5);
    std::vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 gray.rows / 16,  // change this value to detect circles with
                                  // different distances to each other
                 100, 30, 10, 100 // change the last two parameters
                 // (min_radius & max_radius) to detect larger circles
    );
    Mat final_output(img.rows, img.cols, CV_8UC1);
    for (size_t i = 0; i < circles.size(); i++) {

      Vec3i c = circles[i];
      Point center = Point(c[0], c[1]);
      Vec3b col = img.at<Vec3b>(center); // colour of circle
      if (col[2] > 200 && col[1] < 50 && col[0] < 50) {
        // circle center
        circle(final_output, center, 1, Scalar(0, 100, 100), 3, LINE_AA);
        // circle outline
        int radius = c[2];
        circle(final_output, center, radius, col, 3, LINE_AA);
        circle(img, center, radius, (255, 30, 255), 3, LINE_AA);
      }
    }
    imshow("detected circles", img);
    imshow("magic", final_output);
    if (waitKey(10) == 27) {
      break;
    }
  }
  return 0;
}