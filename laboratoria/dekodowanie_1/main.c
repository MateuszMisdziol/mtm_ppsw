#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"


int main(){
  
  char cReceivedString[RECIVER_SIZE];
  //unsigned char uiServoPosition;
  
  KeyboardInit();
  ServoInit(50);
  UART_InitWithInt(9600);

  while(1){

    //ZADANIE 3
    if(eReciever_GetStatus() == READY){
      Reciever_GetStringCopy(cReceivedString);
      DecodeMsg(cReceivedString);
      
      if((ucTokenNr != 0) && (asToken[0].eType == KEYWORD)){
        switch(asToken[0].uValue.eKeyword){
          case CALLIB:
            ServoCallib();
          break;
          case GOTO:
            if(asToken[1].eType == NUMBER){
            ServoGoTo(asToken[1].uValue.uiNumber); //uiServoPosition +
            //uiPreviusPos = uiPreviusPos + asToken[1].uValue.uiNumber; //zobaczyc czy potrzebne raczej nie bo to do czegos innego bylo
            }
          break;
        }
      }
    }
    

  }
}
