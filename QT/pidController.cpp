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

double PIDController::getAngle(Vec2i origin, Vec2i pointA, Vec2i pointB) {
    Vec2i subA(abs(origin[0] - pointA[0]), abs(origin[1] - pointA[1]));
    Vec2i subB(abs(origin[0] - pointB[0]), abs(origin[1] - pointB[1]));
    return acos(
            ((subA[0] * subB[0]) + (subA[1] * subB[1]))
            /
            (sqrt((subA[0] * subA[0]) + (subA[1] * subA[1])) * sqrt((subB[0] * subB[0]) + (subB[1] * subB[1])))
    );
}

Vec2i PIDController::getRotatedCoordinates(const Vec2i &origin, Vec2i point, float angle) {
    Vec2i newPoint = point - origin;
    newPoint[0] = (cos(angle) * point[0]) + (sin(angle) * point[1]);
    newPoint[1] = (-sin(angle) * point[0]) + (cos(angle) * point[1]);
    return newPoint;
}

float PIDController::getVectorLength(const Vec2i &vector) {
    return sqrt(pow(vector[0], 2) + pow(vector[1], 2));
}

Vec2i PIDController::toUnitVector(const Vec2i &vector) {
    return vector / getVectorLength(vector);
}


void PIDController::calculateError(const Vec2i &ballPos) {
    auto zero = center_point;
    auto motor = motor_pos;
    auto ball = ballPos;

    Vec2f BallOnLine;

    float k = (
            ((motor[1] - zero[1]) * (ball[0] - zero[0]) - (motor[0] - zero[0]) * (ball[1] - zero[1]))
            /
            (pow(motor[1] - zero[1], 2) + pow(motor[0] - zero[0], 2))
    );

    BallOnLine[0] = ball[0] - (k * (motor[1] - zero[1])); //This is the projected point on the line that goes between the motor and the center of the 3 motors.
    BallOnLine[1] = ball[1] + (k * (motor[0] - zero[0])); //This is the projected point on the line that goes between the motor and the center of the 3 motors.

    Vec2f SetpointOnLine;
    float l = (
            (((motor[1] - zero[1]) * (setpoint[0] - zero[0])) - ((motor[0] - zero[0]) * (setpoint[1] - zero[1])))
            /
            (pow(motor[1] - zero[1], 2) + pow(motor[0] - zero[0], 2))
    );

    SetpointOnLine[0] = setpoint[0] - (l * (motor[1] - zero[1]));
    SetpointOnLine[1] = setpoint[1] + (l * (motor[0] - zero[0]));

    float distanceSetpointCenter = getDistanceTo(center_point, SetpointOnLine);
    float distanceBallCenter = getDistanceTo(center_point, BallOnLine);

    current_error = distanceSetpointCenter - distanceBallCenter + (getDistanceTo(ballPos, BallOnLine) / 4 );


}

void PIDController::step(const Vec2i &newBallPos) {
    previous_error = current_error;
    calculateError(newBallPos);
//    current_error = distance_to_setpoint - getDistanceTo(newBallPos, motor_pos);
    total_error += current_error;
    step_count++;
}

void PIDController::updateSetpoint(const Vec2i &newSetpoint) {
    setpoint = newSetpoint;
    distance_to_setpoint = getDistanceTo(newSetpoint, motor_pos);
}

float PIDController::getPIDAction() {
    return ((Kp / 1000) * current_error) + ((Kd / 1000) * ((current_error - previous_error) / 0.05)) +
           ((Ki / 1000) * (total_error * 0.005));
}

float PIDController::getMappedPIDAction() {
    float temp;

    if (name != 'A') {
        temp = map(getPIDAction(), 150, -150, 90, 130);
    } else {
        temp = map(getPIDAction(), -150, 150, 90, 130);
    }

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



