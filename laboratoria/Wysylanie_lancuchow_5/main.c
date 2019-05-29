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
  
  //int iCounter;
  
  //WatchInit();
  
  //KeyboardInit();
  //ServoInit(50);
  //Transmiter_SendString("test123");   ZADANIE 2
  char cWatchArray[TRANSMITER_SIZE];
  Timer0Interrupts_Init(1000000, &WatchUpdate);
  UART_InitWithInt(9600);

  while(1){
    
    if(Transmiter_GetStatus() == FREE){
      if(sWatch.fSeccondsValueChanged == 1){
        
        sWatch.fSeccondsValueChanged = 0;
        CopyString("sec", cWatchArray);
        AppendUIntToString(sWatch.ucSecconds, cWatchArray);
        Transmiter_SendString(cWatchArray);
      }
      if(sWatch.fMinutesValueChanged == 1){
        
        sWatch.fMinutesValueChanged = 0;
        CopyString("min", cWatchArray);
        AppendUIntToString(sWatch.ucMinutes, cWatchArray);
        Transmiter_SendString(cWatchArray);
      }
    }
    
    /* ZADANIE 4
    
    for(iCounter = 0; iCounter != 65535; iCounter++){
      char cUARTString[15] = "licznik ";
      AppendUIntToString(iCounter, cUARTString);
      
      if(Transmiter_GetStatus() == FREE){
        Transmiter_SendString(cUARTString);
      }
  }*/
    
    /*  ZADANIE 3
    if(Transmiter_GetStatus() == FREE){
      Transmiter_SendString("test123");
    }*/

  }
}
