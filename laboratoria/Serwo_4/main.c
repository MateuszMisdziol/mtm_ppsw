#include "keyboard.h"
#include "servo.h"

int main (){
  
  KeyboardInit();
  ServoInit(50);
  //ServoGoTo(15);
  //ServoGoTo(5);

  while(1){
    
    switch(eKeyboardRead()){
      case BUTTON_1:
        ServoCallib();
        break;
      case BUTTON_2:
        ServoGoTo(15);
        break;
      case BUTTON_3:
        ServoGoTo(30);
        break;
      case BUTTON_4:
        ServoGoTo(50);
        break;
      default:
        break;
    }
  }
}
