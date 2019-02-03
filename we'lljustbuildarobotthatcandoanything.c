#pragma config(Motor,  port1,           wheelFrontLeft, tmotorVex393_HBridge, openLoop, reversed)
#pragma config(Motor,  port2,           capRotate,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           wheelRearLeft, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port4,           wheelRearRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port5,           liftLeft,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           liftRight,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           ballLift,      tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           ballShooterL,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port9,           ballShooterR,  tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port10,          wheelFrontRight, tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// CONTROLS
// CH1 and CH2
// 6U and 6D rotate cap intake
// 8U 8D right lift
// 7U 7D left lift
// 5U turybow


bool isTurboEnabled = false;

float defaultSpeed = 0.5; // this is multiplier for without turbo
float speed = defaultSpeed; // this is current drive speed multiplier
int vectorFrontLeft = 0;
int vectorFrontRight = 0;
int vectorRearLeft = 0;
int vectorRearRight = 0;


void resetWheelVectors() {
	vectorFrontLeft = 0;
	vectorFrontRight = 0;
	vectorRearLeft = 0;
	vectorRearRight = 0;
}
// note that some vectors can hit 256 with turbo, like if you've maxed out turning and full forwards
//		robotC just sets it to max speed at that point
void runWheels() {
	motor[wheelFrontLeft] = vectorFrontLeft;
	motor[wheelFrontRight] = vectorFrontRight;
	motor[wheelRearLeft] = vectorRearLeft;
	motor[wheelRearRight] = vectorRearRight;
}


task main() {

while (0 == 0) { // infinite loop for live control


	resetWheelVectors();

	if (vexRT[Btn5U] == 1) {
		isTurboEnabled = true;
	} else {
		isTurboEnabled = false;
	}

	if (isTurboEnabled == true) {
		speed = 1.0; // max out motors
	} else { speed = defaultSpeed; }


	vectorFrontLeft += (vexRT[Ch3])*speed;
	vectorFrontRight += (vexRT[Ch3])*speed;
	vectorRearLeft += (vexRT[Ch3])*speed;
	vectorRearRight += (vexRT[Ch3])*speed;

	vectorFrontLeft += (vexRT[Ch1])*speed;
	vectorFrontRight -= (vexRT[Ch1])*speed;
	vectorRearLeft += (vexRT[Ch1])*speed;
	vectorRearRight -= (vexRT[Ch1])*speed;


	// finally sets the wheel motors to the vector values
	runWheels();


  if (vexRT[Btn7U] == 1) {
  	motor[liftLeft] = 127;
	}
	if (vexRT[Btn7D] == 1) {
  	motor[liftLeft] = -20;
	}

  if (vexRT[Btn8U] == 1) {
  	motor[liftRight] = 127;
	}
	if (vexRT[Btn8D] == 1) {
  	motor[liftRight] = -20;
	}


	if (vexRT[Btn6D] == 1) {
		motor[capRotate] = -127;
	}
	else if (vexRT[Btn6U] == 1) {
		motor[capRotate] = 127;
	}
	else {
		motor[capRotate] = 0;
	}

}
}
