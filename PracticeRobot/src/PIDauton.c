

#include "main.h"
#include <math.h>

void rightDrive(int power) {
  motorSet(R_DRIVE,-power);
}

void leftDrive(int power) {
  motorSet(L_DRIVE,power);
}

void square() {
  for(int i = 0; i < 4; i++) {
    drivePID(600);
    turnPID(90,true);
  }
}

void wallRide(bool forwards) {
    // Use Sonar Values in order to drive straight next to a wall
    int rightpower, leftpower, stop, back, front;
    const double kp = 1.4236;
    double error;

    while(true) {

      back = ultrasonicGet(backRight);
      front = ultrasonicGet(frontRight);
      error = back - front;
      displayInt(back,front);

      if(stop >= 10)
        break;
      else if(abs(error) < 1 && back > 5 && front > 5)
        stop++;
      else
        stop = 0;

      if(error == 0){
        rightpower = 75;
        leftpower = 75;
      }
      else if(error > 0){
        rightpower = (int)(kp * error * (1.0/2));
        leftpower = kp * error;
      }
      else {
        rightpower = kp * error;
        leftpower = (int)(kp * error * (1.0/2));
      }

      if(forwards) {
        rightDrive(rightpower);
        leftDrive(leftpower);
      }
      else {
        rightDrive(-rightpower);
        leftDrive(-leftpower);
      }

      delay(20);
    }
}

void drivePID(int distance) {
  // Distance is kept in encoder values (degrees of wheel rotation)
  encoderReset(right);
  encoderReset(left);
  distance = abs(distance);

  int power;
  const double kp = 0.34, ki = 0.26, kd = 0.86;
  double error, previousError = 0, totalError = 0, deriv = 0;

  // Set Minumum Speed Related to Distance
  int min = distance * -0.5 + 65; // Required to reach target
  if(min < 20) min = 20;

  int stop = 0;
  while(true) {

    // P
    error = distance - (encoderGet(right) + encoderGet(left))/2.0;
    if(stop >= 6 || error < 0)
      break;
    else if(abs(error) < 15)
      stop++;
    else
      stop = 0;

    // I
    totalError += error;

    // D
    deriv = error - previousError;
    previousError = error;

    power = (int)(kp * error + ki * totalError + kd * deriv);
    if(power < min) power = min;

    printf("Driving- Error: %f      Power: %d ////// ",error,power);
    displayInt(error,power);

    rightDrive(power);
    leftDrive(power);

    delay(40);
  }
}

void turnPID(int degrees,bool clockwise) {
  // Use gyro to turn certain amount of degrees in a given direction
  gyroReset(gyro);
  degrees *= 10;

  int power;
  const double kp = 2.43, ki = 0.26, kd = 10.8;
  double error, previousError = 0, totalError = 0, deriv = 0;

  // Minmum Speed
  int min = -.35 * abs(degrees) + 65;
  if(min < 25) min = 25;

  int stop = 0;
  while(true) {

    // P
    error = degrees - abs(gyroGet(gyro));
    if(stop >= 6 || error < 0)
      break;
    else if(abs(error) < 6)
      stop++;
    else
      stop = 0;

    // I
    totalError += error;

    // D
    deriv = error - previousError;
    previousError = error;

    power = (int)(kp * error + ki * totalError + kd * deriv);
    if(power < min) power = min;

    printf("Turning- Error: %f      Power: %d  ///////// ",error,power);
    displayInt((int)error,power);


    if(clockwise) {
      rightDrive(-power);
      leftDrive(power);
    }
    else{
      rightDrive(power);
      leftDrive(-power);
    }

    delay(20);
  }

  // Stop the robot
  leftDrive(0);
  rightDrive(0);
  delay(40);
}
