#define MAX_TOKEN_NR 2
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 5

typedef enum TokenType
{KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode
{CALLIB, GOTO, CALC, ID} KeywordCode;

union TokenValue
{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char *pcString;
} ;

struct Token
{
	enum TokenType eType;
	union TokenValue uValue;
};

struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

extern struct Keyword asKeywordList[MAX_KEYWORD_NR];
extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

///////////////FUNKCJE/////////////////

//unsigned char ucFindTokensInString(char *pcString);
//enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode);
//void DecodeTokens(void);
void DecodeMsg(char *pcString);
