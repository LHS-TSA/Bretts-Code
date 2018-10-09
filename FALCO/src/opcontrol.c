
#include "main.h"

bool isFlipping;
void operatorControl() {

	while (true) {

		//if(joystickGetDigital(1, 7, JOY_UP))
			//autonTest();

    ///// Set Motors /////
    setDrive();

    ///// Control the Lift /////
    setLift();

    ///// Control the Claw /////
    setPancake();

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
