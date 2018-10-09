
#include "main.h"


void pancake(int power) {
  printf("%d\n", power);
  motorSet(PANCAKE, power);
}

bool pancakeFlippedZero() {
  return analogRead(PANCAKE_PEN) < 75;
}

bool pancakeFlippedPi() {
  return analogRead(PANCAKE_PEN) > 2750;
}

bool power_max = false;
int power_timer = 0;
int changePower() {

  if(joystickGetDigital(1, 8, JOY_UP)) {
    if(power_max && power_timer > 20) {
      power_max = false;
      power_timer = 0;
    }
    else if(power_timer > 20) {
      power_max = true;
      power_timer = 0;
    }
  }

  power_timer++;

  print( power_max ? "true\n" :"false \n");
  if(power_max)
    return 115;
  return 50;
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

bool flipping = false;
int power = 63;

void setPancake() {
  // flips the claw while driving/lifting/etc
    if(joystickGetDigital(1, 8, JOY_DOWN))
      pancake(-changePower());
    else if(joystickGetDigital(1, 8, JOY_RIGHT))
      pancake(changePower());
    else
      pancake(0);


}

////////////////////////////////////////////////////////////

void flipPancake() {
      // flips the claw while doing nothing else
      int stop = 0;
      if(analogRead(PANCAKE_PEN) < 100) {
        while(stop < 6){
          motorSet(PANCAKE, 60);
          if(analogRead(PANCAKE_PEN) < 1725)
            stop++;
        }
      }
      if(analogRead(PANCAKE_PEN) > 1700) {
        while(stop < 6){
          motorSet(PANCAKE, 60);
          if(analogRead(PANCAKE_PEN) > 25)
            stop++;
        }
      }
}
