#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "string.h"
#include "command_decoder.h"


int main(){
  
  char cReceivedString[RECIVER_SIZE];
  //char tab_pom[10];
	
	//char cStringCallib[] = "callib";
	//char cStringLeft[] = "left";
	//char cStringRight[] = "right";
	
  KeyboardInit();
  //ServoInit(50);
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
            ServoGoTo(asToken[1].uValue.uiNumber);
          break;
        }
      }
    }
    
    
    
    /* ZADANIE 2
    if(eReciever_GetStatus() == READY){
      Reciever_GetStringCopy(tab_pom);
    }
		
		if(eCompareString(tab_pom, cStringCallib) == EQUAL){
			ServoCallib();
		}
		else if(eCompareString(tab_pom, cStringLeft) == EQUAL){
			ServoGoTo(50);
		}
		else if(eCompareString(tab_pom, cStringRight) == EQUAL){
			ServoGoTo(150);
    }*/
  }
}
