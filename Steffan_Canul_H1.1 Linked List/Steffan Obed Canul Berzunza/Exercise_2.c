//Jenny Bacab, Diana Olivas, Steffan Canul, Noe Lozano
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>
  
/* structure for a node */
struct Node
{
    int data;
    struct Node *next;
};

void generate(int size, struct Node **start_ref);
struct Node* merge(struct Node* a, struct Node* b);
void checkNumber(int number, struct Node* head);

void insertAtTheBegin(struct Node **start_ref, int data);
void bubbleSort(struct Node *start);
void swap(struct Node *a, struct Node *b);
void printList(struct Node *start);

void moveNode(struct Node** destRef, struct Node** sourceRef);

int main()
{
    srand(time(NULL));
    
    struct Node *res = NULL;
    struct Node *first_list = NULL;
    struct Node *second_list = NULL;
    
    generate(25, &first_list);
    generate(25, &second_list);
    
    printf("\nFirst linked list");
    printList(first_list);
    
    printf("\nSecond linked list");
    printList(second_list);
    
    /* Merge lists */
    res = merge(first_list, second_list);
    
    printf("\nMerged linked list");
    printList(res);
    
    checkNumber(0, res);
    checkNumber(10, res);
    checkNumber(20, res);
    checkNumber(30, res);
    checkNumber(40, res);
    checkNumber(50, res);
  
    getchar();
    return 0;
}

void generate(int size, struct Node **start_ref)
{
    
    for (int i = 0; i < size; i++) {
        int number = rand() % 100;
        insertAtTheBegin(start_ref, number);
    }
        
    bubbleSort(*start_ref);
}

/* Function to insert a node at the beginning of a linked list */
void insertAtTheBegin(struct Node **start_ref, int data)
{
    struct Node *ptr1 = (struct Node*)malloc(sizeof(struct Node));
    ptr1->data = data;
    ptr1->next = *start_ref;
    *start_ref = ptr1;
}
  
/* Bubble sort the given linked list */
void bubbleSort(struct Node *start)
{
    int swapped, i;
    struct Node *ptr1;
    struct Node *lptr = NULL;
  
    /* Checking for empty list */
    if (start == NULL)
        return;
  
    do
    {
        swapped = 0;
        ptr1 = start;
  
        while (ptr1->next != lptr)
        {
            if (ptr1->data > ptr1->next->data)
            { 
                swap(ptr1, ptr1->next);
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    }
    while (swapped);
}
  
/* function to swap data of two nodes a and b*/
void swap(struct Node *a, struct Node *b)
{
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/* Function to print nodes in a given linked list */
void printList(struct Node *start)
{
    struct Node *temp = start;
    printf("\n");
    while (temp!=NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
}

struct Node* merge(struct Node* a, struct Node* b)
{
  struct Node* result = NULL;
   
  /* point to the last result pointer */
  struct Node** lastPtrRef = &result;
   
  while(1)
  {
    if (a == NULL)
    {
      *lastPtrRef = b;
       break;
    }
    else if (b==NULL)
    {
       *lastPtrRef = a;
       break;
    }
    if(a->data <= b->data)
    {
      moveNode(lastPtrRef, &a);
    }
    else
    {
      moveNode(lastPtrRef, &b);
    }
   
    /* tricky: advance to point to the next ".next" field */
    lastPtrRef = &((*lastPtrRef)->next);
  }
  return(result);
}

void moveNode(struct Node** destRef, struct Node** sourceRef)
{
    /* the front source node  */
    struct Node* newNode = *sourceRef;
    assert(newNode != NULL);
 
    /* Advance the source pointer */
    *sourceRef = newNode->next;
 
    /* Link the old dest off the new node */
    newNode->next = *destRef;
 
    /* Move dest to point to the new node */
    *destRef = newNode;
}

/*Function to count the number of duplicate nodes in the linked list */
void checkNumber(int number, struct Node* head)
{
    int count = 0;
 
    while (head->next != NULL) {

        if(head->data == number){
            count++;
        }
        head = head->next;
    }
    
    printf("\nThe number %d was found %d times.", number, count);
}