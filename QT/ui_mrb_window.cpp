//
// Created by florian on 6/1/19.
//

#include "ui_mrb_window.hpp"

mrb_window::mrb_window(QMainWindow *parent, ui_coordinate_popup *coordinate_popup, serial::Serial *due)
        : QMainWindow(parent), popup_window(coordinate_popup), due(due), motorA('A'), motorB('B'), motorC('C') {
    ui.setupUi(this);
    int connected_camera_count = countCameras();
    QStringList cameras;
    cameras << (QStringList() << "");
    for (size_t i = 0; i < connected_camera_count; i++) {
        cameras << (QStringList() << ("Camera " + std::to_string(i)).c_str());
    }
    ui.load_stream_capture_list->addItems(cameras);
    connect(coordinate_popup, SIGNAL(image_coordinate(Vec2i)), this, SLOT(processNewCoordinate(Vec2i)));
    connectPIDSliderWithSpinboxes();
    connectHSVSliderWithSpinboxes();
    timerId = startTimer(0);
    motorA.setMotorPos(Vec2i(495, 299));
    motorB.setMotorPos(Vec2i(158, 370));
    motorC.setMotorPos(Vec2i(272, 50));
    motorA.updateSetpoint(Vec2i(281, 246));
    motorB.updateSetpoint(Vec2i(281, 246));
    motorC.updateSetpoint(Vec2i(281, 246));
    Vec2i center = (motorA.getMotorPos() + motorB.getMotorPos() + motorC.getMotorPos()) / 3;
    motorA.center_point = center;
    motorB.center_point = center;
    motorC.center_point = center;
    updatePIDControllers(0);
    updateHSV(0);
}

void mrb_window::on_load_stream_btn_clicked() {
    auto currentText = ui.load_stream_capture_list->currentText().split(" ");
    if (currentText.size() == 1) {
        QMessageBox msg;
        msg.setText("Please select a camera first!");
        msg.exec();
        return;
    }

    cameraId = currentText[1].toInt();
    stream.open(cameraId);
    if (!stream.isOpened()) {
        QMessageBox msg;
        std::string text = "Camera with id ";
        text += std::to_string(cameraId);
        text += " could not be opened!";
        cameraId = -1;
        ui.load_stream_capture_list->setCurrentIndex(0);
        msg.setText(text.c_str());
        msg.exec();
        return;
    }
}

