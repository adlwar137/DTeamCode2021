using namespace vex;

extern brain Brain;

using signature = vision::signature;

// VEXcode devices
extern signature Vision17__BLU;
extern signature Vision17__R3D;
extern signature Vision17__SIG_3;
extern signature Vision17__SIG_4;
extern signature Vision17__SIG_5;
extern signature Vision17__SIG_6;
extern signature Vision17__SIG_7;
extern vision Vision17;
extern controller Controller1;
extern motor TrainT;
extern motor TrainB;
extern motor IntakeR;
extern motor IntakeL;
extern smartdrive Drivetrain;
extern motor leftMotorA;
extern motor leftMotorB;
extern motor rightMotorA;
extern motor rightMotorB;
extern led Green;
extern led Yellow;
extern led Red;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );