#include "led.h"
#include "keyboard.h"
#include "timer.h"

void Delay(unsigned int uiTimer){
  
  unsigned int uiLoopCounter;
  
  for(; uiTimer>0; --uiTimer){
    for(uiLoopCounter=0; uiLoopCounter<2418; ++uiLoopCounter){}
  }
}

int main(void){

  LedInit();
  KeyboardInit();
  InitTimer0();
  WaitOnTimer0(5);
  
  while(1){
    
    Delay(500);
    
    switch(eKeyboardRead()){
      case BUTTON_1:
        LedStepRight();
        break;
      case BUTTON_2:
        LedStepLeft();
        break;
      case BUTTON_3:
        break;
      case BUTTON_4:
        break;
      case RELASED:
        break;
      default:
        break;
    }
  }
}

