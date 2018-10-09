#include "main.h"


void intake(int power) {
  motorSet(INTAKE, power);
}


int button_timer = 151;
bool intaking = false;

void setIntake() {
  if(joystickGetDigital(1, 8, JOY_LEFT)) {
    if(intaking && button_timer > 20) {
      intaking = false;
      button_timer = 0;
    }
    else if(button_timer > 20) {
      intaking = true;
      button_timer = 0;
    }
  }

  if(intaking)
    intake(-127);
  else
    intake(0);

  button_timer++;
}
