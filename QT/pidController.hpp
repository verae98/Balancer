//
// Created by florian on 6/1/19.
//

#ifndef BALANCER_PIDCONTROLLER_HPP
#define BALANCER_PIDCONTROLLER_HPP

#include "opencv2/opencv.hpp"

using namespace cv;


class PIDController {
    float distance_to_setpoint = 0;
    float total_error = 0;
    float previous_error = 1;
    int step_count = 0;
    Vec2i motor_pos = {0, 0};
    Vec2i setpoint = {0, 0};
    Vec2i ball_pos = {281, 246};
    float Kp = 0.2;
    float Kd = 0;
    float Ki = 0.04;
    char name;

public:
    explicit PIDController(char name) : name(name) {};

    void calculateError(const Vec2i &ballPos);

    float getDistanceTo(Vec2i target, Vec2i motor);

    float map(float error, int e_lower, int e_upper, int r_lower, int r_upper);

    void step(const Vec2i &newBallPos);

    void updateSetpoint(const Vec2i &newSetpoint);

    float getPIDAction();

    float getMappedPIDAction();

    void setMotorPos(const Vec2i &newMotorPos);

    void setWeights(float Kp, float Ki, float Kd);

    Vec2i getMotorPos();

    Vec2i getSetpoint();

    float current_error = 0;

    Vec2i center_point = {0, 0};
};


#endif //BALANCER_PIDCONTROLLER_HPP
