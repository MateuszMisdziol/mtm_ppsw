#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "timer.h"
#include "led.h"
#include "keyboard.h"

#define DETECTOR_bm (1<<10)

enum State {STATE_LEFT, STATE_RIGHT, STATE_STOP, CALLIB};
enum DetectorState {ACTIVE, INACTIVE};

enum State eState = CALLIB;


void DetectorInit(){
  IO0DIR = IO0DIR & (~DETECTOR_bm); //sprawdzic czy z OR | tez bedzie dzialac
}

enum DetectorState eReadDetector(){
  if((IO0PIN & DETECTOR_bm) == 1){
    return ACTIVE;
  }
  else{
    return INACTIVE;
  }
}

void Automat(void){
  
  switch(eState){
    
    case STATE_LEFT:
      if(eKeyboardRead() == BUTTON_2){
        eState = STATE_STOP;
      }
      else{
        eState = STATE_LEFT;
        LedStepLeft();
      }
      break;
    case STATE_STOP:
      if(eKeyboardRead() == BUTTON_1){
        eState = STATE_LEFT;
      }
      else if(eKeyboardRead() == BUTTON_3){
        eState = STATE_RIGHT;
      }
      else{
        eState = STATE_STOP;
      }
      break;
    case STATE_RIGHT:
      if(eKeyboardRead() == BUTTON_2){
        eState = STATE_STOP;
      }
      else{
        eState = STATE_RIGHT;
        LedStepRight();
      }
      break;
    case CALLIB:
      if(eReadDetector() == ACTIVE){
        eState = STATE_STOP;
      }
      else{
        eState = CALLIB;
        LedStepLeft(); // albo Right nwm sprawdzic trzeba, ma sie obracac przeciwnie do wsk zegara
      }
      break;
  }
}

int main (){
  unsigned int iMainLoopCtr;
  LedInit();
  KeyboardInit();
  Timer0Interrupts_Init(20000, &Automat); // 50Hz (20us)

  while(1){
    iMainLoopCtr++;
  }
}
