#include <LPC21xx.H>
#include "keyboard.h"

#define BUTT1_bm (1<<4)
#define BUTT2_bm (1<<5)
#define BUTT3_bm (1<<6)
#define BUTT4_bm (1<<7)

enum KeyboardState eKeyboardRead(void){
  
  if((IO0PIN&BUTT1_bm) == 0){
    return BUTTON_1;
  }
  else if((IO0PIN&BUTT2_bm) == 0){
    return BUTTON_2;
  }
  else if((IO0PIN&BUTT3_bm) == 0){
    return BUTTON_3;
  }
  else if((IO0PIN&BUTT4_bm) == 0){
    return BUTTON_4;
  }
  else{
    return RELASED;
  }
}

void KeyboardInit(void){
  IO0DIR = IO0DIR & (~(BUTT1_bm | BUTT2_bm | BUTT3_bm | BUTT4_bm));
}
