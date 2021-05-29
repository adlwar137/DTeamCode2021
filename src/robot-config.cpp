#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
/*vex-vision-config:begin*/
signature Vision17__R3D = signature (1, 4681, 6389, 5536, -1, 1629, 814, 4, 0);
signature Vision17__BLU = signature (2, -3073, -1259, -2166, 8235, 15171, 11702, 1, 0);
signature Vision17__GOAL = signature (3, -4627, -913, -2770, -4067, -409, -2238, 1.3, 0);
vision Vision17 = vision (PORT16, 50, Vision17__BLU, Vision17__R3D);
/*vex-vision-config:end*/
controller Controller1 = controller(primary);
motor TrainT = motor(PORT5, ratio18_1, true);
motor TrainB = motor(PORT6, ratio18_1, false);
motor IntakeR = motor(PORT11, ratio18_1, true);
motor IntakeL = motor(PORT12, ratio18_1, false);
motor leftMotorA = motor(PORT2, ratio6_1, false);
motor leftMotorB = motor(PORT4, ratio6_1, false);
motor_group LeftDriveSmart = motor_group(leftMotorA, leftMotorB);
motor rightMotorA = motor(PORT1, ratio6_1, true);
motor rightMotorB = motor(PORT3, ratio6_1, true);
motor_group RightDriveSmart = motor_group(rightMotorA, rightMotorB);
inertial TurnGyroSmart = inertial(PORT18);
smartdrive Drivetrain = smartdrive(LeftDriveSmart, RightDriveSmart, TurnGyroSmart, 299.24, 320, 40, mm, 1);
led Green = led(Brain.ThreeWirePort.A);
led Yellow = led(Brain.ThreeWirePort.B);
led Red = led(Brain.ThreeWirePort.C);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}