#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"


int main(){
  
  int iCounter;
  
  //KeyboardInit();
  //ServoInit(50);
  //UART_InitWithInt(9600);
  //Transmiter_SendString("test123");   ZADANIE 2

  while(1){
    
    // ZADANIE 4
    
    for(iCounter = 0; iCounter != 65535; iCounter++){
      char cUARTString[15] = "licznik ";
      AppendUIntToString(iCounter, cUARTString);
      
      if(Transmiter_GetStatus() == FREE){
        Transmiter_SendString(cUARTString);
      }
  }
    
    /*  ZADANIE 3
    if(Transmiter_GetStatus() == FREE){
      Transmiter_SendString("test123");
    }*/

  }
}
