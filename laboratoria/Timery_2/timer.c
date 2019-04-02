#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLED (1<<0)
#define COUNTER_RESET (1<<1)
#define RESET_ON_MR0 (1<<1)
#define INTERRUPT_ON_MR0 (1<<0)

void InitTimer0(void){
  T0TCR = T0TCR | COUNTER_ENABLED;
}

void WaitOnTimer0(unsigned int uiTimer){
  T0TCR = T0TCR | COUNTER_RESET;
  //T0TCR = T0TCR & (~(COUNTER_RESET)); zerowanie flagi rejestru, sprawdzic czy potrzebne
  
  while(T0TC != (15*uiTimer)){}
}

void InitTimer0Match0(unsigned int uiDelayTime){
  T0MR0 = 15*uiDelayTime;
  T0MCR = T0MCR | RESET_ON_MR0;
  T0MCR = T0MCR | INTERRUPT_ON_MR0;
  
  //T0MCR = T0MCR | (RESET_ON_MR0 | INTERRUPT_ON_MR0); lub tak:
  
  T0TCR = T0TCR | COUNTER_RESET;
  //T0TCR = T0TCR & (~(COUNTER_RESET)); zerowanie flagi rejestru, sprawdzic czy potrzebne
  T0TCR = T0TCR | COUNTER_ENABLED;
  
  //mozna sprobowac to polaczyc w jedna instrukcje, sprawdzic czy bedzie dzialac
  //T0TCR = T0TCR | (COUNTER_ENABLED | COUNTER_RESET);
}

void WaitOnTimerMatch0(){
  while((T0IR & INTERRUPT_ON_MR0) == 0){}
    
  T0IR = INTERRUPT_ON_MR0;
}
