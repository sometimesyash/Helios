#ifndef odometry_h
#define odometry_h

#include "main.h"
#include "api.h"

void kalmanFilter(double x, double y, double z);

class rover{
    public:

        rover(float x, float y,  pros::Motor_Group rMotor, pros::Motor_Group lMotor);

        void setPosition(float x, float y);
        void getPosition();
        void getMap();
        void driveTo(float x, float y, float maxSpeed);
        void activeBreak(double time);
        bool getPID();
        double getLeftMot();
        double getRightMot();
        void moveL(double speed);
        void moveR(double speed);
        double targetL = 0;
        double targetR = 0;
        double errorL = 0;
        double errorR = 0;
        double kP = 0;
        double kI =0;
        double kD = 0;



    private:
       float robotX;
        float robotY;
        pros::Motor_Group rightMotor;
        pros::Motor_Group leftMotor;

};

extern rover heliosRover;


#endif