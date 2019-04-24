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
        LedStepLeft(); // Timer0Interrupts_Init(250000, &LedStepLeft);
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
        LedStepRight(); // Timer0Interrupts_Init(250000, &LedStepRight)
      }
      break;
  }
}

int main (){
  unsigned int iMainLoopCtr;
  LedInit();
  KeyboardInit();
  //InitTimer0Match0(100000);
  Timer0Interrupts_Init(500000, &Automat); //co 0.5 sekundy

  while(1){
    //Automat();
    //WaitOnTimerMatch0();
    iMainLoopCtr++;
  }
}
