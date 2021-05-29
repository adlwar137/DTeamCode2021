#include "autonomous.h"

void auton::match::twoTowerRight() {
  Drivetrain.setStopping(brakeType::brake);

  driveFunc::intakeOn();
  Drivetrain.drive(fwd,10,velocityUnits::pct);
  driveFunc::rollerTrainForTime(1.2);
  driveFunc::intakeOff();
  driveFunc::rollerTrainForTime(0.1);
  Drivetrain.stop();

  driveFunc::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 10, distanceUnits::in);
  driveFunc::intakeOff();

  driveFunc::rollerTrainForTime(0.3,reverse);

  driveFunc::turnToHeadingPID(90);
  
  driveFunc::intakeOn(reverse);
  driveFunc::rollerTrainForTime(1);
  driveFunc::intakeOff();

  driveFunc::turnToHeadingPID(-90);
  driveFunc::drivePID(48, vex::distanceUnits::in);

  driveFunc::turnToHeadingPID(-45);

  driveFunc::intakeOn();
  Drivetrain.driveFor(fwd, 20, distanceUnits::in, 50, velocityUnits::pct);
  //Drivetrain.drive(fwd,10,velocityUnits::pct);
  driveFunc::rollerTrainForTime(1.1, forward, seconds, 30);
  driveFunc::intakeOff();
  driveFunc::rollerTrainForTime(0.3,fwd,seconds,50,velocityUnits::pct);
  Drivetrain.stop();

  driveFunc::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 10, distanceUnits::in);
  driveFunc::intakeOff();

}

void auton::match::twoTowerLeft() {

}

void auton::skills::WIP() {
    Drivetrain.setStopping(brakeType::brake);

  //task::sleep(3000);

  //driveFunc::drivePID(-48, vex::distanceUnits::in);

  //doesnt work ever


  //score first ball
  driveFunc::rollerTrainForTime(0.5, forward, seconds, 100, vex::velocityUnits::pct);
  //back up
  driveFunc::rollerTrainOn();
  driveFunc::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 4, vex::distanceUnits::in, 10, vex::velocityUnits::pct);
  driveFunc::intakeOff();
  Drivetrain.driveFor(reverse, 2, vex::distanceUnits::in, 10, vex::velocityUnits::pct);
  driveFunc::rollerTrainOff();
  //turn to ball
  
  driveFunc::turnToHeadingPID(-85);
  //pick up ball

  driveFunc::intakeOn();
  driveFunc::drivePID(49, vex::distanceUnits::in); //yeah i don't know why this changes so often

  //Drivetrain.driveFor(forward, 50, vex::distanceUnits::in, 35, vex::velocityUnits::pct);
  //driveFunc::drivePID(56, distanceUnits::in);
  //turn towards goal
  driveFunc::turnToHeadingPID(315);
  driveFunc::intakeOff();

  //ram goal :)
  driveFunc::driveForTime(2, forward, seconds, 25, velocityUnits::pct);

  //score ball and descore blue ball
  driveFunc::rollerTrainForTime(1.5, forward, seconds, 80);
  //back up from goal
  //start
  driveFunc::intakeOn(reverse);
  driveFunc::drivePID(-50, vex::distanceUnits::in);
  driveFunc::intakeOff();

  wait(1, sec);

  //here
  //spit out blue ball and turn towards wall ball
  //driveFunc::intakeForTime(1, reverse);
  driveFunc::turnToHeadingPID(180);

  driveFunc::intakeOn();

  wait(1, sec);

  driveFunc::drivePID(30, vex::distanceUnits::in);//bending space time. alright!

  //Drivetrain.driveFor(forward, double distance, distanceUnits units)

  driveFunc::turnToHeadingPID(-90);

  driveFunc::drivePID(32, vex::distanceUnits::in, forward, 30, velocityUnits::pct);
  
  /*
  driveFunc::driveForTime(1, forward, seconds, 10, velocityUnits::pct);
  //score one ball
  driveFunc::rollerTrainForTime(0.5, reverse);
  driveFunc::rollerTrainForTime(0.4);
  driveFunc::rollerTrainForTime(0.5, reverse);
  driveFunc::intakeOff();
  
  //back up from goal
  driveFunc::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 12, vex::distanceUnits::in, 15, vex::velocityUnits::pct);
  driveFunc::intakeOff();

  //Turn in the general direction of the goal
  
  driveFunc::turnToHeadingPID(180);
  
  //drive towards goal
  driveFunc::drivePID(46, vex::distanceUnits::in);
  //Drivetrain.driveFor(forward, 48, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
  //turn towards goal
  
  driveFunc::turnToHeadingPID(-135);
  
  //ram goal :)

  driveFunc::driveForTime(1.5, forward, seconds, 20, velocityUnits::pct);
  //score ball
  driveFunc::intakeOn();
  driveFunc::rollerTrainForTime(0.3);
  driveFunc::intakeOff();
  driveFunc::rollerTrainForTime(1.2);
  //back up
  driveFunc::intakeOn(reverse);
  driveFunc::drivePID(-56, vex::distanceUnits::in);
  driveFunc::intakeOff();
  //driveFunc::intakeForTime(1, reverse)

  driveFunc::turnToHeadingPID(90);

  driveFunc::intakeOn();
  driveFunc::drivePID(24, vex::distanceUnits::in);
  //Drivetrain.driveFor(forward, 28, vex::distanceUnits::in, 30, vex::velocityUnits::pct);

  driveFunc::turnToHeadingPID(180);
  driveFunc::intakeOff();

  //driveFunc::intakeOn();
  driveFunc::driveForTime(1.5, forward, seconds, 15, velocityUnits::pct);
  driveFunc::rollerTrainOn();
  driveFunc::driveForTime(0.5, forward, seconds, 15, velocityUnits::pct);
  //driveFunc::rollerTrainOff();
  driveFunc::intakeOff();

  //copy of first stuff


  //score first ball
  driveFunc::rollerTrainForTime(1, forward, seconds, 100, vex::velocityUnits::pct);
  //back up
  Drivetrain.driveFor(reverse, 6, vex::distanceUnits::in, 10, vex::velocityUnits::pct);
  //turn to ball
  driveFunc::turnToHeadingPID(90); //should be 90 but jack said change to 85 // best descision to change this ever thank you jack
  //pick up ball

  driveFunc::intakeOn();
  driveFunc::drivePID(54, vex::distanceUnits::in);
  //turn towards goal
  driveFunc::turnToHeadingPID(135);
  driveFunc::intakeOff();

  //ram goal :)
  driveFunc::driveForTime(1, forward, seconds, 20, velocityUnits::pct);
  //score ball and descore blue ball
  driveFunc::intakeOn();
  driveFunc::rollerTrainForTime(0.3);
  driveFunc::intakeOff();
  driveFunc::rollerTrainForTime(1.7);
  //back up from goal
  Drivetrain.driveFor(reverse, 56, vex::distanceUnits::in, 20, vex::velocityUnits::pct);  //back up from second goal

  driveFunc::turnToHeadingPID(0);

  driveFunc::intakeOn();
  driveFunc::drivePID(20, vex::distanceUnits::in);
  driveFunc::intakeOff();

  driveFunc::turnToHeadingPID(-90);

  driveFunc::intakeOn(reverse);
  driveFunc::driveForTime(1);
  driveFunc::intakeOff();

  driveFunc::rollerTrainForTime(2);
  */
}

