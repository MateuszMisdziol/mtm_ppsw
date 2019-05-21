#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_STRING_LTH 10
#define MAX_KEYWORD_NR 3

typedef enum TokenType
{KEYWORD, NUMBER, STRING} TokenType;

typedef enum KeywordCode
{CALLIB, GOTO} KeywordCode;

typedef union TokenValue
{
	enum KeywordCode eKeyword;
	unsigned int uiNumber;
	char *pcString;
} TokenValue;

typedef struct Token
{
	enum TokenType eType;
	union TokenValue uValue;
} Token;

typedef struct Keyword
{
	enum KeywordCode eCode;
	char cString[MAX_KEYWORD_STRING_LTH + 1];
} Keyword;

/*typedef enum Result
{OK, ERROR} Result;*/

/*typedef enum CompResult
{ DIFFERENT , EQUAL } CompResult;*/

extern Keyword asKeywordList[MAX_KEYWORD_NR];
extern Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

///////////////FUNKCJE/////////////////

unsigned char ucFindTokensInString(char *pcString);
enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);
