#include "led.h"
#include "keyboard.h"

enum LedState {STATE_LEFT, STATE_RIGHT};
enum LedState eLedState = STATE_LEFT;

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
    
    Delay(500);
    
    switch(eLedState){
      case STATE_LEFT:
				LedStepLeft();
				++ucNumberOfMoves;
        if((ucNumberOfMoves%3) == 0){
          eLedState = STATE_RIGHT;
        }
        else{
          eLedState = STATE_LEFT; 
        }
        break;
      case STATE_RIGHT:
				LedStepRight();
				++ucNumberOfMoves;
        if((ucNumberOfMoves%3) == 0){
          eLedState = STATE_LEFT;
        }
        else{
          eLedState = STATE_RIGHT; 
        }
      default:
        break;
    }
  }
}

