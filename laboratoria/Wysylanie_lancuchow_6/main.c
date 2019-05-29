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
  
  //KeyboardInit();
  //ServoInit(50);

  char cTransmiterString[TRANSMITER_SIZE];
  char cReceivedString[RECIVER_SIZE];
  unsigned char fCalcToken;
  
  Timer0Interrupts_Init(1000000, &WatchUpdate);
  UART_InitWithInt(9600);

  while(1){
    
    if(eReciever_GetStatus() == READY){
      Reciever_GetStringCopy(cReceivedString);
      DecodeMsg(cReceivedString);
      
      if((ucTokenNr != 0) && (asToken[0].uValue.eKeyword == CALC)){
        fCalcToken = 1;
      }
    }
    
    
    if(Transmiter_GetStatus() == FREE){
      if(sWatch.fSeccondsValueChanged == 1){
        
        sWatch.fSeccondsValueChanged = 0;
        CopyString("sec ", cTransmiterString);
        AppendUIntToString(sWatch.ucSecconds, cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
      else if(sWatch.fMinutesValueChanged == 1){
        
        sWatch.fMinutesValueChanged = 0;
        CopyString("min ", cTransmiterString);
        AppendUIntToString(sWatch.ucMinutes, cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
      else if(fCalcToken == 1){
        fCalcToken = 0;
        CopyString("calc ", cTransmiterString);
        AppendUIntToString((asToken[1].uValue.uiNumber * 2), cTransmiterString);
        Transmiter_SendString(cTransmiterString);
      }
    }
  }
}
