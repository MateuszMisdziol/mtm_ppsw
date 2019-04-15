#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main(void){

  LedInit();
  KeyboardInit();
  //InitTimer0();
  InitTimer0Match0(1000000);
  
  while(1){
    WaitOnTimerMatch0();
    //WaitOnTimer0(1000000);
		LedStepLeft();
  }
}

