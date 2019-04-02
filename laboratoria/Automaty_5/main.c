#include "led.h"
#include "keyboard.h"

enum LedState {STATE_RIGHT, STATE_STOP};
enum LedState eLedState = STATE_RIGHT;

void Delay(unsigned int uiTimer){
  
  unsigned int uiLoopCounter;
  
  for(; uiTimer>0; --uiTimer){
    for(uiLoopCounter=0; uiLoopCounter<2418; ++uiLoopCounter){}
  }
}

int main(void){

  LedInit();
  KeyboardInit();

  while(1){
    
    Delay(250);
    
    switch(eLedState){
      case STATE_RIGHT:
        if(eKeyboardRead() == BUTTON_1){
          eLedState = STATE_STOP;
        }
        else{
          eLedState = STATE_RIGHT;
          LedStepRight();
        }
        break;
      case STATE_STOP:
        if(eKeyboardRead() == BUTTON_2){
          eLedState = STATE_RIGHT;
        }
        else{
          eLedState = STATE_STOP;
        }
        break;
      default:
        break;
    }
  }
}