void mrb_window::timerEvent(QTimerEvent *event) {
    if (cameraId == -1) {
        return;
    }
    Mat frame;
    stream >> frame;
    Mat dest;
    Mat hsv_image;
    cvtColor(frame, dest, COLOR_BGR2RGB);
    cvtColor(frame, hsv_image, COLOR_BGR2HSV);
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray, 5);
    std::vector<Vec3f> circles;


    Mat red_hue_image;
    inRange(hsv_image, Scalar(lower_H, lower_S, lower_V), Scalar(upper_H, upper_S, upper_V), red_hue_image);
    GaussianBlur(red_hue_image, red_hue_image, Size(3, 3), 3);
    erode(red_hue_image, red_hue_image, Mat(), Point(-1, -1), 13);
    dilate(red_hue_image, red_hue_image, Mat(), Point(-1, -1), 13);

    SimpleBlobDetector::Params blob_params;

    // Set params for binary image
    blob_params.filterByColor = false;
    blob_params.blobColor = 255; //blobs are white
    blob_params.minThreshold = 127;
    blob_params.thresholdStep = 1;
    blob_params.maxThreshold = blob_params.minThreshold + blob_params.thresholdStep;
    blob_params.minRepeatability = 1;
    // other parameters
    blob_params.filterByInertia = false;
    blob_params.filterByConvexity = false;
    blob_params.filterByCircularity = false;
    blob_params.filterByArea = true;
    blob_params.minArea = 3.14159 * 10.0f * 10.0f; // Min 10.0f diameter
    blob_params.maxArea = 3.14159 * 40.0f * 40.0f; // Max 20.0f diameter


    //detects blobs
    auto detector = SimpleBlobDetector::create(blob_params);
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(red_hue_image, keypoints);


    drawKeypoints(frame, keypoints, frame, Scalar(0, 0, 255), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);


    //HoughCircles(red_hue_image, circles, HOUGH_GRADIENT, 1, 200, 120, 17, 0, 0);

    Mat final_output(frame.rows, frame.cols, CV_8UC1);
    for (size_t i = 0; i < keypoints.size(); i++) {

        Point center = keypoints[i].pt;
        int radius = keypoints[i].size / 2;

        Vec2i ball_pos;
        ball_pos[0] = center.x;
        ball_pos[1] = center.y - radius * 0.8;
        motorA.step(ball_pos);
        motorB.step(ball_pos);
        motorC.step(ball_pos);
        if (running) {
            std::string temp_action;
            std::string action;
            temp_action = std::to_string((int) motorA.getMappedPIDAction());
            while (temp_action.length() < 3) {
                temp_action = "0" + temp_action;
            }
            action += temp_action;
            action += ";";
            temp_action = std::to_string((int) motorB.getMappedPIDAction());
            while (temp_action.length() < 3) {
                temp_action = "0" + temp_action;
            }
            action += temp_action;
            action += ";";
            temp_action = std::to_string((int) motorC.getMappedPIDAction());
            while (temp_action.length() < 3) {
                temp_action = "0" + temp_action;
            }
            action += temp_action;
            action += ";\n";
//                if (test % 10 == 0) {
            if (due->isOpen()) {
                due->write(action);
            } else {
                due->open();
                due->write(action);
            }
            std::cout << "Current Error A = " << std::to_string(motorA.current_error) << std::endl;
            std::cout << "Current Error B = " << std::to_string(motorB.current_error) << std::endl;
            std::cout << "Current Error C = " << std::to_string(motorC.current_error) << std::endl;

            std::cout << action << std::endl;
//                    test = 0;
//                }
//                test++;

            action = "";
            if (due->available()) {
                std::string rec = due->readline();
                std::cout << rec << std::endl;
            }
//            break;
        }
        std::vector<cv::KeyPoint> keypoints1 = {keypoints[0]};
        drawKeypoints(frame, keypoints1, frame, Scalar(255, 0, 0), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);
        break;
    }

    auto motor_color = Scalar(66, 244, 78);
    auto setpoint_color = Scalar(66, 66, 244);
    circle(frame, motorA.getMotorPos(), 5, motor_color, 5, LINE_AA);
    circle(frame, motorB.getMotorPos(), 5, motor_color, 5, LINE_AA);
    circle(frame, motorC.getMotorPos(), 5, motor_color, 5, LINE_AA);
    circle(frame, motorA.getSetpoint(), 5, setpoint_color, 5, LINE_AA);

    auto font = FONT_HERSHEY_SIMPLEX;
    putText(frame, "A", motorA.getMotorPos() + Vec2i(10, -4), font, 1, motor_color, 2, LINE_AA);
    putText(frame, "B", motorB.getMotorPos() + Vec2i(10, -4), font, 1, motor_color, 2, LINE_AA);
    putText(frame, "C", motorC.getMotorPos() + Vec2i(10, -4), font, 1, motor_color, 2, LINE_AA);
    putText(frame, "S", motorC.getSetpoint() + Vec2i(10, -4), font, 1, setpoint_color, 2, LINE_AA);


    cvtColor(frame, dest, CV_BGR2RGB);

    QImage image = QImage((uchar *) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    QImage image1 = QImage((uchar *) red_hue_image.data, red_hue_image.cols, red_hue_image.rows, red_hue_image.step,
                           QImage::Format_Grayscale8);
    ui.camera_stream->setPixmap(QPixmap::fromImage(image));
    ui.camera_stream->show();
    ui.camera_stream_2->setPixmap(QPixmap::fromImage(image1));
    ui.camera_stream->show();
}

int mrb_window::countCameras() {
    cv::VideoCapture temp_camera;
    int maxTested = 10;
    for (int i = 0; i < maxTested; i++) {
        cv::VideoCapture temp_camera(i);
        bool res = (!temp_camera.isOpened());
        temp_camera.release();
        if (res) {
            return i;
        }
    }
    return maxTested;
}

void mrb_window::on_motor_a_selector_btn_clicked() {
    current_target = "Motor A";
    getClickedPointOnImage();
}

void mrb_window::on_motor_b_selector_btn_clicked() {
    current_target = "Motor B";
    getClickedPointOnImage();
}

void mrb_window::on_motor_c_selector_btn_clicked() {
    current_target = "Motor C";
    getClickedPointOnImage();
}

void mrb_window::on_setpoint_selector_btn_clicked() {
    current_target = "Setpoint";
    getClickedPointOnImage();
}

void mrb_window::getClickedPointOnImage() {
    if (!stream.isOpened()) {
        auto currentText = ui.load_stream_capture_list->currentText().split(" ");
        if (currentText.size() == 1) {
            QMessageBox msg;
            msg.setText("Please select a camera first!");
            msg.exec();
            return;
        }

        cameraId = currentText[1].toInt();
        stream.open(cameraId);
        if (!stream.isOpened()) {
            QMessageBox msg;
            std::string text = "Camera with id ";
            text += std::to_string(cameraId);
            text += " could not be opened!";
            cameraId = -1;
            ui.load_stream_capture_list->setCurrentIndex(0);
            msg.setText(text.c_str());
            msg.exec();
            return;
        }
    }
    std::cout << "Building popup" << std::endl;

    popup_window->setCurrentCoordinates(Vec2i(0, 0));
    popup_window->setTargetText(current_target);
    Mat temp;
    stream >> temp;
    popup_window->setCameraImage(temp);
    popup_window->show();
    std::cout << "showing popup" << std::endl;
}


