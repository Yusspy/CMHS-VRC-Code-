#pragma config(Motor,  port1,           wheelRearLeft, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           wheelFrontRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           mobileGoalLift, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           wheelRearRight, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port5,           liftLeftSide,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRightSide, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           coneFlipLeft,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           coneFlipRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           coneClaw,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          wheelFrontLeft, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings// DON'T MODIFY!
#pragma competitionControl(Competition)
#pragma autonomousDuration(20)
#pragma userControlDuration(120)

#include "Vex_Competition_Includes.c"   //Main competition background code...do not modify!




/////////////////////////////////////////////////////////////////////////////////////////
//
//                          Pre-Autonomous Functions
//
// You may want to perform some actions before the competition starts. Do them in the
// following function.
//
/////////////////////////////////////////////////////////////////////////////////////////
void pre_auton() {
  // Set bStopTasksBetweenModes to false if you want to keep user created tasks running between
  // Autonomous and Tele-Op modes. You will need to manage all user created tasks if set to false.
					bStopTasksBetweenModes = true;

	// All activities that occur before the competition starts
	// Example: setting servo positions, extending arm, loading shotgun ...
    // If your robot is a Transformer(copyrighted), then transformation occurs here

}





/////////////////////////////////////////////////////////////////////////////////////////
//
//                             Used Variables and Funcions
//
// Any variables or functions that you will be using are initialized in this area right here.
//
/////////////////////////////////////////////////////////////////////////////////////////

int vectorFrontLeft = 0;
int vectorFrontRight = 0;
int vectorRearLeft = 0;
int vectorRearRight = 0;
bool isTurboEnabled = false;
float speed = 0.5;

void resetWheelVectors() {
	vectorFrontLeft = 0;
	vectorFrontRight = 0;
	vectorRearLeft = 0;
	vectorRearRight = 0;
}

void runWheels() {
	motor[wheelFrontLeft] = vectorFrontLeft;
	motor[wheelFrontRight] = vectorFrontRight;
	motor[wheelRearLeft] = vectorRearLeft;
	motor[wheelRearRight] = vectorRearRight;
}

void moveForward(int speed) {
	motor[wheelFrontRight] = speed;
	motor[wheelRearLeft] = speed;
	motor[wheelRearRight] = speed;
}

void runLift(int speed) {
	motor[liftLeftSide] = speed;
	motor[liftRightSide] = speed;
}

void runMobileGoalPickup(int speed) {
	motor[mobileGoalLift] = speed;
}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task autonomous() {

	motor[coneClaw] = -30;
	moveForward(65);
	wait1Msec(2700);
	moveForward(0);

 	runLift(127);
 	wait1Msec(700);
 	runMobileGoalPickup(-127);
 	wait1Msec(800);
 	runLift(0);
 	runMobileGoalPickup(0);

	moveForward(65);
	wait1Msec(700);
	moveForward(0);

}


/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 User Control Task
//
// This task is used to control your robot during the user control phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task usercontrol() {
/* an infinite loop */
while (0 == 0) // lol it looks like a face
{

	resetWheelVectors();

	if (vexRT[Btn5U] == 1) {
		isTurboEnabled = true;
	} else {
		isTurboEnabled = false;
	}

	if (isTurboEnabled == true) {
		speed = 1.0;
	} else { speed = 0.5; }

	vectorFrontLeft += (vexRT[Ch3])*speed;
	vectorFrontRight += (vexRT[Ch3])*speed;
	vectorRearLeft += (vexRT[Ch3])*speed;
	vectorRearRight += (vexRT[Ch3])*speed;

	vectorFrontLeft += (vexRT[Ch1])*speed;
	vectorFrontRight -= (vexRT[Ch1])*speed;
	vectorRearLeft += (vexRT[Ch1])*speed;
	vectorRearRight -= (vexRT[Ch1])*speed;

	runWheels();


	// LIFT ///
	if (vexRT[Btn8LXmtr2] == 1) {
		motor[liftLeftSide] = 127;
		motor[liftRightSide] = -10;
	} else if (vexRT[Btn8RXmtr2] == 1) {
		motor[liftLeftSide] = -10;
		motor[liftRightSide] = 127;
	} else if (vexRT[Btn8UXmtr2] == 1) {
		motor[liftLeftSide] = 127;
		motor[liftRightSide] = 127;
	} else if (vexRT[Btn8DXmtr2] == 1) {
		motor[liftLeftSide] = -35;
		motor[liftRightSide] = -35;
	} else {
		motor[liftLeftSide] = 0;
		motor[liftRightSide] = 0;
	}

	// CONE FLIPPER //
	if (vexRT[Btn5UXmtr2] == 1) {
		motor[coneFlipLeft] = 127;
		motor[coneFlipRight] = 127;
	} else if (vexRT[Btn5DXmtr2] == 1) {
		motor[coneFlipLeft] = -127;
		motor[coneFlipRight] = -127;
	}  else {
		motor[coneFlipLeft] = 0;
		motor[coneFlipRight] = 0;
	}

	// MOBILE GOAL LIFT //
	if (vexRT[Btn8U] == 1) {
		motor[mobileGoalLift] = 127;
	} else if (vexRT[Btn8D]) {
		motor[mobileGoalLift] = -127;
	} else {
		motor[mobileGoalLift] = 0;
	}

	// THE CLAW //
	if (vexRT[Btn6U] == 1) {
		motor[coneClaw] = 35;
	} else if (vexRT[Btn6D] == 1) {
		motor[coneClaw] = -30;
	} else {
		motor[coneClaw] = 0;
	}

}
}
