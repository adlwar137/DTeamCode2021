#include "vex.h"
#include "autonomous.h"
#include <cmath>

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

    if((target - Drivetrain.heading() >= 0 && target - Drivetrain.heading() <= 180) || (target - Drivetrain.heading() <=-180 && target - Drivetrain.heading() >= -360)) {
      //if need to turn right
      rightMotorA.spin(reverse, power, percentUnits::pct);
      rightMotorB.spin(reverse, power, percentUnits::pct);
      leftMotorA.spin(forward, power, percentUnits::pct);
      leftMotorB.spin(forward, power, percentUnits::pct);
    } else {
      //if need to turn left
      rightMotorA.spin(forward, power, percentUnits::pct);
      rightMotorB.spin(forward, power, percentUnits::pct);
      leftMotorA.spin(reverse, power, percentUnits::pct);
      leftMotorB.spin(reverse, power, percentUnits::pct);
      
    }
    wait(20, timeUnits::msec);
  }
  Drivetrain.stop();
}

void Auton::turnToHeadingPID(int target) {
  //TODO tune this
  const double Kp = 0.25;
  const double Ki = 0.00002;
  const double Kd = 0.21;

  int d;
  int speed;
  double previousError;

  double error = 361;
  double integral;
  double derivative;

  while(error != 0) {
    d = abs(target - Drivetrain.heading()) % 360;
    error = d > 180 ? 360 - d : d;

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(error);

    integral = integral + error;

    if (error < 1) {
      integral = 0;
    }

    /*
    if (abs(error) > 100) {
      integral = 0;
    }
    */
    derivative = error - previousError;
    previousError = error;

    speed = Kp*error + Ki*integral + Kd*derivative;;
    

    if((target - Drivetrain.heading() >= 0 && target - Drivetrain.heading() <= 180) || (target - Drivetrain.heading() <=-180 && target - Drivetrain.heading() >= -360)) {
      //if need to turn right
      rightMotorA.spin(reverse, speed, percentUnits::pct);
      rightMotorB.spin(reverse, speed, percentUnits::pct);
      leftMotorA.spin(forward, speed, percentUnits::pct);
      leftMotorB.spin(forward, speed, percentUnits::pct);
    } else {
      //if need to turn left
      rightMotorA.spin(forward, speed, percentUnits::pct);
      rightMotorB.spin(forward, speed, percentUnits::pct);
      leftMotorA.spin(reverse, speed, percentUnits::pct);
      leftMotorB.spin(reverse, speed, percentUnits::pct);
      
    }
    wait(20, timeUnits::msec);
  }
  Drivetrain.stop();
}

void Auton::turnByPID(int target) {
  turnToHeadingPID(target + Drivetrain.heading());
}

void Auton::drivePID(double target, vex::rotationUnits rotationUnits) {
  rightMotorA.resetPosition();
  rightMotorB.resetPosition();
  leftMotorA.resetPosition();
  leftMotorB.resetPosition();

  //TODO tune this
  const double Kp = 1;
  const double Ki = 0;
  const double Kd = 0;

  int speed;
  double previousError;

  double error = 361;
  double integral;
  double derivative;

  while(error > 1) {
    error = target - (
      rightMotorA.position(rotationUnits) +
      rightMotorB.position(rotationUnits) +
      leftMotorA.position(rotationUnits) +
      leftMotorB.position(rotationUnits)
    ) / 4;

    integral = integral + error;

    if (error < 1) {
      integral = 0;
    }

    /*
    if (abs(error) > 100) {
      integral = 0;
    }
    */
    derivative = error - previousError;
    previousError = error;

    speed = Kp*error + Ki*integral + Kd*derivative;;
    
    rightMotorA.spin(forward, speed, percentUnits::pct);
    rightMotorB.spin(forward, speed, percentUnits::pct);
    leftMotorA.spin(forward, speed, percentUnits::pct);
    leftMotorB.spin(forward, speed, percentUnits::pct);

    wait(20, timeUnits::msec);
  }
  Drivetrain.stop();
}

void Auton::drivePID(double target, vex::distanceUnits distance) {
  double amount;
  //convert distance to revolutions
  switch(distance){
    case vex::distanceUnits::cm:
    amount = target / (2 * M_PI * 3.81);
    break;
    case vex::distanceUnits::in:
    amount = target / (2 * M_PI * 1.5);
    break;
    case vex::distanceUnits::mm:
    amount = target / (2 * M_PI * 38.1);
    break;
  }
  drivePID(amount, vex::rotationUnits::rev);
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