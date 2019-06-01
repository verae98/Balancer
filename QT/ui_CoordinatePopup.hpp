//
// Created by florian on 6/1/19.
//

#ifndef BALANCER_UICOORDINATEPOPUP_HPP
#define BALANCER_UICOORDINATEPOPUP_HPP

#include "../ui_coordinate_popup.h"
#include <iostream>
#include "opencv2/opencv.hpp"
#include <QMouseEvent>

using namespace cv;

class ui_coordinate_popup : public QWidget {
Q_OBJECT
public:
    explicit ui_coordinate_popup(QWidget *parent = nullptr);

    void setTargetText(const std::string &target);

    void setCurrentCoordinates(Vec2i currentCoords);

    void setCameraImage(const Mat &image);

    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:
    void on_confirm_btn_clicked();
    void on_cancel_btn_clicked();
signals:
    void image_coordinate(Vec2i targetCoordinate);

protected:

private:
    Ui::Form ui;
    Vec2i currentCoords = {0, 0};
};


#endif //BALANCER_UICOORDINATEPOPUP_HPP
