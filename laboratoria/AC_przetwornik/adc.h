#define P027_AIN1_ADC_PIN (1<<22)   // ustawienie pinu
// AD CONTROL REGISTER
#define CHANNEL_AIN0 (1<<0)         // kanal pierwszy
#define AD_ENABLE (1<<21)           // wlaczenie przetwornika ad
#define START_AD_CONVERSION (1<<24) // start przetwornika AD
// AD DATA REGISTER
#define AD_DONE_REGISTER (1<<31)    // konwersja gotowa
#define AD_DATA_MASK 0x0000FFC0     // maska aby odczytac dane z rejestru
#define DIVIDER 21                  // dzielnik aby pot. robil 1 obrot

void AD_Init(void);
unsigned int uiReadADC(void);
unsigned int uiCompleteAD(void);