//garbage
void auton::match::center() {
  driveFunc::intakeOn();
  driveFunc::rollerTrainOn();
  driveFunc::driveForTime(3);
  driveFunc::rollerTrainOff();
  driveFunc::intakeOff();
}

void auton::match::corner() {
  driveFunc::intakeOn();
  driveFunc::driveForTime(1, forward, seconds, 50, velocityUnits::pct);
  driveFunc::intakeOff();
  driveFunc::rollerTrainForTime(2);
  driveFunc::intakeOn(reverse);
  driveFunc::driveForTime(0.5, reverse, seconds, 50, velocityUnits::pct);
  driveFunc::intakeOff();
}

//sort of working
void auton::match::right() {
  driveFunc::rollerTrainOn();
  driveFunc::driveForTime(0.5, fwd, seconds, 20, velocityUnits::pct);
  driveFunc::rollerTrainOff();
  Drivetrain.driveFor(reverse, 10, vex::distanceUnits::in, 10, vex::velocityUnits::pct);
  driveFunc::turnToHeadingPID(270);
  Drivetrain.driveFor(forward, 54, vex::distanceUnits::in, 20, vex::velocityUnits::pct);
  driveFunc::turnToHeadingPID(315);
  driveFunc::intakeOn();
  driveFunc::driveForTime(1, forward, seconds, 20, velocityUnits::pct);
  driveFunc::intakeOff();
  driveFunc::driveForTime(1, forward, seconds, 20, velocityUnits::pct);
  driveFunc::rollerTrainForTime(2);
  driveFunc::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 20, vex::distanceUnits::in, 30, vex::velocityUnits::pct);
}

//not updated whatsoever
void auton::match::left() {
  driveFunc::rollerTrainForTime(2, forward, seconds, 80, vex::velocityUnits::pct);
  Drivetrain.driveFor(reverse, 18, vex::distanceUnits::cm, 15, vex::velocityUnits::pct);
  driveFunc::turnToHeadingPID(90);
  Drivetrain.driveFor(forward, 39, vex::distanceUnits::cm, 15, vex::velocityUnits::pct);
  driveFunc::turnToHeadingPID(45);
  driveFunc::intakeOn();
  driveFunc::driveForTime(2, forward, seconds, 20, velocityUnits::pct);
  driveFunc::intakeOff();
  driveFunc::rollerTrainForTime(2);
  driveFunc::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 20, vex::distanceUnits::cm, 30, vex::velocityUnits::pct);
  driveFunc::intakeOff();
}
