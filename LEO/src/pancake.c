
#include "main.h"


void pancake(int power) {
  motorSet(PANCAKE, power);
}

bool pancakeFlippedZero() {
  return analogRead(PANCAKE_PEN) < 75;
}

bool pancakeFlippedPi() {
  return analogRead(PANCAKE_PEN) > 2750;
}


/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

bool clockwise = true;
bool flipping = false;
int power = 0, flipping_timer = 0;
bool setPancake() {
  // flips the claw while driving/lifting/etc

    if(flipping) {

      if(flipping_timer > 30) {
        flipping_timer = power = 0;
        flipping = false;

        if(clockwise)
          clockwise = false;
        else
          clockwise = true;
      }

      else {
        flipping_timer++;
        if(power > 0)
          power -= 4;
        else
          power += 4;
      }
    }
    else {
      if(clockwise)
        power = 127;
      else
        power = -127;

      flipping = true;
    }

    pancake(power);
    return flipping;
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
