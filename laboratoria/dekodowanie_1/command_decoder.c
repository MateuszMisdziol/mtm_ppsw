#include "string.h"
#include "command_decoder.h"

struct Keyword asKeywordList[MAX_KEYWORD_NR]=
	{
		{CALLIB, "callib"},
		{GOTO, "goto"},
	};
  
struct Token asToken[MAX_TOKEN_NR];

unsigned char ucTokenNr;

unsigned char ucFindTokensInString(char *pcString){
	
	enum LedState { TOKEN, DELIMITER};
	enum LedState eState = DELIMITER;
	
	unsigned char ucTokenCounter = 0;
	unsigned char ucCharCounter = 0;
	char cAktualnyZnak;
	
	for(ucCharCounter=0; pcString[ucCharCounter] != '\0'; ucCharCounter++){
		cAktualnyZnak = pcString[ucCharCounter];
		switch(eState){
			case DELIMITER: 	
				if(cAktualnyZnak == ' '){
					eState = DELIMITER;
				}else if(ucTokenCounter < MAX_TOKEN_NR){
					eState = TOKEN;
					asToken[ucTokenCounter].uValue.pcString = pcString + ucCharCounter; 
					ucTokenCounter++;
				}else{
					return(ucTokenCounter);
				}
				break;
			case TOKEN: 
				if(cAktualnyZnak != ' '){
					eState = TOKEN;
				}else{
					eState = DELIMITER;
				}
				break;
		}	
	}
	return(ucTokenCounter);
}

enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode){
	
	unsigned char ucKeywordIndex;
	
	for(ucKeywordIndex=0; ucKeywordIndex < MAX_KEYWORD_NR; ucKeywordIndex++){
		if(eCompareString(pcStr, asKeywordList[ucKeywordIndex].cString) == EQUAL){
			*peKeywordCode = asKeywordList[ucKeywordIndex].eCode;
			return(OK);
		}
	}
	return(ERROR);
}

void DecodeTokens(void){
	
	unsigned int uiNumber;
	unsigned char ucTokenIndex;
	enum KeywordCode eKeyword;
	
	for(ucTokenIndex=0; ucTokenIndex < ucTokenNr; ucTokenIndex++){
		if((eStringToKeyword (asToken[ucTokenIndex].uValue.pcString, &eKeyword))== OK){
			asToken[ucTokenIndex].eType = KEYWORD;
			asToken[ucTokenIndex].uValue.eKeyword=eKeyword;
		}else if((eHexStringToUInt(asToken[ucTokenIndex].uValue.pcString,&uiNumber))== OK){
			asToken[ucTokenIndex].eType = NUMBER;
			asToken[ucTokenIndex].uValue.uiNumber = uiNumber;
		}else{
			asToken[ucTokenIndex].eType = STRING;
		}
	}
}

void DecodeMsg(char *pcString){

	ucTokenNr = ucFindTokensInString (pcString);
	ReplaceCharactersInString(pcString,' ','\0');
	DecodeTokens();
}
