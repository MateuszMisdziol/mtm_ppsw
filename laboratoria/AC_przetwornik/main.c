#include <LPC21xx.H>
#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "timer_interrupts.h"

//////////////// ADC ///////////////////

#define P027_AIN1_ADC_PIN (1<<22)   // ustawienie pinu
// AD CONTROL REGISTER
#define CHANNEL_AIN0 (1<<0)         // kanal pierwszy
#define AD_ENABLE (1<<21)           // wlaczenie przetwornika ad
#define START_AD_CONVERSION (1<<24) // start przetwornika AD
// AD DATA REGISTER
#define AD_DONE_REGISTER (1<<31)    // konwersja gotowa
#define AD_DATA_MASK 0x0000FFC0

void AD_Init(void){
  
  PINSEL1 = PINSEL1 | P027_AIN1_ADC_PIN;
  ADCR = CHANNEL_AIN0 | AD_ENABLE; //0x1200E01
}

int ADReturn(unsigned int x){

  unsigned long int uiADConverterData;

  uiADConverterData = (ADDR & AD_DATA_MASK);
  uiADConverterData = (uiADConverterData>>6);
  uiADConverterData = (uiADConverterData / 21);
  
  return (uiADConverterData + x);
}

struct Watch sWatch;

void WatchUpdate(void){
  
  sWatch.ucSecconds++;
  sWatch.fSeccondsValueChanged = 1;
  
  if(sWatch.ucSecconds > 59){
    sWatch.ucMinutes++;
    sWatch.fMinutesValueChanged = 1;
    sWatch.ucSecconds = 0;
  }
  
  if(sWatch.ucMinutes > 59){
    sWatch.ucMinutes = 0;
  }
}


int main(void){
  
  char cTransmiterString[TRANSMITER_SIZE];
  char cReceivedString[RECIVER_SIZE];
  unsigned char fCalcToken;
	unsigned char fIDToken;
	unsigned char fUnKnownCommand;
  
  ServoInit(200);
  Timer0Interrupts_Init(1000000, &WatchUpdate);
  UART_InitWithInt(9600);
  AD_Init();
  

  while(1){
    
    ///////////////// ADC ///////////////////
    
    ADCR |= START_AD_CONVERSION;
   
    /////////// UART ODBIORNIK //////////////
    
    if(eReciever_GetStatus() == READY){
      Reciever_GetStringCopy(cReceivedString);
      DecodeMsg(cReceivedString);
      
      if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
				
				switch(asToken[0].uValue.eKeyword){
					case CALC:
						fCalcToken = 1;
					break;
					case GOTO:
						ServoGoTo(asToken[1].uValue.uiNumber);
					break;
					case CALLIB:
            asToken[1].uValue.uiNumber = 0;
						ServoCallib();
					break;
					case ID:
						fIDToken = 1;
					break;
					default:
						fUnKnownCommand = 1;
					break;
				}
			}
			else{
				fUnKnownCommand = 1;
			}
		}
    else if((ADDR & AD_DONE_REGISTER) == AD_DONE_REGISTER){
      
      ServoGoTo(ADReturn(asToken[1].uValue.uiNumber));
    }
    
    /////////// UART WYSYLANIE //////////////
    
    if(Transmiter_GetStatus() == FREE){
      if(sWatch.fSeccondsValueChanged == 1){
        
        sWatch.fSeccondsValueChanged = 0;
        CopyString("sec ", cTransmiterString);
        AppendUIntToString(sWatch.ucSecconds, cTransmiterString);
				AppendString("\n", cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
      else if(sWatch.fMinutesValueChanged == 1){
        
        sWatch.fMinutesValueChanged = 0;
        CopyString("min ", cTransmiterString);
        AppendUIntToString(sWatch.ucMinutes, cTransmiterString);
				AppendString("\n", cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
      else if(fCalcToken == 1){
        fCalcToken = 0;
        CopyString("CALC ", cTransmiterString);
        AppendUIntToString((asToken[1].uValue.uiNumber) * 2, cTransmiterString);
				AppendString("\n", cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
			else if(fIDToken == 1){
        fIDToken = 0;
        CopyString("ID mateusz\n", cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
			else if(fUnKnownCommand == 1){
        fUnKnownCommand = 0;
        CopyString("unknown_command\n", cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
    }
  }
}
