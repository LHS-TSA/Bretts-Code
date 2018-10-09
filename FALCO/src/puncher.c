
#include "main.h"

void puncher(int power) {
  motorSet(PUNCH_TOP, -power);
  motorSet(PUNCH_BOT, -power);
}



bool isReady() {
  return digitalRead(PUNCHER_LIMIT_SWITCH);
}


int shoot_timer = 0;
bool shooting = false;
void setPuncher () {
    // flips the claw while driving/lifting/etc
      if(joystickGetDigital(1,7,JOY_RIGHT) && shooting == false &&
      shoot_timer > 25) {
        shooting = true;
        shoot_timer = 0;
      }

      if((!isReady() && shoot_timer > 75) ||
        (joystickGetDigital(1,7,JOY_RIGHT) && shoot_timer > 2000)) {
        shooting = false;
        shoot_timer = 0;
      }


      if(shooting) {
        puncher(127);
      }
      else
        puncher(0);

      shoot_timer++;

  }

  bool timer_started = false;;
  int auton_shoot_timer = 0;
  void shootPuncher() {
    // flips the claw while doing nothing else
    // used for the starting positions
      while(auton_shoot_timer < 1500) { //isReady() || auton_shoot_timer < 11000
        if(isReady())
          timer_started = true;
        if(timer_started);
        auton_shoot_timer++;
        puncher(127);
        delay(2);
      }

      timer_started = false;
      puncher(0);
      auton_shoot_timer = 0;

  }
