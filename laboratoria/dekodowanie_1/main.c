#include "keyboard.h"
#include "servo.h"
#include "uart.h"
//#include "led.h"

int main(){
  
  extern char cOdebranyZnak;
  KeyboardInit();
  ServoInit(50);
  UART_InitWithInt(9600);



  while(1){
      
    if(eReciever_GetStatus() == READY){
      
    }
  }
}
