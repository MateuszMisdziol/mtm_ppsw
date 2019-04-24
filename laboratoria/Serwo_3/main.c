#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "timer.h"
#include "led.h"
#include "keyboard.h"

#define DETECTOR_bm (1<<10)

/*enum LedState {STATE_LEFT, STATE_RIGHT, STATE_STOP, STATE_CALLIB};

enum LedState eLedState = STATE_CALLIB;

TO CHYBA WYWALAMY*/

enum DetectorState {ACTIVE, INACTIVE};

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

enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo{
  enum ServoState eState;
  unsigned int uiCurrentPosition;
  unsigned int uiDesiredPosition;
};

struct Servo sServo;

//---------------------FUNKCJE-------------------------

void ServoAutomat(void){
  
  switch(sServo.eState){
    case CALLIB:
      if(eReadDetector() == INACTIVE){
        sServo.eState = CALLIB;
        LedStepLeft();
      }
      else{
        sServo.uiCurrentPosition = 0;
        sServo.uiDesiredPosition = 0;
        sServo.eState = IDLE;
      }
      break;
    case IDLE:
      if(sServo.uiCurrentPosition == sServo.uiDesiredPosition){
        sServo.eState = IDLE;
      }
      else{
        sServo.eState = IN_PROGRESS;
      }
      break;
    case IN_PROGRESS:
      if(sServo.uiCurrentPosition > sServo.uiDesiredPosition){
        LedStepRight();
        sServo.uiCurrentPosition--;
        sServo.eState = IN_PROGRESS;
      }
      else if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
        LedStepLeft();
        sServo.uiCurrentPosition++;
        sServo.eState = IN_PROGRESS;
      }
      else if(sServo.uiCurrentPosition == sServo.uiDesiredPosition){
        sServo.eState = IDLE;
      }
      break;
  }
}

void ServoInit(unsigned int uiServoFrequency){
  
  uiServoFrequency = (1/uiServoFrequency) * 1000000;  // zamiana Hz na mikrosekundy
  sServo.eState = CALLIB;
  LedInit();
  KeyboardInit();
  DetectorInit();
  Timer0Interrupts_Init(uiServoFrequency, &ServoAutomat);
}

void ServoCallib(void){
  sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
  sServo.uiDesiredPosition = uiPosition;
}

int main (){
  
  ServoInit(100); // 100Hz

  while(1){
    
    switch(eKeyboardRead()){
      case BUTTON_1:
        ServoCallib();
        break;
      case BUTTON_2:
        ServoGoTo(12);
        break;
      case BUTTON_3:
        ServoGoTo(24);
        break;
      case BUTTON_4:
        ServoGoTo(36);
        break;
      default:
        break;
    }
  }
}
