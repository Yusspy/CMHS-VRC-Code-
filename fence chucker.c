#pragma config(Motor,  port1,           frontLeftWheel, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightClaw,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           rearLeftWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           rearRightWheel, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           leftArmLift1,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           leftArmLift2,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           rightArmLift1, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           rightArmLift2, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           leftClaw,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          frontRightWheel, tmotorVex393_HBridge, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#pragma platform(VEX)

//Competition Control and Duration Settings// DON'T MODIFY!
#pragma competitionControl(Competition)
#pragma autonomousDuration(15)
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

int frontLeftVector = 0;
int frontRightVector = 0;
int rearLeftVector = 0;
int rearRightVector = 0;

void moveForward(int speed) {
    	motor[frontLeftWheel] = speed;
	motor[frontRightWheel] = speed;
	motor[rearLeftWheel] = speed;
	motor[rearRightWheel] = speed;
}
void moveBackward(int speed) {

}

void strafeLeft(int speed) {

}
void strafeRight(int speed) {

}

void rotateLeft(int speed) {
    
}
void rotateRight(int speed) {
    
}

void stopMoving() {
    	motor[frontLeftWheel] = 0;
	motor[frontRightWheel] = 0;
	motor[rearLeftWheel] = 0;
	motor[rearRightWheel] = 0;
}

void runWheels() {
	motor[frontLeftWheel] = frontLeftVector;
	motor[frontRightWheel] = frontRightVector;
	motor[rearLeftWheel] = rearLeftVector;
	motor[rearRightWheel] = rearRightVector;
}

void resetWheelVectors() {
	frontLeftVector = 0;
	frontRightVector = 0;
	rearLeftVector = 0;
	rearRightVector = 0;
}

void setArmLiftSpeed(int speed) {
	motor[leftArmLift1] = speed;
	motor[leftArmLift2] = speed;
	motor[rightArmLift1] = -speed;
	motor[rightArmLift2] = -speed;
}

void resetPincerClaws() {
	motor[leftClaw] = 0;
	motor[rightClaw] = 0;
}

int perviePincerPressureSpeed = 60;



/////////////////////////////////////////////////////////////////////////////////////////
//
//                                 Autonomous Task
//
// This task is used to control your robot during the autonomous phase of a VEX Competition.
// You must modify the code to add your own robot specific commands here.
//
/////////////////////////////////////////////////////////////////////////////////////////
task autonomous() {

	////////// i donut have anythang good here yet ///////

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
	while (69 == 69) //lol, get rekt
	{

		resetWheelVectors();
		resetPincerClaws();

		//Moving forwards and backwards
		frontLeftVector += vexRT[Ch3];
		frontRightVector += vexRT[Ch3];
		rearLeftVector += vexRT[Ch3];
		rearRightVector += vexRT[Ch3];

		
		//Strafing left and right
		frontLeftVector += vexRT[Ch4];
		frontRightVector -= vexRT[Ch4];
		rearLeftVector -= vexRT[Ch4];
		rearRightVector += vexRT[Ch4];

		//Turning
		frontLeftVector += vexRT[Ch1] *2;
		frontRightVector -= vexRT[Ch1] *2;
		rearLeftVector += vexRT[Ch1] *2;
		rearRightVector -= vexRT[Ch1] *2;

		runWheels(); //inputs wheel vectors

		//Arm lift Control
		if (vexRT[Btn6U] == 1) {
			setArmLiftSpeed(127);
		}
		else if (vexRT[Btn5U] == 1) {
			setArmLiftSpeed(-127);
		}
		else {
			setArmLiftSpeed(0);
		}

		//pincer control open
		if (vexRT[Btn6D] == 1) {
			motor[leftClaw] = 127;
			motor[rightClaw] = -127;
		}
		//pincer control close
		if (vexRT[Btn5D] == 1) {
			motor[leftClaw] = -127;
			motor[rightClaw] = 127;
		}

		//fine tune left claw
		/*if (vexRT[Btn7L] == 1) {motor[leftClaw] = -perviePincerFineTuneSpeed;}
		if (vexRT[Btn7R] == 1) {motor[leftClaw] = perviePincerFineTuneSpeed;}

		//fine tune right claw
		if (vexRT[Btn8R] == 1) {motor[rightClaw] = perviePincerFineTuneSpeed;}
		if (vexRT[Btn8L] == 1) {motor[rightClaw] = -perviePincerFineTuneSpeed;}*/

	}
}
