#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"
#include "timer_interrupts.h"

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


int main(){
  
	char cTransmiterString[TRANSMITER_SIZE];
  char cReceivedString[RECIVER_SIZE];
  unsigned char fCalcToken;
	unsigned char fIDToken;
	unsigned char fUnKnownCommand;
	
  //KeyboardInit();
	
  ServoInit(50);
  Timer0Interrupts_Init(1000000, &WatchUpdate);
  UART_InitWithInt(9600);

  while(1){
    
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
