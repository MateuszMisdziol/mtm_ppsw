#include "led.h"
#include "keyboard.h"

enum LedState {LED_LEFT, LED_RIGHT};
enum LedState eLedState = LED_LEFT;

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
      case LED_LEFT:
        eLedState = LED_RIGHT;
        LedStepRight();
        break;
      case LED_RIGHT:
        eLedState = LED_LEFT;
        LedStepLeft();
        break;
      default:
        break;
    }
  }
}

