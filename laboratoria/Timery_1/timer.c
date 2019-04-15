#include <LPC21xx.H>
#include "timer.h"

#define COUNTER_ENABLED (1<<0)
#define COUNTER_RESET (1<<1)


void InitTimer0(void){
  T0TCR = COUNTER_ENABLED;
}

void WaitOnTimer0(unsigned int uiTime){
  T0TCR = T0TCR | COUNTER_RESET;
  T0TCR = T0TCR & (~COUNTER_RESET); //POWROT DO 0 NA BICIE RESETU
  
  while(T0TC < (uiTime*15)){} 
}
