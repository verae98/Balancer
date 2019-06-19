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
    /**
     * Construct a popup widget
     * @param parent the main window
     */
    explicit ui_coordinate_popup(QWidget *parent = nullptr);

    /**
     * @brief method for the main window to specify the target whose coordinates are being set.
     */
    void setTargetText(const std::string &target);

    /**
     * Set the current coordinates in a Label
     * @param currentCoords
     */
    void setCurrentCoordinates(Vec2i currentCoords);

    /**
     * Show a still so that the user knows where to click.
     * @param image
     */
    void setCameraImage(const Mat &image);

    /**
     * override the event filter to capture only mouseclicks that happen on the image.
     * @param obj
     * @param event
     * @return
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

public slots:

    /**
     * Event handler for the 'confirm' button
     */
    void on_confirm_btn_clicked();

    /**
     * Event handler for the 'cancel' button
     */
    void on_cancel_btn_clicked();
signals:

    /**
     * Signal the main window that there is a new coordinate.
     * @param targetCoordinate
     */
    void image_coordinate(Vec2i targetCoordinate);

protected:

private:
    /**
     * The generated ui so that QT knows what to draw and where.
     */
    Ui::Form ui;
    /**
     * Store the coordinate as it's being updated.
     */
    Vec2i currentCoords = {0, 0};
};


#endif //BALANCER_UICOORDINATEPOPUP_HPP
