#include "odometry.h"

float xPos = 0;
float yPos = 0;
float zPos = 0;
pros::Motor l1(1);
pros::Motor l2(2);
pros::Motor r1(3);
pros::Motor r2(4);

pros::Motor_Group lMo({l1, l2});
pros::Motor_Group rMo({r1, r2});

class rover{
    public:

        rover(float x, float y,  pros::Motor_Group rMotor, pros::Motor_Group lMotor) : rightMotor(rMotor), leftMotor(lMotor));
        

        void setPosition(float x, float y){
            robotX = x;
            robotY = y;
        }
        void getPositionX(){
            return robotX;
        }
        void getPositionY(){
            return robotY;
        }
        void getMap();
        void setPid(bool cur){
            runPID = cur;
        }
        void driveTo(float dist, float maxSpeed){
            target = dist;
            
        }
        void activeBreak(double time){
            target = 0;
            runPid = true;
            pros::delay(time);
            runPid = false;   

        }
        bool getPID(){
            return runPid;
        }
        double getLeftMot(){
            return leftMotor.get_position();

        }
        double getRightMot(){
            return rightMotor.get_position();

        }

        void moveL(double speed){
            leftMotor.move(speed);
        }
        void moveR(double speed){
            rightMotor.move(speed);
        }

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
        bool runPID = false;
        

};


rover heliosRover(xPos, yPos, rMo, lMo);

void odomDrive (void * ignore){
  pros::IMU imuPM (1);
  pros::ADIEncoder leftEncode(1, 3);
  pros::ADIEncoder rightEncode(5,7);
  double encodL;
  double encodR;

  while(true){
    if(imuPM.is_calibrating()){
      heliosRover.setPosition(0, 0);
    } else {
      double angle = imuPM.get_heading();
      double changeL = leftEncode.get_value() - encodL;
      double changeR = rightEncode.get_value() - encodR;
      double avgCh = (changeL+changeR)/2;
      encodL = leftEncode.get_value();
      encodR = rightEncode.get_value();

      xPos += avgCh * cos(angle);
      yPos += avgCh * sin(angle);

      pros::delay(5);
    }
  }

}


