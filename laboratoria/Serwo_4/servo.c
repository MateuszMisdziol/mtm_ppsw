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
  if((IO0PIN & DETECTOR_bm) == 1){
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
        LedStepRight();  // tu moze ma byc left
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
  
  uiServoFrequency = ((1/uiServoFrequency) * 1000000);  // zamiana Hz na mikrosekundy
  sServo.eState = CALLIB;
  LedInit();
  DetectorInit();
  Timer0Interrupts_Init(uiServoFrequency, &ServoAutomat);
}

void ServoCallib(void){
  sServo.eState = CALLIB;
  //while(eReadDetector()==INACTIVE); moze cos takiego ma byc
}

void ServoGoTo(unsigned int uiPosition){
  sServo.uiDesiredPosition = uiPosition;
  //sServo.eState = IN_PROGRESS; tu moze to
}
