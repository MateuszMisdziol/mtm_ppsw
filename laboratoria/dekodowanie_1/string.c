#include <LPC21xx.H>
#include "string.h"

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
