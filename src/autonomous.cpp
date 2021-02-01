#include "vex.h"
#include "autonomous.h"
#include <cmath>

double turnAmount = 1.50;

//do something else with this
void Auton::setup() {
  Auton::rollerTrain(2, reverse);
  Drivetrain.driveFor(reverse, 5, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
  Drivetrain.driveFor(forward, 5, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
}

void Auton::turnToHeading(int target, int accuracy, int min, int max) {
  double diff = 10000000; //big number
  int d; 

  double power = 0;

  while(diff > accuracy) {
    
    d = abs(target - Drivetrain.heading()) % 360;
    diff = d > 180 ? 360 - d : d;

    power = diff / 180 * max + min;

    //clamp power
    if(power > max) {
      power = max;
    }

    if(target - diff < 0) {
      //if need to turn left
      rightMotorA.spin(forward, power, percentUnits::pct);
      rightMotorB.spin(forward, power, percentUnits::pct);
      leftMotorA.spin(reverse, power, percentUnits::pct);
      leftMotorB.spin(reverse, power, percentUnits::pct);
    } else {
      //if need to turn right
      rightMotorA.spin(reverse, power, percentUnits::pct);
      rightMotorB.spin(reverse, power, percentUnits::pct);
      leftMotorA.spin(forward, power, percentUnits::pct);
      leftMotorB.spin(forward, power, percentUnits::pct);
    }
  }
  Drivetrain.stop();
}

void Auton::driveForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  rightMotorA.spin(direction, speed, velocityUnits);
  rightMotorB.spin(direction, speed, velocityUnits);
  leftMotorA.spin(direction, speed, velocityUnits);
  leftMotorB.spinFor(direction, time, timeUnits, speed, velocityUnits);
  rightMotorA.stop();
  rightMotorB.stop();
  leftMotorA.stop();
  leftMotorB.stop();
}

void Auton::setAllBrake(vex::brakeType brakeType) {
  rightMotorA.setBrake(brakeType);
  rightMotorB.setBrake(brakeType);
  leftMotorA.setBrake(brakeType);
  leftMotorB.setBrake(brakeType);
}

void Auton::rollerTrainOn(vex::directionType direction, double speed, vex::velocityUnits velocityUnits) {
  TrainT.spin(direction, speed, velocityUnits);
  TrainB.spin(direction, speed, velocityUnits);
}

void Auton::rollerTrainOff() {
  TrainT.stop();
  TrainB.stop();
}

void Auton::rollerTrain(double distance, vex::directionType direction, vex::rotationUnits rotationUnits, double speed, vex::velocityUnits velocityUnits) {
  TrainT.startRotateFor(direction, distance, rotationUnits, speed, velocityUnits);
  TrainB.rotateFor(direction, distance, rotationUnits, speed, velocityUnits);
}

void Auton::rollerTrainForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  TrainT.spin(direction, speed, velocityUnits);
  TrainB.spinFor(direction, time, timeUnits, speed, velocityUnits);
  TrainT.stop();
  TrainB.stop();
}

void Auton::intakeOn(vex::directionType direction, double speed, vex::velocityUnits velocityUnits) {
  IntakeL.spin(direction, speed, velocityUnits);
  IntakeR.spin(direction, speed, velocityUnits);
}

void Auton::intakeOff() {
  IntakeL.stop();
  IntakeR.stop();
}

void Auton::intakeForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  IntakeL.spin(direction, speed, velocityUnits);
  IntakeR.spinFor(direction, time, timeUnits, speed, velocityUnits);
  IntakeL.stop();
  IntakeR.stop();
}

void Auton::rotate(double amount, vex::rotationUnits rotationUnits, vex::turnType turnType, double speed, vex::velocityUnits velocityUnits) {
  if(turnType == vex::turnType::right) {
    rightMotorA.startRotateFor(reverse, amount * turnAmount, rotationUnits, speed, velocityUnits);
    rightMotorB.startRotateFor(reverse, amount * turnAmount, rotationUnits, speed, velocityUnits);
    leftMotorA.startRotateFor(forward, amount * turnAmount, rotationUnits, speed, velocityUnits);
    leftMotorB.rotateFor(forward, amount * turnAmount, rotationUnits, speed, velocityUnits);
  } else {
    rightMotorA.startRotateFor(forward, amount * turnAmount, rotationUnits, speed, velocityUnits);
    rightMotorB.startRotateFor(forward, amount * turnAmount, rotationUnits, speed, velocityUnits);
    leftMotorA.startRotateFor(reverse, amount * turnAmount, rotationUnits, speed, velocityUnits);
    leftMotorB.rotateFor(reverse, amount * turnAmount, rotationUnits, speed, velocityUnits);
  }
}
