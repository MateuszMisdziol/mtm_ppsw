#include <LPC21xx.H>
#include "ad_converter.h"

#define P027_AIN1_ADC_PIN (1<<22)   // ustawienie pinu
// AD CONTROL REGISTER
#define CHANNEL_AIN0 (1<<0)         // kanal pierwszy
#define CLOCK_DIVDER 0x0000E00      // ustawienie czestotliwosci na 4,5MHz
#define AD_ENABLE (1<<21)           // wlaczenie przetwornika ad
#define START_AD_CONVERSION (1<<24) // start przetwornika AD
// AD DATA REGISTER
#define 

void AD_Init(void){
  
  PINSEL1 = PINSEL1 | P027_AIN1_ADC_PIN;
  ADCR = CHANNEL_AIN0 | CLOCK_DIVDER | AD_ENABLE; //0x1200E01
}

