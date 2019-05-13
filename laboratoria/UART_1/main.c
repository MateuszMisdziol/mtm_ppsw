#include "keyboard.h"
#include "servo.h"
#include "uart.h"
#include "led.h"

int main (){
  
  extern char cOdebranyZnak;
  KeyboardInit();
  LedInit();
  ServoInit(100);
  UART_InitWithInt(9600);

  while(1){
    
    /*switch(cOdebranyZnak){
      case '1':
        ServoGoTo(90);
        break;
      case '2':
        ServoGoTo(180);
        break;
      case '3':
        ServoGoTo(270);
        break;
      case 'c':
        ServoCallib();
      break;
      default:
        break;
    }*/
    
    switch(cOdebranyZnak){
    case '1':
      //ServoGoTo(50*ucServoPosition);
      //cOdebranyZnak='\0';
      //ucServoPosition++;
      break;
    case 'c':
      ServoCallib();
      cOdebranyZnak='\0';
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
