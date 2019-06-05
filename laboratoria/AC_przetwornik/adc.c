#include <LPC21xx.H>
#include "adc.h"

void AD_Init(void){
  
  PINSEL1 = PINSEL1 | P027_AIN1_ADC_PIN;
  ADCR = CHANNEL_AIN0 | AD_ENABLE; //0x1200E01
}

unsigned int uiReadADC(void){

  unsigned int uiADConverterData;
	
	ADCR |= START_AD_CONVERSION;  //sprawdzic bo chyba tu nie dziala
	
  uiADConverterData = (ADDR & AD_DATA_MASK);
	uiADConverterData = (uiADConverterData>>6);
  
  return (uiADConverterData);
}

unsigned int uiCompleteAD(void){
	
	if((ADDR & AD_DONE_REGISTER) == AD_DONE_REGISTER){
		return 1;
	}
	else{
		return 0;
	}
}
