#include <LPC210X.H>
#include "string.h"
#include "uart.h"

/************ UART ************/
// U0LCR Line Control Register
#define mDIVISOR_LATCH_ACCES_BIT                   0x00000080
#define m8BIT_UART_WORD_LENGTH                     0x00000003

// UxIER Interrupt Enable Register
#define mRX_DATA_AVALIABLE_INTERRUPT_ENABLE        0x00000001
#define mTHRE_INTERRUPT_ENABLE                     0x00000002

// UxIIR Pending Interrupt Identification Register
#define mINTERRUPT_PENDING_IDETIFICATION_BITFIELD  0x0000000F
#define mTHRE_INTERRUPT_PENDING                    0x00000002
#define mRX_DATA_AVALIABLE_INTERRUPT_PENDING       0x00000004

/************ Interrupts **********/
// VIC (Vector Interrupt Controller) channels
#define VIC_UART0_CHANNEL_NR  6
#define VIC_UART1_CHANNEL_NR  7

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE                           0x00000020

// USTAWIENIE PINU DLA UARTA
#define P01_RXD_UART0_PIN                          0x00000004    //(1<<2)
#define P00_TXD_UART0_PIN                          0x00000001

////////////// STRUKTURY /////////////////////

struct ReciverBuffer{
  char cData[RECIVER_SIZE];
  unsigned char ucCharCtr;
  enum eReciverStatus eStatus;
};

struct TransmiterBuffer{
  char cData[TRANSMITER_SIZE];
  enum eTransmiterStatus eStatus;
  unsigned char fLastCharacter;
  unsigned char cCharCtr;
};

struct ReciverBuffer sReciverBuffer;
struct TransmiterBuffer sTransmiterBuffer;

////////////// Zmienne globalne ////////////
char cOdebranyZnak;


////////////// FUNKCJE /////////////////
void Reciever_PutCharacterToBuffer(char cCharacter){
  
  if(sReciverBuffer.ucCharCtr > RECIVER_SIZE){
    sReciverBuffer.eStatus = OVERFLOW;
  }
  else if(cCharacter != TERMINATOR){
    sReciverBuffer.cData[sReciverBuffer.ucCharCtr] = cCharacter;
    sReciverBuffer.ucCharCtr++;
  }
  else{
    sReciverBuffer.cData[sReciverBuffer.ucCharCtr] = '\0';
    sReciverBuffer.eStatus = READY;
    sReciverBuffer.ucCharCtr = 0;
  }
}

enum eReciverStatus eReciever_GetStatus(void){

    return sReciverBuffer.eStatus;
}

void Reciever_GetStringCopy(char * ucDestination){
  
  CopyString(sReciverBuffer.cData, ucDestination);
  sReciverBuffer.eStatus = EMPTY;
}

char Transmiter_GetCharacterFromBuffer(void){

  char cCurrentChar = sTransmiterBuffer.cData[sTransmiterBuffer.cCharCtr];
  
  if(cCurrentChar == '\0'){
    
    sTransmiterBuffer.fLastCharacter = 1;
    cCurrentChar = TERMINATOR;
    return cCurrentChar;
  }
  
  if(sTransmiterBuffer.fLastCharacter == 1){
    
    sTransmiterBuffer.fLastCharacter = 0;
    sTransmiterBuffer.eStatus = FREE;
    cCurrentChar = '\0';
    return cCurrentChar;
  }
  
  sTransmiterBuffer.cCharCtr++;
  return cCurrentChar;
}

void Transmiter_SendString(char cString[]){
  
  CopyString(cString, sTransmiterBuffer.cData);
  sTransmiterBuffer.cCharCtr = 0;
  sTransmiterBuffer.eStatus = BUSY;
  U0THR = Transmiter_GetCharacterFromBuffer();
}

enum eTransmiterStatus Transmiter_GetStatus(void){
  
  return sTransmiterBuffer.eStatus;
}

__irq void UART0_Interrupt (void){
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
     cOdebranyZnak = U0RBR;
     Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)  // wyslano znak - nadajnik pusty 
   {
     if(Transmiter_GetStatus() == BUSY){
       U0THR = Transmiter_GetCharacterFromBuffer();
     }
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | P01_RXD_UART0_PIN | P00_TXD_UART0_PIN;                // ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT;              // dlugosc slowa, DLAB = 1
   U0DLL   = (((15000000)/16)/uiBaudRate);                                   // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                                    // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE | mTHRE_INTERRUPT_PENDING;  // wlaczanie flagi przerwania RDA dla UART0

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;                          // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;                  // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);                            // Enable UART 0 Interrupt Channel
}
