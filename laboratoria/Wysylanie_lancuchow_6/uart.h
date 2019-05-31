#define RECIVER_SIZE 30
#define TRANSMITER_SIZE 30

enum eReciverStatus {EMPTY, READY, OVERFLOW};
enum eTransmiterStatus {FREE, BUSY};

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

struct Watch {
	unsigned char ucMinutes;
	unsigned char ucSecconds;
	unsigned char fSeccondsValueChanged, fMinutesValueChanged;
};

////////////// FUNKCJE ///////////////////

__irq void UART0_Interrupt (void);
void UART_InitWithInt(unsigned int uiBaudRate);
void Reciever_PutCharacterToBuffer(char cCharacter);
enum eReciverStatus eReciever_GetStatus(void);
void Reciever_GetStringCopy(char * ucDestination);
char Transmiter_GetCharacterFromBuffer(void);
void Transmiter_SendString(char cString[]);
enum eTransmiterStatus Transmiter_GetStatus(void);
void WatchInit(void);
