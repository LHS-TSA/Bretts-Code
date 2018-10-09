

#include "main.h"

const int trueSpeed[128] =
{
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
 25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
 28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
 33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
 37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
 41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
 46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
 52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
 61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
 71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
 80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
 88, 89, 89, 90, 90,127,127,127
};

void operatorControl(){

		int leftDrive, rightDrive;
		int lift, distanceBehind;
		while (true) {


      if(joystickGetDigital(1,7,JOY_UP))
        square();

      if(joystickGetDigital(1,7,JOY_LEFT))
        wallRide(true);

      if(joystickGetDigital(1,5,JOY_UP)) {
        rightDrive = joystickGetAnalog(1, 3) + joystickGetAnalog(1,4);
			  leftDrive = joystickGetAnalog(1, 3) - joystickGetAnalog(1,4);
      }
      else {
        rightDrive = joystickGetAnalog(1, 2);
  			leftDrive = joystickGetAnalog(1, 3);
      }

      distanceBehind = ultrasonicGet(back);
      // Correct values for Linear speed Increase and Prevent unwanted events
      if(abs(rightDrive) <= 15) rightDrive = 0;
      else if(distanceBehind > 0 && distanceBehind < 25 && rightDrive < 0) rightDrive = 10;
      else if(rightDrive < -127) rightDrive = -trueSpeed[127];
      else if(rightDrive < 0) rightDrive = -trueSpeed[-rightDrive];
      else if(rightDrive > 127) rightDrive = trueSpeed[127];
      else rightDrive = trueSpeed[rightDrive];

      if(abs(leftDrive) <= 15) leftDrive = 0;
      else if((distanceBehind > 0 && distanceBehind < 25 && leftDrive < 0)) leftDrive = 10;
      else if(leftDrive < -127) leftDrive = -trueSpeed[127];
      else if(leftDrive < 0) leftDrive = -trueSpeed[-leftDrive];
      else if (leftDrive > 127) leftDrive = trueSpeed[127];
      else leftDrive = trueSpeed[leftDrive];

      // Control the lift
			lift = 0;
			if(joystickGetDigital(1,6,JOY_UP) && analogRead(LIFT_PENTENTIOMETER) < 2700 ) lift = -45;
			else if(joystickGetDigital(1, 6, JOY_DOWN) && digitalRead(LIGHT_LIMIT_SWITCH) == HIGH) lift = 15;

      display();

			///// Set Motors /////
			motorSet(R_DRIVE, -rightDrive);
			motorSet(L_DRIVE, leftDrive);
      motorSet(LIFT, lift);

      print("Test ");

      delay(20);
		}
}
