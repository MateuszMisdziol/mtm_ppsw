#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "string.h"


int main(){
  
  extern char cOdebranyZnak;
	char tab_pom[10];
	
	char cStringCallib[] = "callib";
	char cStringLeft[] = "left";
	char cStringRight[] = "right";
	
  KeyboardInit();
  ServoInit(50);
  UART_InitWithInt(9600);



  while(1){
      
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
		}
  }
}
