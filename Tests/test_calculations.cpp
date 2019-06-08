#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

float getDistanceTo(const vector<float> &target, const vector<float> & motor) {
    return sqrt(pow(target[0] - motor[0], 2) + pow(target[1] - motor[1], 2));
}


int main()
{   
    vector<float> center_point = {20,20};
    vector<float> motor_pos = {40,50};
    vector<float> ballPos = {70, 80};
    vector<float> setpoint = {50, 50};
    
    auto zero = center_point;
    auto motor = motor_pos;
    auto ball = ballPos;
    auto set_point = setpoint;

    vector<float> BallOnLine = {0,0};

    ball[0] = ball[0] - zero[0];
    ball[1] = ball[1] - zero[1];

    motor[0] = motor[0] - zero[0];
    motor[1] = motor[1] - zero[1];

    set_point[0] = set_point[0] - zero[0];
    set_point[1] = set_point[1] - zero[1];
    
    //cout << ball[0] << " " << ball[1] << " " << motor[0] << " " << motor[1];
    float ballOnMotorK= 
            ( ball[0]*motor[0] + ball[1] * motor[1] ) / (pow(motor[0], 2) + pow(motor[1], 2) ) ;
    cout << ballOnMotorK << "\n";
    BallOnLine[0] = (ballOnMotorK * (motor[0])); //This is the projected point on the line that goes between the motor and the center of the 3 motors.
    BallOnLine[1] = (ballOnMotorK * (motor[1])); //This is the projected point on the line that goes between the motor and the center of the 3 motors.


    vector<float> SetpointOnLine = {0,0};
     float setpointOnMotorK= 
            ( set_point[0]*motor[0] + set_point[1] * motor[1] ) / (pow(motor[0], 2) + pow(motor[1], 2));

    SetpointOnLine[0] = setpointOnMotorK * (motor[0]);
    SetpointOnLine[1] = setpointOnMotorK * (motor[1]);

    float distanceSetpointCenter = getDistanceTo(motor, SetpointOnLine);
    float distanceBallCenter = getDistanceTo(motor, BallOnLine);

    float current_error = distanceSetpointCenter - distanceBallCenter;
    //cout << "BallOnLine[0]: "<< BallOnLine[0] << "\n BallOnLine[1]" << BallOnLine[1] << "\n";
    //cout << "setpoint [0]: "<< SetpointOnLine[0] << "\n SetpointOnLine[1]" << SetpointOnLine[1] << "\n";
    cout << "current_error: " << current_error;
    
}
