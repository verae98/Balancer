//
// Created by florian on 6/1/19.
//

#include "../headers/pidController.hpp"

float PIDController::getDistanceTo(Vec2i target, Vec2i motor) {
    return sqrt(pow(target[0] - motor[0], 2) + pow(target[1] - motor[1], 2));
}

float PIDController::map(float error, int e_lower, int e_upper, int r_lower, int r_upper) {
    return (error - e_lower) * (r_upper - r_lower) / (e_upper - e_lower) +
           r_lower;
}

void PIDController::step(const Vec2i &newBallPos) {
    previous_error = current_error;
    current_error = distance_to_setpoint - getDistanceTo(newBallPos, motor_pos);
    total_error += current_error;
    step_count++;
}

void PIDController::updateSetpoint(const Vec2i &newSetpoint) {
    setpoint = newSetpoint;
    distance_to_setpoint = getDistanceTo(newSetpoint, motor_pos);
}

float PIDController::getPIDAction() {
    return (Kp * current_error) + (Kd * ((current_error - previous_error) / 0.01));
}

float PIDController::getMappedPIDAction() {
    return map(getPIDAction(), -300, 300, 90, 75);
}

void PIDController::setMotorPos(const Vec2i &newMotorPos) {
    motor_pos = newMotorPos;
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



