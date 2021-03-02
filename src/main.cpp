/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Vision17             vision        16              
// Controller1          controller                    
// TrainT               motor         5               
// TrainB               motor         6               
// IntakeR              motor         11              
// IntakeL              motor         12              
// Drivetrain           drivetrain    2, 4, 1, 3, 18  
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "drawing.h"
#include "autonomous.h"
#include <map>

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here



bool tank = true;

enum AutonSelect {RedRight, RedLeft, BlueRight, BlueLeft, None};

std::map<AutonSelect, std::string> AutonSelectMap { {RedRight, "RedRight"}, {RedLeft, "RedLeft"}, {BlueRight, "BlueRight"}, {BlueLeft, "BlueLeft"}, {None, "None"}};

enum TrainMode {manual, automatic};
AutonSelect selectedAuton = None;
TrainMode cameraToggle = manual;

const int maxHeight = 240;
const int maxWidth = 480;

//Various Functions
void swapTank() {
  tank = !tank;
}

void swapTrain() {
  if (cameraToggle == manual) {
    cameraToggle = automatic;
  } else {
    cameraToggle = manual;
  }
}

void stopDrive() {
  Drivetrain.stop();
}

drawing::Button* Right;
drawing::Button* Left;

void RightButton() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("you selected Right!");
  selectedAuton = BlueRight;
  delete Right;
  delete Left;
}
void LeftButton() {
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("you pressed Left!");
  selectedAuton = BlueLeft;
  delete Left;
  delete Right;
}
void Bluescreen() {

}

void click() {
  //check if any buttons have been pressed
  drawing::Button::press();
  //legacy auton selection (will be removed soon)
  /*
  int xp = Brain.Screen.xPosition();
  int yp = Brain.Screen.yPosition();
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1,1);
  Controller1.Screen.print("Auton Selected: ");
  Controller1.Screen.setCursor(2,1);
  //Controller1.Screen.print(xp);
  //Controller1.Screen.setCursor(2,1);
  //Controller1.Screen.print(yp);
  if(xp < maxWidth) {
    //left quadrants assuming 0,0 is topleft
    if(yp > maxHeight) {
      //Redleft
      selectedAuton = AutonSelect::RedLeft;
      Controller1.Screen.print("Red Left");
    } else {
      //BlueLeft
      selectedAuton = AutonSelect::BlueLeft;
      Controller1.Screen.print("Blue Left");
    }
  } else {
    //right quadrants assuming 0,0 is topleft
    if(yp > maxHeight) {
      //BlueRight
      selectedAuton = AutonSelect::BlueRight;
      Controller1.Screen.print("Blue Right");
    } else {
      //RedRight
      selectedAuton = AutonSelect::RedRight;
      Controller1.Screen.print("Red Right");
    }
  }
*/

  /*
  //GOD

  for (int i = 0; i < s.size(); i++) {
    if((xp >= s[i].x) && (xp <= (s[i].x + s[i].width))) {
      if((yp >= s[i].y) && (yp <= (s[i].y + s[i].height))) {
        Controller1.Screen.clearScreen();
        Controller1.Screen.setCursor(1, 1);
        Controller1.Screen.print(i);
      }
    }
  }
  */
}


/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  Vision17.setLedMode(vision::ledMode::manual);

  //autonomous selection
  Right = new drawing::Button(maxWidth/2, 0, maxWidth, maxHeight, LeftButton, "Right (8 Pointer)", color(0,0,255));
  Left = new drawing::Button(0,0, maxWidth/2, maxHeight, RightButton, "Left (8 Pointer)", color(255,0,0));

}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
task::sleep(3000);

//Auton::turnToHeadingPID(90);

//Skills Right

  Auton::rollerTrainForTime(2, forward, seconds, 80, vex::velocityUnits::pct);

  Drivetrain.driveFor(reverse, 15, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);

  Auton::turnToHeadingPID(-90);

  Drivetrain.driveFor(forward, 40, vex::distanceUnits::cm, 25, velocityUnits::pct);

  Auton::intakeOn();
  
  Auton::driveForTime(2, forward, seconds, 15, vex::velocityUnits::pct);

  Drivetrain.driveFor(reverse, 18, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);

  Auton::intakeOff();

  Auton::turnToHeadingPID(-45);

  Auton::driveForTime(3, forward, seconds, 10, velocityUnits::pct);

  Auton::rollerTrainForTime(2, forward, seconds, 80, vex::velocityUnits::pct);

  Drivetrain.driveFor(reverse, 15, distanceUnits::cm, 10, vex::velocityUnits::pct);

