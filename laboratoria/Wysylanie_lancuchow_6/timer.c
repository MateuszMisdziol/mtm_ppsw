#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLED (1<<0)
#define COUNTER_RESET (1<<1)
#define RESET_ON_MR0 (1<<1)
#define INTERRUPT_ON_MR0 (1<<0)
#define MR0_INTERRUPT (1<<0)


void InitTimer0(void){
  T0TCR = COUNTER_ENABLED;
}

void WaitOnTimer0(unsigned int uiTime){
  T0TCR = T0TCR | COUNTER_RESET;
  T0TCR = T0TCR & (~COUNTER_RESET); //POWROT DO 0 NA BICIE RESETU
  
  while(T0TC < (uiTime*15)){} 
}

void InitTimer0Match0(unsigned int uiDelayTime){
  T0MR0 = (15*uiDelayTime);
  T0MCR = T0MCR | RESET_ON_MR0;
  T0MCR = T0MCR | INTERRUPT_ON_MR0;
  
  T0TCR = T0TCR | COUNTER_RESET;
  T0TCR = COUNTER_ENABLED;
}

void WaitOnTimerMatch0(void){
  
	while((T0IR & MR0_INTERRUPT) == 0){}  
  T0IR = MR0_INTERRUPT;
}
