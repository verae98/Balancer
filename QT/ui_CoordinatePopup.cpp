//
// Created by florian on 6/1/19.
//

#include "ui_CoordinatePopup.hpp"

ui_coordinate_popup::ui_coordinate_popup(QWidget *parent) : QWidget(parent) {
    ui.setupUi(this);
    ui.camera_still->setMouseTracking(true);
    ui.camera_still->installEventFilter(this);
}

void ui_coordinate_popup::setTargetText(const std::string &target) {
    ui.target_system_label->setText(target.c_str());
}

void ui_coordinate_popup::setCurrentCoordinates(Vec2i currentCoords) {
    this->currentCoords = currentCoords;
    std::string temp = "[";
    temp += std::to_string(currentCoords[0]);
    temp += ", ";
    temp += std::to_string(currentCoords[1]),
    temp += "]";
    ui.current_coordinates->setText(temp.c_str());
}

void ui_coordinate_popup::setCameraImage(const Mat &image) {
    Mat dest;
    cvtColor(image, dest, CV_BGR2RGB);
    QImage image1 = QImage((uchar *) dest.data, dest.cols, dest.rows, dest.step, QImage::Format_RGB888);
    auto map = QPixmap::fromImage(image1);
    ui.camera_still->setPixmap(map);
    ui.camera_still->setFixedSize(map.size());
    ui.camera_still->show();
}

bool ui_coordinate_popup::eventFilter(QObject *obj, QEvent *event) {
    if (qobject_cast<QLabel*>(obj)==ui.camera_still && event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
        currentCoords = Vec2i(mouseEvent->x(), mouseEvent->y());
        setCurrentCoordinates(currentCoords);
    }
    return false;
}

void ui_coordinate_popup::on_confirm_btn_clicked() {
    emit image_coordinate(currentCoords);
    this->close();
}

void ui_coordinate_popup::on_cancel_btn_clicked() {
    this->close();
}
