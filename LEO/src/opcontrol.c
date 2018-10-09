
#include "main.h"

bool isFlipping;
void operatorControl() {

	isFlipping = false;
	while (true) {

		//print(digitalRead(AUTON) ? "true\n" : "false\n");
		//if(joystickGetDigital(1, 7, JOY_UP))
			//autonTest();
		print( digitalRead(AUTON) ? "true\n" : "false\n");


    ///// Set Motors /////
    setDrive();

    ///// Control the Lift /////
    setLift();

    ///// Control the Claw /////
    if(joystickGetDigital(1, 8, JOY_LEFT) || isFlipping)
      isFlipping = setPancake();

    ///// Control the Puncher /////
    setPuncher();

    ///// Control the Intake /////
    setIntake();

    ///// Delay /////
    delay(20);
		}
}



/*
motorSet(BACK_RIGHT_DRIVE, rightDrive);
motorSet(MID_RIGHT_DRIVE, rightDrive);
motorSet(FRONT_RIGHT_DRIVE, -rightDrive);
motorSet(BACK_LEFT_DRIVE, -leftDrive);
motorSet(MID_LEFT_DRIVE, -leftDrive);
motorSet(FRONT_LEFT_DRIVE, leftDrive);
*/
