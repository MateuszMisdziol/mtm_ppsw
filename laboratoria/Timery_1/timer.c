#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLED (1<<0)
#define COUNTER_RESET (1<<1)

void InitTimer0(void){
  T0TCR = COUNTER_ENABLED;
}

void WaitOnTimer0(unsigned int uiTimer){
  T0TCR = COUNTER_RESET;
  //T0TCR = T0TCR & (~(COUNTER_RESET)); zerowanie flagi rejestru, sprawdzic czy potrzebne
  
  while(T0TC != (15*uiTimer)){}
}
