//Diana Olivas, Steffan Canul, Noé Lozano, Jenny Bacab
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A Linked List Node
struct Node
{
    char data;
    struct Node *next;
};

void printList(struct Node *topPtr)
{
    struct Node *ptr = topPtr;
    while (ptr)
    {
      printf("%c ", ptr->data);
      ptr = ptr->next;
    } 
}

void push(struct Node **topPrt, char data)
{
  struct Node *newNode = (struct Node*)malloc(sizeof(struct Node));
  newNode->data = data;

  newNode->next = *topPrt;

  *topPrt = newNode;
}

int main() {
    
  struct Node *topPtr = NULL;
  int choice;
  char data[500];

  printf("Input a string:");
  scanf("%s", data);

  int length = strlen(data);

  for (int i=0; i<length;++i){
    push(&topPtr, data[i]);
  }

  printList(topPtr);
  return 0;
}