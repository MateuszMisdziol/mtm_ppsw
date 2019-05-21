#include "command_decoder.h"
#include "string.h"

Token asToken[MAX_TOKEN_NR];

Keyword asKeywordList[MAX_KEYWORD_NR] =
{
	{CALLIB, "callib"}, {GOTO, "goto"}
};

unsigned char ucTokenNr = 0;

unsigned char ucFindTokensInString(char *pcString){
  
  enum State {TOKEN, DELIMITER};
  enum State eState = DELIMITER;
  char cCurrentChar;
  unsigned char ucWhichToken;

  for(ucWhichToken = 0; ;ucWhichToken++){
    
    cCurrentChar = pcString[ucWhichToken];
    
    switch(eState){
      case TOKEN:
        if(cCurrentChar == '\0'){
          return ucTokenNr;
        }
        else if(ucTokenNr == MAX_TOKEN_NR){
          return ucTokenNr;
        }
        else if(cCurrentChar == ' '){
          eState = DELIMITER;
        }
        break;
      case DELIMITER:
        if(cCurrentChar == '\0'){
          return ucTokenNr;
        }
        else if(cCurrentChar != ' '){
          eState = TOKEN;
          asToken[ucTokenNr].uValue.pcString = pcString + ucWhichToken;
          ucTokenNr++;
        }
        break;
    }
  }
}

enum Result eStringToKeyword(char pcStr[], enum KeywordCode *peKeywordCode){
  
  unsigned char ucKeywordCounter;
  
  for(ucKeywordCounter = 0; ucKeywordCounter < MAX_KEYWORD_NR; ucKeywordCounter++){
    if(eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString) == EQUAL){
      *peKeywordCode = asKeywordList[ucKeywordCounter].eCode;
      return OK;
    }
  }
  return ERROR;
}

void DecodeTokens(void){
  
  unsigned char ucTokenCounter;
  
  for(ucTokenCounter = 0; ucTokenCounter < ucTokenNr; ucTokenCounter++){

    if(eStringToKeyword(asToken[ucTokenCounter].uValue.pcString, &asToken[ucTokenCounter].uValue.eKeyword) == OK){
      asToken[ucTokenCounter].eType = KEYWORD;
    }
    else if(eHexStringToUInt(asToken[ucTokenCounter].uValue.pcString, &asToken[ucTokenCounter].uValue.uiNumber) == OK){
      asToken[ucTokenCounter].eType = NUMBER;
    }
    else{
      asToken[ucTokenCounter].eType = STRING;
    }
  }
}


void DecodeMsg(char *pcString){
  ucTokenNr = ucFindTokensInString(pcString);
  ReplaceCharactersInString(pcString, ' ', '\0');
  DecodeTokens();
}
