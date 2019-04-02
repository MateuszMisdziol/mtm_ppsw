#include "led.h"
#include "keyboard.h"

//git test

enum LedState {STATE_LEFT, STATE_RIGHT, STATE_STOP, STATE_STEP_5};
enum LedState eLedState = STATE_STOP;

unsigned char ucStepCounter = 0;

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
      case STATE_STOP:
        if(eKeyboardRead() == BUTTON_1){
          eLedState = STATE_LEFT;
        }
        else if(eKeyboardRead() == BUTTON_3){
          eLedState = STATE_RIGHT;
        }
        else{
          eLedState = STATE_STOP;
        }
        break;
      case STATE_LEFT:
        if(eKeyboardRead() == BUTTON_2){
          eLedState = STATE_STEP_5;
        }
        else{
          eLedState = STATE_LEFT;
          LedStepLeft();
        }
        break;
      case STATE_RIGHT:
        if(eKeyboardRead() == BUTTON_2){
          eLedState = STATE_STOP;
        }
        else{
          eLedState = STATE_RIGHT;
          LedStepRight();
        }
        break;
      case STATE_STEP_5:
        if(ucStepCounter == 5){
          eLedState = STATE_STOP;
          ucStepCounter = 0;
        }
        else{
          eLedState = STATE_STEP_5;
          LedStepLeft();
          ucStepCounter++;
        }
        break;
      default:
        break;
    }
  }
}
