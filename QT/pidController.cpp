//
// Created by florian on 6/1/19.
//

#include "pidController.hpp"

float PIDController::getDistanceTo(Vec2i target, Vec2i motor) {
    return sqrt(pow(target[0] - motor[0], 2) + pow(target[1] - motor[1], 2));
}

float PIDController::map(float error, int e_lower, int e_upper, int r_lower, int r_upper) {
    return (error - e_lower) * (r_upper - r_lower) / (e_upper - e_lower) +
           r_lower;
}

void PIDController::calculateError(const Vec2i &ballPos) {
    auto zero = center_point;
    auto motor = motor_pos;
    auto ball = ballPos;
    auto set_point = setpoint;

    Vec2f BallOnLine;
    ball[0] = ball[0] - zero[0];
    ball[1] = ball[1] - zero[1];
    motor[0] = motor[0] - zero[0];
    motor[1] = motor[1] - zero[1];
    set_point[0] = set_point[0] - zero[0];
    set_point[1] = set_point[1] - zero[1];
    float ballOnMotorK= (
            ( ball[0]*motor[0] + ball[1] * motor[1] ) / (pow(motor[0], 2) + pow(motor[1], 2))
    );
    BallOnLine[0] = (ballOnMotorK * (motor[0])); //This is the projected point on the line that goes between the motor and the center of the 3 motors.
    BallOnLine[1] = (ballOnMotorK * (motor[1])); //This is the projected point on the line that goes between the motor and the center of the 3 motors.
    Vec2f SetpointOnLine;
     float setpointOnMotorK= (
            ( set_point[0]*motor[0] + set_point[1] * motor[1] ) / (pow(motor[0], 2) + pow(motor[1], 2))
    );
    SetpointOnLine[0] = setpointOnMotorK * (motor[0]);
    SetpointOnLine[1] = setpointOnMotorK * (motor[1]);
    float distanceSetpointCenter = getDistanceTo(motor, SetpointOnLine);
    float distanceBallCenter = getDistanceTo(motor, BallOnLine);
    current_error = distanceSetpointCenter - distanceBallCenter;
    //if(current_error > 0 && current_error < 20){current_error = 0;}
    //if(current_error < 0 && current_error > -20){current_error = 0;}
}

void PIDController::step(const Vec2i &newBallPos) {
    previous_error = current_error;
    calculateError(newBallPos);
    total_error += current_error;
    step_count++;
}

void PIDController::updateSetpoint(const Vec2i &newSetpoint) {
    total_error = 0;
    previous_error = 0;
    setpoint = newSetpoint;
    distance_to_setpoint = getDistanceTo(newSetpoint, motor_pos);
}

float PIDController::getPIDAction() {
    return ((Kp / 1000) * current_error) + ((Kd / 1000) * ((current_error - previous_error) / 0.05)) +
           ((Ki / 1000) * (total_error * 0.005));
}

float PIDController::getMappedPIDAction() {
    float temp = map(getPIDAction(), -150, 150, 90, 130);
    if (temp < 90) {
        temp = 90;
    } else if (temp > 130) {
        temp = 130;
    }
    return temp;
}

void PIDController::setMotorPos(const Vec2i &newMotorPos) {
    motor_pos = newMotorPos;
    distance_to_setpoint = getDistanceTo(setpoint, motor_pos);
}

void PIDController::setWeights(float Kp, float Ki, float Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
}

Vec2i PIDController::getMotorPos() {
    return motor_pos;
}

Vec2i PIDController::getSetpoint() {
    return setpoint;
}



