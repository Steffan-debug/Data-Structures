//Diana Olivas, Steffan Canul, Noé Lozano, Jenny Bacab
#include <stdio.h>
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

char pop(struct Node **topPtr)
{
    if (*topPtr == NULL) {
        return -1;
    }
 
    struct Node *head = *topPtr;
    int result = head->data;
    
    (*topPtr) = (*topPtr)->next;
 
    free(head);
 
    return result;
}

int main() {
    
    struct Node *topPtr = NULL;
    int choice;
    char data;

    do 
    {
        printf("\n\nMenu\n");
        printf("1. Print the element of the stack.\n");
        printf("2. Push a character.\n");
        printf("3. Pop a character.\n");
        printf("8. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
      
        switch (choice)
        {
            case 1: 
                printList(topPtr);
            break;
            case 2: 
                printf("\nEnter a character: ");
                scanf("%s", &data);
                //data = getchar();
                push(&topPtr, data);
                //printList(topPtr);
            break;
            case 3: 
                printf("\nThe popped node is %c", pop(&topPtr));
            break;
            case 8: 
                printf("Goodbye\n"); 
            break;
            default: 
                printf("Wrong Choice. Enter again\n");
            break;
        } 
    } while (choice != 8);
    
    
    return 0;
}