void mrb_window::processNewCoordinate(Vec2i newCoordinate) {
    if (current_target == "Motor A") {
        motorA.setMotorPos(newCoordinate);
        std::cout << "Motor A coordinates upadted" << std::endl;
    } else if (current_target == "Motor B") {
        motorB.setMotorPos(newCoordinate);
        std::cout << "Motor B coordinates upadted" << std::endl;
    } else if (current_target == "Motor C") {
        motorC.setMotorPos(newCoordinate);
        std::cout << "Motor C coordinates upadted" << std::endl;
    } else if (current_target == "Setpoint") {
        motorA.updateSetpoint(newCoordinate);
        motorB.updateSetpoint(newCoordinate);
        motorC.updateSetpoint(newCoordinate);
        std::cout << "Setpoint Updated" << std::endl;
    }

    Vec2i center = (motorA.getMotorPos() + motorB.getMotorPos() + motorC.getMotorPos()) / 3;
    motorA.center_point = center;
    motorB.center_point = center;
    motorC.center_point = center;
}

void mrb_window::connectPIDSliderWithSpinboxes() {
    connect(ui.Kp_spinbox, SIGNAL(valueChanged(int)), ui.Kp_slider, SLOT(setValue(int)));
    connect(ui.Kp_slider, SIGNAL(valueChanged(int)), ui.Kp_spinbox, SLOT(setValue(int)));

    connect(ui.Ki_spinbox, SIGNAL(valueChanged(int)), ui.Ki_slider, SLOT(setValue(int)));
    connect(ui.Ki_slider, SIGNAL(valueChanged(int)), ui.Ki_spinbox, SLOT(setValue(int)));

    connect(ui.Kd_spinbox, SIGNAL(valueChanged(int)), ui.Kd_slider, SLOT(setValue(int)));
    connect(ui.Kd_slider, SIGNAL(valueChanged(int)), ui.Kd_spinbox, SLOT(setValue(int)));

    connect(ui.Kp_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updatePIDControllers(int)));
    connect(ui.Kd_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updatePIDControllers(int)));
    connect(ui.Ki_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updatePIDControllers(int)));
}


void mrb_window::connectHSVSliderWithSpinboxes() {
    connect(ui.upper_S_spinbox, SIGNAL(valueChanged(int)), ui.upper_S_slider, SLOT(setValue(int)));
    connect(ui.upper_S_slider, SIGNAL(valueChanged(int)), ui.upper_S_spinbox, SLOT(setValue(int)));

    connect(ui.upper_H_spinbox, SIGNAL(valueChanged(int)), ui.upper_H_slider, SLOT(setValue(int)));
    connect(ui.upper_H_slider, SIGNAL(valueChanged(int)), ui.upper_H_spinbox, SLOT(setValue(int)));

    connect(ui.upper_V_spinbox, SIGNAL(valueChanged(int)), ui.upper_V_slider, SLOT(setValue(int)));
    connect(ui.upper_V_slider, SIGNAL(valueChanged(int)), ui.upper_V_spinbox, SLOT(setValue(int)));

    connect(ui.upper_H_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateHSV(int)));
    connect(ui.upper_S_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateHSV(int)));
    connect(ui.upper_V_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateHSV(int)));

    connect(ui.lower_S_spinbox, SIGNAL(valueChanged(int)), ui.lower_S_slider, SLOT(setValue(int)));
    connect(ui.lower_S_slider, SIGNAL(valueChanged(int)), ui.lower_S_spinbox, SLOT(setValue(int)));

    connect(ui.lower_H_spinbox, SIGNAL(valueChanged(int)), ui.lower_H_slider, SLOT(setValue(int)));
    connect(ui.lower_H_slider, SIGNAL(valueChanged(int)), ui.lower_H_spinbox, SLOT(setValue(int)));

    connect(ui.lower_V_spinbox, SIGNAL(valueChanged(int)), ui.lower_V_slider, SLOT(setValue(int)));
    connect(ui.lower_V_slider, SIGNAL(valueChanged(int)), ui.lower_V_spinbox, SLOT(setValue(int)));

    connect(ui.lower_H_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateHSV(int)));
    connect(ui.lower_S_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateHSV(int)));
    connect(ui.lower_V_spinbox, SIGNAL(valueChanged(int)), this, SLOT(updateHSV(int)));
}

void mrb_window::updateHSV(int val) {
    upper_H = ui.upper_H_spinbox->value();
    upper_S = ui.upper_S_spinbox->value();
    upper_V = ui.upper_V_spinbox->value();

    lower_H = ui.lower_H_spinbox->value();
    lower_S = ui.lower_S_spinbox->value();
    lower_V = ui.lower_V_spinbox->value();
}


void mrb_window::updatePIDControllers(int val) {
    float P = ui.Kp_spinbox->value();
    float I = ui.Ki_spinbox->value();
    float D = ui.Kd_spinbox->value();

    motorA.setWeights(P, I, D);
    motorB.setWeights(P, I, D);
    motorC.setWeights(P, I, D);
}

void mrb_window::on_stop_pid_clicked() {
    running = false;
}

void mrb_window::on_start_pid_clicked() {
    running = true;
}


