#include "keyboard.h"
#include "servo.h"

int main (){
  
  KeyboardInit();
  ServoInit(100); // 100Hz  tutaj moze 500
  //moze trzeba dodac Servo_Goto(100);

  while(1){
    
    switch(eKeyboardRead()){
      case BUTTON_1:
        ServoCallib();
        break;
      case BUTTON_2:
        ServoGoTo(12);  // albo 50
        break;
      case BUTTON_3:
        ServoGoTo(24);  // 100
        break;
      case BUTTON_4:
        ServoGoTo(36);  // 150
        break;
      default:
        break;
    }
  }
}
