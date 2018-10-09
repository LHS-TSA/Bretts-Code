#include "main.h"


void intake(int power) {
  motorSet(INTAKE, -power);
}


int button_timer = 151;
bool intaking = false;
int intake_power = -127;
void setIntake() {
  if(joystickGetDigital(1, 8, JOY_RIGHT)) {
    if(intaking && button_timer > 20) {
      intaking = false;
      button_timer = 0;
    }
    else if(button_timer > 20) {
      intaking = true;
      button_timer = 0;
      intake_power = -127;
    }
  }

  if(joystickGetDigital(1, 8, JOY_UP)) {
    if(intaking && button_timer > 20) {
      intaking = false;
      button_timer = 0;
    }
    else if(button_timer > 20) {
      intaking = true;
      button_timer = 0;
      intake_power = 127;
    }
  }


  if(intaking)
    intake(intake_power);
  else
    intake(0);

  button_timer++;
}
