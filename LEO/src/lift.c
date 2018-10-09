#include "main.h"

void lift(int power) {
  motorSet(LIFT_LEFT, power);
  motorSet(LIFT_RIGHT, - power);
}


int liftPower;
void setLift() {

  if(joystickGetDigital(1,5,JOY_DOWN) && joystickGetDigital(1,6,JOY_DOWN))
    liftPower = 0;
  else if(joystickGetDigital(1,5,JOY_DOWN))
    liftPower = -127;
  else if(joystickGetDigital(1,6,JOY_DOWN))
    liftPower = 127;
  else
    liftPower = 0;

  lift(liftPower);
}
