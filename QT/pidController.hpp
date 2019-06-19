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
    /**
     * Hardcoded to the center of the image to prevent an error buildup from {0,0}
     */
    Vec2i ball_pos = {281, 246};
    float Kp = 0.2;
    float Kd = 0;
    float Ki = 0.04;
    char name;

public:
    explicit PIDController(char name) : name(name) {};

    /**
     * Calculate the error for this motor.
     * @param ballPos
     */
    void calculateError(const Vec2i &ballPos);

    /**
     * Helper method to get the distance between two coordinates
     * @param target
     * @param motor
     * @return
     */
    float getDistanceTo(Vec2i target, Vec2i motor);

    /**
     * Map a given value, within a given range, to another range.
     * @param error
     * @param e_lower lower bound of input
     * @param e_upper upper bound of input
     * @param r_lower lower bound of output
     * @param r_upper upper bound of output
     * @return
     */
    float map(float error, int e_lower, int e_upper, int r_lower, int r_upper);

    /**
     * Calculate the error, and update all the necessary fields.
     * @param newBallPos
     */
    void step(const Vec2i &newBallPos);

    /**
     * Helper to update the setpoint
     * @details resets the error, total_error and recalculates the distance from the motor to the setpoint
     * @param newSetpoint
     */
    void updateSetpoint(const Vec2i &newSetpoint);

    /**
     * Get the PID value based on the current error.
     * @return
     */
    float getPIDAction();

    /**
     * Get the value of PID as an angle that the servo has to move to.
     * @return
     */
    float getMappedPIDAction();

    /**
     * Helper to upadte the motor position
     * @details also recalculates the distance between the motor and the setpoint
     * @param newMotorPos
     */
    void setMotorPos(const Vec2i &newMotorPos);

    /**
     * Update the P, I and D weights for the PID calculation
     * @param Kp
     * @param Ki
     * @param Kd
     */
    void setWeights(float Kp, float Ki, float Kd);

    /**
     * Helper to get the motor position
     * @return
     */
    Vec2i getMotorPos();

    /**
     * Helper to get the setpoint configured for the motor
     * @return
     */
    Vec2i getSetpoint();

    /**
     * Store the current_error
     */
    float current_error = 0;

    /**
     * Store the current setpoint
     */
    Vec2i center_point = {0, 0};
};


#endif //BALANCER_PIDCONTROLLER_HPP
