
#include "main.h"
#include <math.h>

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

int backwards_timer = 21;
bool backwards = false;

bool isBackwards() {
  if(joystickGetDigital(1, 7, JOY_DOWN)) {
    if(backwards && backwards_timer > 20) {
      backwards = false;
      backwards_timer = 0;
    }
    else if(backwards_timer > 20) {
      backwards = true;
      backwards_timer = 0;
    }
  }

  backwards_timer++;

  return backwards;
}

int rightTemp = 0;
void driveRobot(int rightPower, int leftPower){
  ///// Set Motors /////
  if(isBackwards()) {

    rightTemp = rightPower;
    rightPower = -leftPower;
    leftPower = -rightTemp;
  }

  motorSet(BACK_RIGHT_DRIVE, rightPower);
  motorSet(MID_RIGHT_DRIVE, -rightPower);
  motorSet(FRONT_RIGHT_DRIVE, rightPower);
  motorSet(BACK_LEFT_DRIVE, -leftPower);
  motorSet(MID_LEFT_DRIVE, leftPower);
  motorSet(FRONT_LEFT_DRIVE, -leftPower);
}

int leftDrive, rightDrive;

void setDrive() {
  if(false) { //joystickGetDigital(1,5,JOY_UP)
    rightDrive = joystickGetAnalog(1, 3) - joystickGetAnalog(1,4);
    leftDrive = joystickGetAnalog(1, 3) + joystickGetAnalog(1,4);
  }
  else {
    rightDrive = joystickGetAnalog(1, 2);
    leftDrive = joystickGetAnalog(1, 3);
  }

  if(true) { //joystickGetDigital(1,6,JOY_UP)
    // Correct values for Linear speed Increase
    if(abs(rightDrive) <= 20) rightDrive = 0;
    else if(rightDrive < -127) rightDrive = -trueSpeed[127];
    else if(rightDrive < 0) rightDrive = -trueSpeed[-rightDrive];
    else if(rightDrive > 127) rightDrive = trueSpeed[127];
    else rightDrive = trueSpeed[rightDrive];

    if(abs(leftDrive) <= 20) leftDrive = 0;
    else if(leftDrive < -127) leftDrive = -trueSpeed[127];
    else if(leftDrive < 0) leftDrive = -trueSpeed[-leftDrive];
    else if (leftDrive > 127) leftDrive = trueSpeed[127];
    else leftDrive = trueSpeed[leftDrive];
 }
 else{
   if(abs(rightDrive) <= 20) rightDrive = 0;
   if(abs(leftDrive) <= 20) leftDrive = 0;
 }

 driveRobot(rightDrive,leftDrive);

}


void turn(int degrees) {

}


int distance_timer = 0, drive_speed = -40;
void goFar(int distance) {

  while(distance_timer < distance) {

    if(abs(distance-distance_timer) <= 127 && drive_speed < 0)
      drive_speed++;

    driveRobot(drive_speed,drive_speed);
    distance_timer++;
  }
  driveRobot(0,0);
}



void autonTest() {
  if(digitalRead(AUTON)) {
    shootPuncher();
    print("FINISHED SHOOTING");
    goFar(3500);
  }
  else
    shootPuncher();

  print("DONE WITH AUTON");
}
