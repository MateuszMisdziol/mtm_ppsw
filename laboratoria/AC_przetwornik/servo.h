enum DetectorState {ACTIVE, INACTIVE};

void ServoInit(unsigned int uiServoFrequency);
void ServoCallib(void);
void ServoGoTo(unsigned int uiPosition);
enum DetectorState eReadDetector(void);
