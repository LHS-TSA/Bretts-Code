
#include "main.h"

char screen = 'c';
int reset = 0;

void display() {
  lcdClear(uart1);

  // screen declared in main
  switch(lcdReadButtons(uart1)) {
    case BUTTONRIGHT:
      screen = 'l';
      break;
    case BUTTONCENT:
      if(screen == 'c' && reset > 150){
        gyroReset(gyro);
        reset = 0;
      }
      else if(screen != 'c'){
        screen = 'c';
        reset = 0;
      }
      else
        reset++;
      break;
    case BUTTONLEFT:
      if(screen == 'r' && reset > 150){
        encoderReset(right);
        encoderReset(left);
        reset = 0;
      }
      else if(screen != 'r'){
        screen = 'r';
        reset = 0;
      }
      else
        reset++;
      break;
  }

  switch(screen) {
    case 'l':
      lcdPrint(uart1,1,"Battery = %f", powerLevelMain()/1.0);
      break;
    case 'c':
      lcdPrint(uart1,1, "Gyro: %d",gyroGet(gyro));
      break;
    case 'r':
      lcdPrint(uart1,1,"E Right = %d",encoderGet(right));
      lcdPrint(uart1,2,"E Left = %d", encoderGet(left));
      break;
  }

}

void displayGyro() {
  lcdClear(uart1);
  lcdPrint(uart1,1,"%d",gyroGet(gyro));
}

void displayEncoders() {
  lcdClear(uart1);
  lcdPrint(uart1,1,"E Right = %d",encoderGet(right));
  lcdPrint(uart1,2,"E Left = %d", encoderGet(left));
}

void displayInt(int value1,int value2) {
  lcdClear(uart1);
  lcdPrint(uart1,1,"%d",value1);
  lcdPrint(uart1,2,"%d",value2);
}
