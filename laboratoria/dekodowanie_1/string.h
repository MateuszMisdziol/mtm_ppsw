#define TERMINATOR '\r'

///////////OPERACJE_PROSTE/////////////

enum CompResult {DIFFERENT, EQUAL};

void CopyString(char pcSource[], char pcDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString(char pcSourceStr[], char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar);

///////////KONWERSJE/////////////

enum Result {OK, ERROR};

void UIntToHexStr (unsigned int uiValue, char pcStr[]);
enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);
