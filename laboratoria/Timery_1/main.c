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
  
  while(1){
    
    WaitOnTimer0(1000000);
    LedStepLeft();    
  }
}

