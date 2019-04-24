#include "timer_interrupts.h"
#include "timer.h"
#include "led.h"
#include "keyboard.h"

enum LedState {STATE_LEFT, STATE_RIGHT, STATE_STOP};

enum LedState eLedState = STATE_STOP;

void Automat(void){
  
  switch(eLedState){
    
    case STATE_LEFT:
      if(eKeyboardRead() == BUTTON_2){
        eLedState = STATE_STOP;
      }
      else{
        eLedState = STATE_LEFT;
        LedStepLeft();
      }
      break;
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
    case STATE_RIGHT:
      if(eKeyboardRead() == BUTTON_2){
        eLedState = STATE_STOP;
      }
      else{
        eLedState = STATE_RIGHT;
        LedStepRight();
      }
      break;
  }
}

int main (){
  unsigned int iMainLoopCtr;
  LedInit();
  KeyboardInit();
  Timer0Interrupts_Init(20000, &Automat);
	Timer1Interrupts_Init(50000, &Automat);

  while(1){
    iMainLoopCtr++;
  }
}
