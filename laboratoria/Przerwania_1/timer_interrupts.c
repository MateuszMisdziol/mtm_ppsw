#include <LPC21xx.H>

// TIMER
#define mCOUNTER_ENABLE 0x00000001 // 1<<0
#define mCOUNTER_RESET  0x00000002 // 1<<1

// CompareMatch
#define mINTERRUPT_ON_MR0 0x00000001 // 1<<0
#define mRESET_ON_MR0     0x00000002 // 1<<1
#define mMR0_INTERRUPT    0x00000001 // 1<<0

// VIC (Vector Interrupt Controller) VICIntEnable
#define VIC_TIMER0_CHANNEL_NR 4

// VICVectCntlx Vector Control Registers
#define mIRQ_SLOT_ENABLE 0x00000020  //wpisanie jedynki do bitu 5 sluzy do wlaczenia slotu IRQ

//globalny wskaznik na funkcje 
void(*ptrTimer0InterruptFunction)(void);

/**********************************************/
//(Interrupt Service Routine) of Timer 0 interrupt
__irq void Timer0IRQHandler(){

	T0IR=mMR0_INTERRUPT; 	// skasowanie flagi przerwania 
	ptrTimer0InterruptFunction();		// cos do roboty
	VICVectAddr=0x00; 	// potwierdzenie wykonania procedury obslugi przerwania
}
/**********************************************/
void Timer0Interrupts_Init(unsigned int uiPeriod, void (*ptrInterruptFunction)(void)){ // microseconds

        // interrupts

	VICIntEnable |= (0x1 << VIC_TIMER0_CHANNEL_NR);            // Enable Timer 0 interrupt channel 
	VICVectCntl0 = mIRQ_SLOT_ENABLE | VIC_TIMER0_CHANNEL_NR;  // Enable Slot 0 and assign it to Timer 0 interrupt channel
	VICVectAddr0 = (unsigned long)Timer0IRQHandler; 	   // Set to Slot 0 Address of Interrupt Service Routine 

        // match module

	T0MR0 = 15 * uiPeriod;                 	      // value 
	T0MCR |= (mINTERRUPT_ON_MR0 | mRESET_ON_MR0); // action 

        // timer

	T0TCR |=  mCOUNTER_ENABLE; // start 
  
        //zadanie 3 
  
  ptrTimer0InterruptFunction = ptrInterruptFunction;
}
