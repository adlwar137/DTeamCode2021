#include "vex.h"
#include "autonomous.h"

double turnAmount = 1.65;

void Auton::setup() {
  Auton::rollerTrain(2, reverse);
  Drivetrain.driveFor(reverse, 5, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
  Drivetrain.driveFor(forward, 5, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
}

void Auton::turnToHeading(double target, double accuracy) {
  double Kp = 0.01;
  double Ki = 0.05;
  double Kd = 0.025;

  double error = 0;
  double lastError = 0;

  double integral = 0;
  double derivative = 0;

  double power = 0;

  while(!(Drivetrain.heading() >= target + accuracy && Drivetrain.heading() <= target + accuracy)) {
    error = target - Drivetrain.heading();
    integral = integral + error;
    derivative = error - lastError;

    power = (error * Kp) + (integral * Ki) + (derivative * Kd);

    if(Drivetrain.heading() > target) {
      //if need to turn left
      rightMotorA.spin(forward, power, percentUnits::pct);
      rightMotorB.spin(forward, power, percentUnits::pct);
      leftMotorA.spin(forward, power, percentUnits::pct);
      leftMotorB.spin(forward, power, percentUnits::pct);
    } else {
      //if need to turn right
      rightMotorA.spin(reverse, power, percentUnits::pct);
      rightMotorB.spin(reverse, power, percentUnits::pct);
      leftMotorA.spin(forward, power, percentUnits::pct);
      leftMotorB.spin(forward, power, percentUnits::pct);
    }

    lastError = error;
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