//  Auton::turnToHeading(180, 1, 1, 15);

//  Drivetrain.driveFor(forward, 70, distanceUnits::cm, 10, vex::velocityUnits::pct);

  //Match Right
  /*
  Auton::rollerTrainForTime(2, forward, seconds, 80, vex::velocityUnits::pct);
  Drivetrain.driveFor(reverse, 18, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
  Auton::turnToHeading(270, 1, 1, 25);
  Drivetrain.driveFor(forward, 35, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
  Auton::turnToHeading(315, 1, 1, 25);
  Auton::intakeOn();
  Auton::driveForTime(2, forward, seconds, 20, velocityUnits::pct);
  Auton::intakeOff();
  Auton::rollerTrainForTime(2);
  Auton::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 10, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
  Auton::intakeOff;
  */
  //Match Left
  /*
  Auton::rollerTrainForTime(2, forward, seconds, 80, vex::velocityUnits::pct);
  Drivetrain.driveFor(reverse, 18, vex::distanceUnits::cm, 15, vex::velocityUnits::pct);
  Auton::turnToHeading(90, 1, 1, 25);
  Drivetrain.driveFor(forward, 35, vex::distanceUnits::cm, 15, vex::velocityUnits::pct);
  Auton::turnToHeading(45, 1, 1, 25);
  Auton::intakeOn();
  Auton::driveForTime(2, forward, seconds, 20, velocityUnits::pct);
  Auton::intakeOff();
  Auton::rollerTrainForTime(2);
  Auton::intakeOn(reverse);
  Drivetrain.driveFor(reverse, 20, vex::distanceUnits::cm, 20, vex::velocityUnits::pct);
  Auton::intakeOff();
  */
  //Match Center
  /*
  Auton::rollerTrainForTime(2, forward, seconds, 80, vex::velocityUnits::pct);

  Drivetrain.driveFor(reverse, 10, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);

  Auton::turnToHeading(90, 1, 1, 25);

  Auton::turnToHeading(180, 1, 1, 25);

  wait(1, sec);

  Auton::intakeOn();

  Auton::driveForTime(4, forward, seconds, 10, velocityUnits::pct);
  //Drivetrain.driveFor(forward, 20, vex::distanceUnits::cm, 10, velocityUnits::pct);

  Auton::intakeOff();

  Auton::rollerTrainForTime(2);

  Drivetrain.driveFor(reverse, 10, vex::distanceUnits::cm, 10, vex::velocityUnits::pct);
  */
  //Match Corner
  /*
  Auton::intakeOn();
  Auton::driveForTime(1, forward, seconds, 50, velocityUnits::pct);
  Auton::intakeOff();
  Auton::rollerTrainForTime(2);
  Auton::intakeOn(reverse);
  Auton::driveForTime(1, reverse, seconds, 50, velocityUnits::pct);
  Auton::intakeOff();
  */
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  switch(selectedAuton){
    Controller1.Screen.clearScreen();
    Controller1.Screen.setCursor(1,1);
    Controller1.Screen.print("Running:");
    case RedLeft:
      Controller1.Screen.print("Red Left Auton");

      //auton goes here
    break;

    case BlueRight:
      Controller1.Screen.print("Blue Right Autonomous");
    break;

    case BlueLeft:
      Controller1.Screen.print("Blue Left Autonomous");
    break;

    case RedRight:
      Controller1.Screen.print("Red Right Autonomous");

      //auton goes here
    break;

    case None:
      Controller1.Screen.print("No Auton selected RIP");

      //auton goes here
    break;
  }
  Controller1.Screen.clearScreen();
  Controller1.Screen.setCursor(1, 1);
  Controller1.Screen.print("Auton Complete!");
}
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  //Controller1.ButtonRight.pressed(test);

  Brain.Screen.pressed(click);

  Controller1.ButtonA.pressed(swapTank);
  Controller1.ButtonB.pressed(swapTrain);
  Controller1.ButtonUp.released(stopDrive);
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    //movement

    if(Brain.Battery.capacity() > 75) {
      Green.on();
      Yellow.off();
      Red.off();
    } else if(Brain.Battery.capacity() > 50 && Brain.Battery.capacity() < 75) {
      Green.off();
      Yellow.on();
      Red.off();
    } else {
      Green.off();
      Yellow.off();
      Red.off();
    }
    
    if (tank == true) {
      leftMotorA.spin(forward, Controller1.Axis3.value(), pct);
      leftMotorB.spin(forward, Controller1.Axis3.value(), pct);
      rightMotorA.spin(forward, Controller1.Axis2.value(), pct);
      rightMotorB.spin(forward, Controller1.Axis2.value(), pct);
    } else {
      leftMotorA.spin(forward, Controller1.Axis3.value() + Controller1.Axis1.value(), pct);
      leftMotorB.spin(forward, Controller1.Axis3.value() + Controller1.Axis1.value(), pct);
      rightMotorA.spin(forward, Controller1.Axis3.value() - Controller1.Axis1.value(), pct);
      rightMotorB.spin(forward, Controller1.Axis3.value() - Controller1.Axis1.value(), pct);
    }

    //Intake
    if(Controller1.ButtonR1.pressing()) {
      IntakeR.spin(forward, 100, pct);
      IntakeL.spin(forward, 100, pct);
      TrainT.spin(forward,100, pct);
    } else if(Controller1.ButtonR2.pressing()) {
      IntakeR.spin(reverse, 100, pct);
      IntakeL.spin(reverse, 100, pct);
    } else if(Controller1.ButtonUp.pressing()) {
      IntakeR.spin(forward, 100, pct);
      IntakeL.spin(forward, 100, pct);
      Drivetrain.drive(forward, 20, velocityUnits::pct);
    }

    if(!Controller1.ButtonR1.pressing() && !Controller1.ButtonR2.pressing() && !Controller1.ButtonLeft.pressing() && !Controller1.ButtonUp.pressing()) {
      IntakeL.stop();
      IntakeR.stop();
      TrainT.stop();
    }

    if(cameraToggle == manual) {
      if(Controller1.ButtonL1.pressing()) {
        TrainT.spin(forward, 100, pct);
        TrainB.spin(forward, 100, pct);
      } else if(Controller1.ButtonL2.pressing()) {
        TrainT.spin(reverse, 100, pct);
        TrainB.spin(reverse, 100, pct);
      } else if (Controller1.ButtonLeft.pressing()) {
        TrainT.spin(reverse, 100, pct);
        TrainB.spin(forward, 100, pct);
        IntakeL.spin(forward, 100, pct);
        IntakeR.spin(forward, 100, pct);
      } else {
        //TrainT.stop();
        TrainB.stop();
      }
    } else {
    //roller train ball sorting and cycling

      TrainB.spin(forward, 50, pct);

      //red signature
      Vision17.takeSnapshot(Vision17__R3D);
      vex::vision::object biggest_red = Vision17.largestObject;
      int red_area = biggest_red.width * biggest_red.height;
      
      //blue signature
      Vision17.takeSnapshot(Vision17__BLU);
      vex::vision::object biggest_blue = Vision17.largestObject;
      int blue_area = biggest_blue.width * biggest_blue.height;

      //decide what to do based on vision sensor data
      if ((red_area > blue_area) && (red_area > 10000)) {
        //red ball
        Vision17.setLedColor(255, 0, 0);
        if(selectedAuton == RedLeft || selectedAuton == RedRight) {
          TrainT.spin(forward, 50, pct);
        } else if (selectedAuton == BlueLeft || selectedAuton == BlueRight) {
          TrainT.spin(reverse, 80, pct);
        }
      } else if ((blue_area > red_area) && (blue_area > 10000)) {
        //blue ball
        Vision17.setLedColor(0, 0, 255);
        if(selectedAuton == RedLeft || selectedAuton == RedRight) {
          TrainT.spin(reverse, 80, pct);
        } else if (selectedAuton == BlueLeft || selectedAuton == BlueRight) {
          TrainT.spin(forward, 50, pct);
        }
      } else {
        //none
        Vision17.setLedColor(255, 255, 0);
        TrainT.spin(reverse, 50, pct);
        //
        //TrainT.stop();
      }
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
    
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
