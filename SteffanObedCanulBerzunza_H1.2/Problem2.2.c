//Diana Olivas, Steffan Canul, Noé Lozano, Jenny Bacab
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX 100

char finalstr[MAX];

struct listNode{
  char data;
  struct listNode *nextPtr;
};

void cleanStr(char string[]);
void nodesStr(struct listNode **startPtr, char string[], int size);
void reverseNodesStr(struct listNode **startPtr, char text[], int size);
bool isPalindrome(struct listNode *startPtr1, struct listNode *startPtr2);

int main()
{
  char text[MAX];
    
  struct listNode *startPtr_1 = NULL, *startPtr_2 = NULL;
    
  printf("\nType a line of text: ");
  scanf("%[^\n]s", text);
    
  cleanStr(text);

  int size = strlen(finalstr); 

  for(int i = 0; i < size; i++){
    printf("%c",finalstr[i]);
  }

  nodesStr(&startPtr_1, finalstr, size);
  reverseNodesStr(&startPtr_2, finalstr, size);

  isPalindrome(startPtr_1, startPtr_2) ? printf("\nThe word is palindrome") : printf("\nThe word is not palindrome");
  return 0;
}

void cleanStr(char string[]){
  int count = 0;
  for(int i = 0 ; i < strlen(string) ; ++i) {
    char temp = string[i];

    if((temp >= 32 && temp <= 47) || (temp >= 58 && temp <= 64) || (temp >= 91 && temp <= 96) || (temp >= 123 && temp <= 126)){ 
      continue;
    }
    finalstr[count] = temp;
    count++;
  }
}

void nodesStr(struct listNode **startPtr, char string[], int size){
  struct listNode *newPtr;

  for(int i = 0; i < size; ++i){
    newPtr = malloc(sizeof(struct listNode));

    if(newPtr != NULL){
      newPtr->data = string[i];
      newPtr->nextPtr = *startPtr;
      *startPtr = newPtr;               
    }
    else
      printf("\nYour data was not inserted, there is no memory available");
  }
}

void reverseNodesStr(struct listNode **startPtr, char string[], int size){
  struct listNode *newPtr;

  for(int i = size - 1 ; i >= 0; --i){
    newPtr = malloc(sizeof(struct listNode));

    if(newPtr != NULL){
        newPtr->data = string[i];
        newPtr->nextPtr = *startPtr;
        *startPtr = newPtr;               
    }
    else
      printf("\nYour data was not inserted, there is no memory available");
  }
}

bool isPalindrome(struct listNode *startPtr1, struct listNode *startPtr2){
  
  while(startPtr1 != NULL)
  {

    if(startPtr1->data == startPtr2->data)
      return 1; 

    else
      return 0;
         
    startPtr1 = startPtr1->nextPtr;
    startPtr2 = startPtr2->nextPtr;      
  }
  return 0;
}