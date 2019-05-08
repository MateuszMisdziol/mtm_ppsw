#include <LPC21xx.H>
#include "timer_interrupts.h"
#include "led.h"
#include "servo.h"

#define DETECTOR_bm (1<<10)

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

struct Servo{
  enum ServoState eState;
  unsigned int uiCurrentPosition;
  unsigned int uiDesiredPosition;
};

struct Servo sServo;

//***********FUNKCJE***************

void DetectorInit(void){
  IO0DIR = IO0DIR & (~DETECTOR_bm); //sprawdzic czy z OR | tez bedzie dzialac
}

enum DetectorState eReadDetector(void){
  if((IO0PIN & DETECTOR_bm) == 0){
    return ACTIVE;
  }
  else{
    return INACTIVE;
  }
}

void ServoAutomat(void){
  
  switch(sServo.eState){
    case CALLIB:
      if(eReadDetector() == INACTIVE){
        sServo.eState = CALLIB;
        LedStepLeft();
      }
      else{
        //LedStepLeft(); sprawdzic
        sServo.uiCurrentPosition = 0;
        sServo.uiDesiredPosition = 0;
        sServo.eState = IDLE;
      }
      break;
    case IDLE:
      if(sServo.uiDesiredPosition != sServo.uiCurrentPosition){
        sServo.eState = IN_PROGRESS;
      }
      else{
        sServo.eState = IDLE;
      }
      break;
    case IN_PROGRESS:
      if(sServo.uiDesiredPosition > sServo.uiCurrentPosition){
        LedStepRight();  // tu moze ma byc left
        sServo.uiCurrentPosition++;
        sServo.eState = IN_PROGRESS;
      }
      else if(sServo.uiDesiredPosition < sServo.uiCurrentPosition){
        LedStepLeft();
        sServo.uiCurrentPosition--;
        sServo.eState = IN_PROGRESS;
      }
      else{
        sServo.eState = IDLE;
      }
      break;
  }
}

void ServoInit(unsigned int uiServoFrequency){
  
  uiServoFrequency = ((1/uiServoFrequency) * 1000000);  // zamiana Hz na mikrosekundy
  sServo.eState = CALLIB;
  LedInit();
  DetectorInit();
  Timer0Interrupts_Init(uiServoFrequency, &ServoAutomat);
}

void ServoCallib(void){
  sServo.eState = CALLIB;
}

void ServoGoTo(unsigned int uiPosition){
  sServo.uiDesiredPosition = uiPosition;
}
