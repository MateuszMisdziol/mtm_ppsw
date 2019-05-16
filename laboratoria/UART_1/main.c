#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"

int main(){
  
	unsigned char ucServoPosition;
  extern char cOdebranyZnak;
  KeyboardInit();
  ServoInit(50);
  UART_InitWithInt(9600);


  while(1){
      
          //CWICZENIE 4
    
    switch(cOdebranyZnak){
      case '1':
        ServoGoTo(12*ucServoPosition);
				ucServoPosition++;
				cOdebranyZnak = '\0';
        break;
      case 'c':
        ServoCallib();
        cOdebranyZnak = '\0';
				ucServoPosition = 0;
      break;
      default:
        break;
    }
    
    
    switch(eKeyboardRead()){
      case BUTTON_1:
        ServoCallib();
        break;
      case BUTTON_2:
        ServoGoTo(90);
        break;
      case BUTTON_3:
        ServoGoTo(180);
        break;
      case BUTTON_4:
        ServoGoTo(270);
        break;
      case RELASED:
        break;
      default:
        break;
    }
  }
}
