#include "led.h"
#include "keyboard.h"

enum LedState {STATE_STOP, STATE_RIGHT};
enum LedState eLedState = STATE_STOP;

unsigned char ucNumberOfMoves = 0;

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
				LedStepRight();
        if(ucNumberOfMoves%3 == 0){
          eLedState = STATE_STOP;
        }
        else{
          eLedState = STATE_RIGHT;
        }
				++ucNumberOfMoves;
				Delay(100);
        break;
      case STATE_STOP:
        if(eKeyboardRead() == BUTTON_1){
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

