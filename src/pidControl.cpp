#include "odometry.h"

void pidRun(void* ignore){

    double previousErrorL = 0;
    double previousErrorR = 0;

    while(heliosRover.getPID()){

    double leftAvg = heliosRover.getLeftMot();
    double rightAvg = heliosRover.getRightMot();


    double errorL = heliosRover.targetL - leftAvg;
    double errorR = heliosRover.targetR - rightAvg;

    double deltaErrorL = heliosRover.errorL - previousErrorL;
    double deltaErrorR = heliosRover.errorR - previousErrorR;

    double motorTargetL = heliosRover.kP * errorL + heliosRover.kD * deltaErrorL;
    double motorTargetR = heliosRover.kP * errorR + heliosRover.kD * deltaErrorR;

    heliosRover.moveL(motorTargetL);
    heliosRover.moveR(motorTargetR);


    previousErrorL = errorL;
    previousErrorR = errorR;

    pros::delay(20);
  }

}
