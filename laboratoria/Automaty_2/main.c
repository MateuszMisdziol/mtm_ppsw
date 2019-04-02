#include "led.h"
#include "keyboard.h"

enum LedState {STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
enum LedState eLedState = STATE0;

void Delay(unsigned int uiTimer){
  
  unsigned int uiLoopCounter;
  
  for(; uiTimer>0; --uiTimer){
    for(uiLoopCounter=0; uiLoopCounter<2418; ++uiLoopCounter){}
  }
}

int main(void){

  LedInit();
  KeyboardInit();
  
  //pytanie sprawdzic czy najpierw zmieniac stan
  //czy najpierw wywolywac funkcje LedStepLeft();
  //wydaje mi sie ze najpierw funkcja ale sprawdzic
  //to lepiej na plytce
  
  while(1){
    
    Delay(250);
    
    switch(eLedState){
      case STATE0:
        eLedState = STATE1;
        LedStepLeft();
        break;
      case STATE1:
        eLedState = STATE2;
        LedStepLeft();
        break;
      case STATE2:
        eLedState = STATE3;
        LedStepLeft();
        break;
      case STATE3:
        eLedState = STATE4;
        LedStepRight();
        break;
      case STATE4:
        eLedState = STATE5;
        LedStepRight();
        break;
      case STATE5:
        eLedState = STATE0;
        LedStepRight();
        break;
      default:
        break;
    }
  }
}

