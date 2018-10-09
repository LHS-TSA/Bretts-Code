
#include "main.h"

void puncher(int power) {
  motorSet(PUNCH_TOP, power);
  motorSet(PUNCH_BOT, power);
}



bool isReady() {
  return digitalRead(PUNCHER_LIMIT_SWITCH);
}


int shoot_timer = 0;
bool shooting = false;
void setPuncher () {
    // flips the claw while driving/lifting/etc

      if(joystickGetDigital(1,8,JOY_DOWN) && shooting == false &&
          shoot_timer > 25) {
        shooting = true;
        shoot_timer = 0;
      }

      if((!isReady() && shoot_timer > 75) ||
        (joystickGetDigital(1,8,JOY_DOWN) && shoot_timer > 125)) {
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

//bool auton_shooting = false;
int auton_shoot_timer = 0;
void shootPuncher() {
  // flips the claw while doing nothing else
  // used for the starting positions
    while(isReady() || auton_shoot_timer < 8000) {
      print(isReady() ? "true " : "false ");
      printf("%d \n", auton_shoot_timer);
      auton_shoot_timer++;
      puncher(127);
    }
    print(isReady() ? "FINAL : true " : "FINAL: false ");
    printf("%d \n", auton_shoot_timer);
    puncher(0);
    auton_shoot_timer = 0;

}
