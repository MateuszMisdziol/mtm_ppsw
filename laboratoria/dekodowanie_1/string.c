#include "string.h"

///////////OPERACJE_PROSTE/////////////

void CopyString(char pcSource[], char pcDestination[]){
  
  unsigned char ucCharNumber;
  
  for(ucCharNumber = 0; pcSource[ucCharNumber] != '\0'; ucCharNumber++){
    pcDestination[ucCharNumber] = pcSource[ucCharNumber];
  }
  pcDestination[ucCharNumber]='\0';
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
  
  unsigned char ucCharNumber;
  
  for(ucCharNumber = 0; pcStr1[ucCharNumber] == pcStr2[ucCharNumber]; ucCharNumber++){
    if(pcStr1[ucCharNumber] == '\0'){
      return EQUAL;
    }
  }
  return DIFFERENT;
}

void AppendString(char pcSourceStr[], char pcDestinationStr[]){
  
  unsigned char ucPointerNubmer;
  
  for(ucPointerNubmer = 0; pcDestinationStr[ucPointerNubmer] != '\0'; ucPointerNubmer++){}
  CopyString(pcSourceStr, pcDestinationStr+ucPointerNubmer);
}

void ReplaceCharactersInString(char pcString[], char cOldChar, char cNewChar){
  
  unsigned char ucCharNumber;
  
  for(ucCharNumber = 0; pcString[ucCharNumber] != '\0'; ucCharNumber++){
    if(pcString[ucCharNumber] == cOldChar){
      pcString[ucCharNumber] = cNewChar;
    }
  }
}

//////////////////KONWERSJE/////////////////////////////

void UIntToHexStr (unsigned int uiValue, char pcStr[]){

	unsigned char ucTetradaCounter;
	unsigned char ucCurrentTetrada;

	pcStr[0] = '0';
	pcStr[1] = 'x';

	for(ucTetradaCounter = 0; ucTetradaCounter < 4; ucTetradaCounter++){
		
		ucCurrentTetrada = ((uiValue >> (ucTetradaCounter * 4)) & HEX_bm);

		if(ucCurrentTetrada>9){
			pcStr[5-ucTetradaCounter] = (ucCurrentTetrada - 10) + 'A';
		}
		else{
			pcStr[5-ucTetradaCounter] = ucCurrentTetrada + '0';
		}
	}
	pcStr[6] = '\0';
}


enum Result eHexStringToUInt(char pcStr[], unsigned int *puiValue){

	unsigned char ucCharCounter;

	if((pcStr[0] != '0') | (pcStr[1] != 'x') | (pcStr[2] == '\0')){
		return ERROR;
	}

	for(ucCharCounter = 2; ucCharCounter != '\0'; ucCharCounter++){
		if(pcStr[ucCharCounter] == '\0'){
			return OK;
		}
		else if (ucCharCounter >= 6){
			return ERROR;
		}

		*puiValue = *puiValue << 4;

		if(pcStr[ucCharCounter] >= 'A'){
			*puiValue = *puiValue | ((pcStr[ucCharCounter] - 'A') + 10);
		}
		else{
			*puiValue = *puiValue | (pcStr[ucCharCounter] - '0');
		}
	}
	return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){

	unsigned char PointerNumber;

	for(PointerNumber = 0; pcDestinationStr[PointerNumber] != '\0'; PointerNumber++){}
	UIntToHexStr(uiValue, pcDestinationStr+PointerNumber);
}
