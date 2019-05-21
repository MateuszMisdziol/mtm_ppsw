#include <LPC210X.H>
#include "uart.h"
#include "string.h"

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

////////////// STRUKTURY /////////////////////

struct ReciverBuffer{
  char cData[RECIVER_SIZE];
  unsigned char ucCharCtr;
  enum eReciverStatus eStatus;
};

struct ReciverBuffer sReciverBuffer;

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

__irq void UART0_Interrupt (void){
   // jesli przerwanie z odbiornika (Rx)
   
   unsigned int uiCopyOfU0IIR=U0IIR; // odczyt U0IIR powoduje jego kasowanie wiec lepiej pracowac na kopii

   if      ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mRX_DATA_AVALIABLE_INTERRUPT_PENDING) // odebrano znak
   {
     cOdebranyZnak = U0RBR;
     Reciever_PutCharacterToBuffer(cOdebranyZnak);
   } 
   
   if ((uiCopyOfU0IIR & mINTERRUPT_PENDING_IDETIFICATION_BITFIELD) == mTHRE_INTERRUPT_PENDING)              // wyslano znak - nadajnik pusty 
   {
      // narazie nic nie wysylamy
   }

   VICVectAddr = 0; // Acknowledge Interrupt
}

////////////////////////////////////////////
void UART_InitWithInt(unsigned int uiBaudRate){

   // UART0
   PINSEL0 = PINSEL0 | P01_RXD_UART0_PIN;                       // ustawic pina na odbiornik uart0
   U0LCR  |= m8BIT_UART_WORD_LENGTH | mDIVISOR_LATCH_ACCES_BIT; // dlugosc slowa, DLAB = 1
   U0DLL   = (((15000000)/16)/uiBaudRate);                      // predkosc transmisji
   U0LCR  &= (~mDIVISOR_LATCH_ACCES_BIT);                       // DLAB = 0
   U0IER  |= mRX_DATA_AVALIABLE_INTERRUPT_ENABLE;               // wlaczanie flagi przerwania RDA dla UART0

   // INT
   VICVectAddr1  = (unsigned long) UART0_Interrupt;             // set interrupt service routine address
   VICVectCntl1  = mIRQ_SLOT_ENABLE | VIC_UART0_CHANNEL_NR;     // use it for UART 0 Interrupt
   VICIntEnable |= (0x1 << VIC_UART0_CHANNEL_NR);               // Enable UART 0 Interrupt Channel
}
