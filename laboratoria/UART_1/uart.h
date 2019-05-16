enum eReciverStatus {EMPTY, READY, OVERFLOW};
//struct ReciverBuffer sReciverBuffer;

__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
enum eReciverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char * ucDestination);
