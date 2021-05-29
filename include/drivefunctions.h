#include "vex.h"

namespace driveFunc { 

    //Wierd P loop amalgamation if the functions below this one work then don't use this one
    void turnToHeading(int target, int accuracy, int min, int max, int interations);

    //turn using a pid loop (takes degrees based on absolute Heading)
    void turnToHeadingPID(int target, bool visionAdjust = false, vex::vision::signature signature = Vision17__R3D);

    //same thing as above but this one is relative to the current position (only use if you have to)
    void turnByPID(int target);

    //drive rotationUnits
    void drivePID(double target, vex::rotationUnits rotationUnits, vex::directionType direction = vex::directionType::fwd, double maxspeed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);

    //drive distanceUnits
    void drivePID(double target, vex::distanceUnits distance, vex::directionType direction = vex::directionType::fwd, double maxspeed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);

    //my own drivetrain code for driving for a time because there's none currently (overrides below)
    void driveForTime(double time, vex::directionType direction = vex::directionType::fwd, vex::timeUnits timeUnits = vex::timeUnits::sec, double speed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);

    //set brake Type for all wheels
    void setAllBrake(vex::brakeType brakeType);

    //turn on the roller train so blocking code can determin when it turns off
    void rollerTrainOn(vex::directionType direction = vex::directionType::fwd, double speed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);

    //turn roller train off after blocking code is complete
    void rollerTrainOff();

    //spin the whole roller train
    void rollerTrain(double distance, vex::directionType direction = vex::directionType::fwd, vex::rotationUnits rotationUnits = vex::rotationUnits::rev, double speed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);

    //spin the whole roller train for a time instead of encoder values
    void rollerTrainForTime(double time, vex::directionType direction = vex::directionType::fwd, vex::timeUnits timeUnits = vex::timeUnits::sec, double speed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);

    //turns on the intake
    void intakeOn(vex::directionType direction = vex::directionType::fwd, double speed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);
    //turns off the intake
    void intakeOff();

    void intakeForTime(double time, vex::directionType direction = vex::directionType::fwd, vex::timeUnits timeUnits = vex::timeUnits::sec, double speed = 100, vex::velocityUnits velocityUnits = vex::velocityUnits::pct);
}


