#include "vex.h"
#include "autonomous.h"
#include <cmath>

void Auton::turnToHeading(int target, int accuracy, int min, int max, int iterations) {
  for(int i = 0; i < iterations; i++) {
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
}

void Auton::turnToHeadingPID(int target) {
  //TODO tune this
  //STOP COPYING MY CODE LANDIN
  const double Kp = 0.29;
  const double Ki = 0.055;
  const double Kd = 0;

  int d;
  int speed;
  double previousError;

  double error = 361;
  double integral;
  double derivative;

  //will be used later
  //int time = vex::timer::system();

  while(error > 1) {
    double heading = Drivetrain.heading();
    
    d = abs(target - heading) % 360;
    error = d > 180 ? 360 - d : d;
    /*
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(heading);
    */
    integral = integral + error;
    derivative = error - previousError;
    previousError = error;

    if (error < 1) {
      integral = 0;
    }

    //fix for the loop integrating while the error is massive causing huge overshoots
    if (error > 5) {
      integral = 0;
    }
    
    speed = Kp*error + Ki*integral + Kd*derivative;

    if((target - heading >= 0 && target - heading <= 180) || (target - heading <=-180 && target - heading >= -360)) {
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
    //will be used later
    /*
    if(error != previousError) {
      time = vex::timer::system();
      
    }
    */
    wait(100, timeUnits::msec);
  }
  Drivetrain.stop();
  //wait for a time then recalculate error to check for overshoot
  wait(100, msec);
  d = abs(target - Drivetrain.heading()) % 360;
  error = d > 180 ? 360 - d : d;
  //if overshoot then recurse otherwise return
  if(error > 1) {
    Auton::turnToHeadingPID(target);
  } else {
    return;
  }
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
  const double Kp = 10;
  const double Ki = 0.3;
  const double Kd = 1;

  int speed;
  double previousError;

  double error = 361;
  double integral;
  double derivative;

  double startHeading = Drivetrain.heading();
  const double skewTolerance = 3;
  

  while(error > 0.1) {
    double avgpos = (
      rightMotorA.position(rotationUnits) +
      rightMotorB.position(rotationUnits) +
      leftMotorA.position(rotationUnits) +
      leftMotorB.position(rotationUnits)
    ) / 4;

    error = target - avgpos;
    double headingDiff = Drivetrain.heading() - startHeading;

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(error);

    integral = integral + error;

    //IF YOU DON'T CHANGE THIS CORRECTLY IT WON'T WORK FOR YOUR BOT
    if (error < 0.2 || avgpos < target) {
      integral = 0;
    }

    
    if (abs(error) > 1) {
      integral = 0;
    }
    
    derivative = error - previousError;
    previousError = error;

    speed = Kp*error + Ki*integral + Kd*derivative;;
    
    //UNDERSTAND HOW THIS WORKS BELOW LANDIN
    if(avgpos < target) {
      //i have brain damage
      //this *should* make the bot correct itself while driving even if the base is skewed using the gyroscope
      //actually the entire autonomous program is hanging on by the gyroscopy
      //god help me
      //this is awful please work
      /*if(fabs(headingDiff) > skewTolerance || fabs(headingDiff) < skewTolerance) {
        rightMotorA.spin(forward, speed + (headingDiff * 0.05), pct);
        rightMotorB.spin(forward, speed + (headingDiff * 0.05), pct);

        leftMotorA.spin(forward, speed - (headingDiff * 0.05), pct);
        leftMotorB.spin(forward, speed - (headingDiff * 0.05), pct);
      } else {*/
        Drivetrain.drive(forward, speed, velocityUnits::pct);
      //}
    } else {
      Drivetrain.drive(reverse, speed, velocityUnits::pct);
    }

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
    amount = target / (2 * M_PI * 1.625);
    break;
    case vex::distanceUnits::mm:
    amount = target / (2 * M_PI * 38.1);
    break;
  }
  drivePID(amount, vex::rotationUnits::rev);
}

void Auton::driveForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  Drivetrain.drive(direction, speed, velocityUnits);
  wait(time, timeUnits);
  Drivetrain.stop();
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