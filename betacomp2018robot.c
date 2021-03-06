#pragma config(Sensor, dgtl1,  sonarLeft,      sensorSONAR_inch)
#pragma config(Sensor, dgtl3,  sonarRight,     sensorSONAR_inch)
#pragma config(Motor,  port1,           wheelFrontLeft, tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           wheelFrontRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port3,           wheelRearLeft, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port4,           wheelRearRight, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port6,           armMotor1,     tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port7,           armMotor2,     tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port9,           claw,          tmotorVex393_MC29, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// CONTROLS

// 7U, release claw
// 7D, clamp claw
// Ch4, rotate robot
// 6D, drive forwards
// 5D, drive backwards
// Ch2, control arm
// 8U, toggle TURBO


bool isTurboEnabled = false;
bool isClawPressed = false;

float defaultSpeed = 0.5; // this is multiplier for without turbo
float speed = defaultSpeed; // this is current drive speed multiplier
int vectorFrontLeft = 0;
int vectorFrontRight = 0;
int vectorRearLeft = 0;
int vectorRearRight = 0;

int clawGrabPressure = -127; // set this to a value between [0 to -127]
int clawReleasePressure = 100; // set this to a value between [0 to 127]


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

	if (vexRT[Btn8U] == 1) {
		isTurboEnabled = true;
	} else {
		isTurboEnabled = false;
	}

	if (isTurboEnabled == true) {
		speed = 1.0; // max out motors
	} else { speed = defaultSpeed; }


	// FORWARDS BACKWARDS MOVEMENT
	// checks which button pressed then sets variable to 127 or -127
	int forwardsBackwardsSpeed = 0;
		if (vexRT[Btn6D] == 1) { // forwards
			forwardsBackwardsSpeed = 127;
		}
		else if (vexRT[Btn5D] == 1) { // backwards
			forwardsBackwardsSpeed = -127;
		}
	vectorFrontLeft += (forwardsBackwardsSpeed) * speed;
	vectorFrontRight += (forwardsBackwardsSpeed) * speed;
	vectorRearLeft += (forwardsBackwardsSpeed) * speed;
	vectorRearRight += (forwardsBackwardsSpeed) * speed;

	// STEERING MOVEMENT
	vectorFrontLeft += (vexRT[Ch4]) * speed;
	vectorFrontRight -= (vexRT[Ch4]) * speed;
	vectorRearLeft += (vexRT[Ch4]) * speed;
	vectorRearRight -= (vexRT[Ch4]) * speed;


	// finally sets the wheel motors to the vector values
	runWheels();


	/// CLAW STUFF

	if (vexRT[Btn7U] == 1) { // disable claw pressure
		isClawPressed = false;
	}
	else if (vexRT[Btn7D] == 1) { // enable claw pressure
		isClawPressed = true;
	}

	if (vexRT[Btn7U] == 1) { // run motor release speed
		motor[claw] = clawReleasePressure;
	}
	else {
		motor[claw] = 0; // else stop the claw
	}

	// now if the isClawPressed enabled, override whatever the motor
	// 		speed was before and set it to claw pressure
	if (isClawPressed == true) {
		motor[claw] = clawGrabPressure;
	}

	// and set the arm speed to ch2
	motor[armMotor1] = vexRT[Ch2];
	motor[armMotor2] = vexRT[Ch2];

}
}
