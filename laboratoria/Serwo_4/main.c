#include "keyboard.h"
#include "servo.h"

int main (){
  
  KeyboardInit();
  ServoInit(100); // 100Hz

  while(1){
    
    switch(eKeyboardRead()){
      case BUTTON_1:
        ServoCallib();
        break;
      case BUTTON_2:
        ServoGoTo(12);
        break;
      case BUTTON_3:
        ServoGoTo(24);
        break;
      case BUTTON_4:
        ServoGoTo(36);
        break;
      default:
        break;
    }
  }
}
