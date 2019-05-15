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
      
          /*CWICZENIE 2
    
    switch(cOdebranyZnak){
    case '1':
      LedOn(0);
    break;
    case '2':
      LedOn(1);
    break;
    case '3':
      LedOn(2);
    break;
    case '4':
      LedOn(3);
    break;
    case 'c':
      LedOn(10);
      cOdebranyZnak = '\0';
      break;
    default:
      break;
    }*/
    
          /*CWICZENIE 3
    
    switch(cOdebranyZnak){
      case '1':
        ServoGoTo(17);  //50 90st.
        break;
      case '2':
        ServoGoTo(30);  //180 180st.
        break;
      case '3':
        ServoGoTo(55);  //150 270st.
        break;
      case 'c':
        ServoCallib();
      break;
      default:
        break;
    }*/
    
          //CWICZENIE 4
    
    switch(cOdebranyZnak){
      case '1':
        ServoGoTo(17);  //50  90st.
        cOdebranyZnak = '\0';
        break;
      case 'c':
        ServoCallib();
        cOdebranyZnak = '\0';
      break;
      default:
        break;
    }
    
    /*NIE USUWAC NWM CZEMU :D
    
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
    }*/
  }
}
