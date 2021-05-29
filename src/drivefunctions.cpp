#include "drivefunctions.h"
#include "vex.h"
#include <cmath>


void driveFunc::turnToHeading(int target, int accuracy, int min, int max, int iterations) {
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

void driveFunc::turnToHeadingPID(int target, bool visionAdjust, vex::vision::signature signature) {
  //TODO tune this
  const double Kp = 0.3;
  const double Ki = 0.06;
  //sensitive to noise BE CAREFUL
  //hopefully predictive enough to reduce the massive overshoots while maintaining decent speed
  //god help me
  const double Kd = 0.1;

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
    driveFunc::turnToHeadingPID(target, visionAdjust);
  } else {
    return;
  }

  if(visionAdjust){
    const double Ki = 0.01;
    const int MaxVisionWidth = 315;

    double error = 2;
    double previousError = 0;

    while(error > 1) {

      Vision17.takeSnapshot(signature);
    
      vex::vision::object GOAL = Vision17.largestObject;

      error = GOAL.centerX - (MaxVisionWidth/2);

      integral = error + previousError;

      speed = integral*Ki;

      previousError = error;

      Drivetrain.turn(turnType::right, speed, velocityUnits::pct);
    }
  }
}

void driveFunc::turnByPID(int target) {
  turnToHeadingPID(target + Drivetrain.heading());
}

void driveFunc::drivePID(double target, vex::rotationUnits rotationUnits, vex::directionType direction, double maxspeed, vex::velocityUnits velocityUnits) {
  rightMotorA.resetPosition();
  rightMotorB.resetPosition();
  leftMotorA.resetPosition();
  leftMotorB.resetPosition();

  //maybe i should somehow make a function to do all the pid math
  //it would really streamline this if i knew c++


  //TODO tune this
  //Drive PID variables
  const double Kp = 10; //was 10
  const double Ki = 0.5; //was 0.5
  const double Kd = 1; //was 1

  int speed;
  double previousError;

  double error = 361;
  double integral;
  double derivative;


  //turn pid variables for keeping it straight while turning
  double startHeading = Drivetrain.heading();
  
  const double TKp = 0.5; //was 0.5
  const double TKi = 0;
  const double TKd = 0;

  double turn = 0;
  double TpreviousError;
  int d;

  double Terror = 1;
  double Tintegral;
  double Tderivative;

  //main pid loop
  while(abs(error) > 0.1) {

    double avgpos = (
      rightMotorA.position(rotationUnits) +
      rightMotorB.position(rotationUnits) +
      leftMotorA.position(rotationUnits) +
      leftMotorB.position(rotationUnits)
    ) / 4;

    //calculate error for both drive and turn
    error = target - avgpos;
    double headingDiff = Drivetrain.heading() - startHeading;


    //drive pid math
    integral = integral + error;
    derivative = error - previousError;
    previousError = error;
    //turn pid math
    Tintegral = Tintegral + Terror;
    Tderivative = Terror - TpreviousError;
    TpreviousError = Terror;

    //not sure this does anything important
    /*
    if (error < 0.1 || avgpos < target) {
      integral = 0;
    }
    */

    //anti windup drive
    if (abs(error) > 1) {
      integral = 0;
    }

    //anti windup turn
    if(abs(Terror) > 1) {
      Tintegral = 0;
    }

    //disable turning
    if(abs(Terror) < 0.2) {
      Tintegral = 0;
    }
    
    speed = Kp*error + Ki*integral + Kd*derivative;
    //turn = TKp*Terror + TKi*Tintegral + Kd*Tderivative;

    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1, 1);
    Controller1.Screen.print(speed);
    

    //yeah fuck it im just gonna clamp it
    //no clever solution today
    if(speed > maxspeed) {
      speed = maxspeed;
    }


    
    //gotta use pid 2 electric boogaloo
    if(avgpos < target) {
      //i hate the double pid solution so much
      leftMotorA.spin(forward, speed + turn, velocityUnits::pct);
      leftMotorB.spin(forward, speed + turn, velocityUnits::pct);

      rightMotorA.spin(forward, speed - turn, velocityUnits::pct);
      rightMotorB.spin(forward, speed - turn, velocityUnits::pct);
    } else {
      //TODO
      //think about how the robot moves in reverse and make this work with turn pid
      //mind too jello to think
      leftMotorA.spin(forward, speed + turn, velocityUnits::pct);
      leftMotorB.spin(forward, speed + turn, velocityUnits::pct);

      rightMotorA.spin(forward, speed - turn, velocityUnits::pct);
      rightMotorB.spin(forward, speed - turn, velocityUnits::pct);
    }
    
    wait(20, timeUnits::msec);
  }
  Drivetrain.stop();
}

void driveFunc::drivePID(double target, vex::distanceUnits distance, vex::directionType direction, double maxspeed, vex::velocityUnits velocityUnits) {
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
  drivePID(amount, vex::rotationUnits::rev, direction, maxspeed, velocityUnits);
}

void driveFunc::driveForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  Drivetrain.drive(direction, speed, velocityUnits);
  wait(time, timeUnits);
  Drivetrain.stop();
}

void driveFunc::setAllBrake(vex::brakeType brakeType) {
  rightMotorA.setBrake(brakeType);
  rightMotorB.setBrake(brakeType);
  leftMotorA.setBrake(brakeType);
  leftMotorB.setBrake(brakeType);
}

void driveFunc::rollerTrainOn(vex::directionType direction, double speed, vex::velocityUnits velocityUnits) {
  TrainT.spin(direction, speed, velocityUnits);
  TrainB.spin(direction, speed, velocityUnits);
}

void driveFunc::rollerTrainOff() {
  TrainT.stop();
  TrainB.stop();
}

void driveFunc::rollerTrain(double distance, vex::directionType direction, vex::rotationUnits rotationUnits, double speed, vex::velocityUnits velocityUnits) {
  TrainT.startRotateFor(direction, distance, rotationUnits, speed, velocityUnits);
  TrainB.rotateFor(direction, distance, rotationUnits, speed, velocityUnits);
}

void driveFunc::rollerTrainForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  TrainT.spin(direction, speed, velocityUnits);
  TrainB.spinFor(direction, time, timeUnits, speed, velocityUnits);
  TrainT.stop();
  TrainB.stop();
}

void driveFunc::intakeOn(vex::directionType direction, double speed, vex::velocityUnits velocityUnits) {
  IntakeL.spin(direction, speed, velocityUnits);
  IntakeR.spin(direction, speed, velocityUnits);
}

void driveFunc::intakeOff() {
  IntakeL.stop();
  IntakeR.stop();
}

void driveFunc::intakeForTime(double time, vex::directionType direction, vex::timeUnits timeUnits, double speed, vex::velocityUnits velocityUnits) {
  IntakeL.spin(direction, speed, velocityUnits);
  IntakeR.spinFor(direction, time, timeUnits, speed, velocityUnits);
  IntakeL.stop();
  IntakeR.stop();
}
