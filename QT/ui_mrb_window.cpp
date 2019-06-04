//
// Created by florian on 6/1/19.
//

#include "ui_mrb_window.hpp"

mrb_window::mrb_window(QMainWindow *parent, ui_coordinate_popup *coordinate_popup, serial::Serial *due)
        : QMainWindow(parent), popup_window(coordinate_popup), due(due) {
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
    timerId = startTimer(0);
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
    cvtColor(frame, dest, COLOR_BGR2RGB);
    Mat gray;
    cvtColor(frame, gray, COLOR_BGR2GRAY);

    medianBlur(gray, gray, 5);
    std::vector<Vec3f> circles;
    HoughCircles(gray, circles, HOUGH_GRADIENT, 1,
                 20,             // change this value to detect circles with
            // different distances to each other
                 100, 30, 20, 50 // change the last two parameters
            // (min_radius & max_radius) to detect larger circles
    );
    Mat final_output(frame.rows, frame.cols, CV_8UC1);
    for (size_t i = 0; i < circles.size(); i++) {

        Vec3f c = circles[i];
        Point center = Point(c[0], c[1]);
        int radius = c[2];

        // std::cout << center << std::endl;
        Vec3b intensity = frame.at<Vec3b>(center.y, center.x);
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
            Vec2i ball_pos;
            ball_pos[0] = center.x;
            ball_pos[1] = center.y;
            motorA.step(ball_pos);
            motorB.step(ball_pos);
            motorC.step(ball_pos);

            std::string action;
            action += std::to_string((int) motorA.getMappedPIDAction());
            action += ";";
            action += std::to_string((int) motorB.getMappedPIDAction());
            action += ";";
            action += std::to_string((int) motorC.getMappedPIDAction());
            action += ";\n";
            if (test % 10 == 0) {
                if(due->isOpen()) {
                    due->write(action);
                }else{
                    due->open();
                    due->write(action);
                }
                std::cout << action << std::endl;
                test = 0;
            }
            test++;

            action = "";
            if(due->available()) {
                std::string rec = due->readline();
                std::cout << rec << std::endl;
            }
            circle(frame, center, radius, (255, 30, 255), 3, LINE_AA);
            break;
        }
    }

    auto motor_color = Scalar(66, 244, 78);
    auto setpoint_color = Scalar(66, 66 ,244);
    circle(frame, motorA.getMotorPos(), 5, motor_color, 5, LINE_AA);
    circle(frame, motorB.getMotorPos(), 5, motor_color, 5, LINE_AA);
    circle(frame, motorC.getMotorPos(), 5, motor_color, 5, LINE_AA);
    circle(frame, motorA.getSetpoint(), 5, setpoint_color, 5, LINE_AA);

    auto font = FONT_HERSHEY_SIMPLEX;
    putText(frame, "A", motorA.getMotorPos() + Vec2i(10, -4), font, 1, motor_color, 2, LINE_AA);
    putText(frame, "B", motorB.getMotorPos() + Vec2i(10, -4), font, 1, motor_color, 2, LINE_AA);
    putText(frame, "C", motorC.getMotorPos() + Vec2i(10, -4), font, 1, motor_color, 2, LINE_AA);
    putText(frame, "S", motorC.getSetpoint() + Vec2i(10, -4), font, 1, setpoint_color, 2, LINE_AA);


    // Draw the image to the QT Label
    cvtColor(frame, dest, CV_BGR2RGB);
    QImage image1 = QImage((uchar *) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    ui.camera_stream->setPixmap(QPixmap::fromImage(image1));
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

void mrb_window::updatePIDControllers(int val) {
    float P = ui.Kp_spinbox->value() / 1000;
    float I = ui.Ki_spinbox->value() / 1000;
    float D = ui.Kd_spinbox->value() / 1000;

    motorA.setWeights(P, I, D);
    motorB.setWeights(P, I, D);
    motorC.setWeights(P, I, D);
}


