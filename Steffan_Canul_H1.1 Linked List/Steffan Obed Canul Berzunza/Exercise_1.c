//Steffan Canul, Diana Olivas, Jenny Bacab, Noe Lozano
//Libraries definition
#include <stdio.h>
#include <stdlib.h>
//Self Definition and global pointers
struct listNode{
	char data; 	
	struct listNode *nextPtr; 	
} *startPtr, *newPtr, *currentPtr;

//Functions of the program
void isEmpty(struct listNode *startPtr);
void insertEnd(struct listNode **startPtr, char data);
void insert(struct listNode **startPtr, int index, char data);
void printList(struct listNode *startPtr);
void deleteNode(struct listNode **head_ref, int index);
void printListBackwards(struct listNode *list);
struct listNode *searchNode(struct listNode **head, char data);


//Global variables
int user, uindex, searchindex;
char udata;
//Main function
int main(void){

  startPtr = NULL;//Stablish the starting pointer to NULL/to nothing

  while (user != 8)//If the user type 8, the program ends
  {
    printf("\nEnter your choice:\n1 to check if the list is empty.\n2 to insert a node at the end of the list.\n3 to insert a node at a specific location (index).\n4 to delete a node at a specific location (index).\n5 to search an specific value in the list.\n6 to print all the elements in the list.\n7 to print all the elements in the list in reverse order.\n8 to exit");
    printf("\nSelect one of the following options:");
    scanf("%d",&user);
    //The principal interface of the program
    switch(user)//Switch to choice an option
    {
      case 1:
        isEmpty(startPtr);
      break;
      case 2:
        printf("\nInsert Data: ");
        scanf(" %c",&udata);
        insertEnd(&startPtr, udata);
        fflush(stdin);
      break;
      case 3:
        printf("\nInsert Data: ");
        scanf(" %c",&udata);
        printf("Insert Index: ");
        scanf("%d",&uindex);
        insert(&startPtr, uindex, udata);
        fflush(stdin);
      break;
      case 4:
        printf("Insert the index to delete: ");
        scanf("%d", &uindex);
        deleteNode(&startPtr, uindex);
        fflush(stdin);
      break;
      case 5:
        printf("Insert the value to find: ");
        scanf(" %c", &udata);
        if(searchNode(&startPtr, udata) != 0)//if it returns a pointer:
          printf("\nYour value '%d' was found in the node with index: %d\n\n", searchNode(&startPtr, udata)->data, searchindex);//Prints the data of the returned pointer and its index
        else if (searchNode(&startPtr, udata) == 0)//if it do not returns a pointer:
          printf("\nYour value is not in the Linked list\n");

      break;
      case 6:
        printList(startPtr);
      break;
      case 7:
        printListBackwards(startPtr);
      break;
      default:
        printf("\nSelect a valid option\n\n");
      break;
    }
  }
}

//Function that checks if there is any list/node
void isEmpty(struct listNode *startPtr){
  if(startPtr == NULL){//If the start pointer is not pointing in any direction
    printf("\nThe list is empty\n\n");//Then hte list is empty
  }
  else{
    printf("\nThere's something in the list\n\n");//Else, the list isn't empty
  }
  fflush(stdin);//Clean the buffer
}

//Function to insert a node at the end of the list
void insertEnd(struct listNode **startPtr, char data){
  //Nodes definition
  struct listNode *currentPtr;
  struct listNode *newPtr = malloc(sizeof(struct listNode));

  if (newPtr != NULL){ //If there is available memory:
    newPtr->data = data;//The new pointer is named the insert name
    newPtr->nextPtr = NULL;//The new pointer starts pointing to null 
    
    if (*startPtr == NULL){//If the startpointer is pointing to nothing
      *startPtr = newPtr;//The start pointer starts to point to the new pointer address
    }
    else{//If the startpointer isn't pointing to nothing
      currentPtr = *startPtr;//The address of of the startptr is copied to currentptr
      while(currentPtr->nextPtr != NULL){//While the link pointer to is pointing to another pointer
        currentPtr = currentPtr->nextPtr;//The program iterates until find the last node
      }
      currentPtr->nextPtr = newPtr;//And then the pointer is inserted
    }
  }
  else{//If there is not available memory, the program send an error and comes back to the interface
    printf("%c not inserted. No memory available.\n", data);
  }
  fflush(stdin);//Clean the buffer
}

//Function to insert a node in any location using the index
void insert(struct listNode **startPtr, int index, char data){
  //Nodes definition and variables
  int size = 0;
  int indexplus = index+1;
  struct listNode *currentPtr, *newPtr, *prevPtr;
  newPtr = malloc(sizeof(struct listNode)); 
  //The current pointer takes the address of the startpointer
  currentPtr = *startPtr;

  while(currentPtr != NULL){
    ++size;
    currentPtr = currentPtr->nextPtr;
  }//Iterative form to calculate the size of the list
  
  if (newPtr != NULL){//If there is available memory:
    newPtr->data = data;//The new pointer is named the insert name
    newPtr->nextPtr = NULL;////The new pointer starts pointing to null
    currentPtr = *startPtr;//The address of of the startptr is copied to currentptr

    if (index < 0 || index > size){//If the index typed exceeds the size of the list, the program do not allow the insertion of the node
    printf("\nInvalid position\n\n");
    fflush(stdin);//Clean the buffer
    return;}

    else{//But if not:
      currentPtr = *startPtr;
      prevPtr = *startPtr;//Both pointers to move start at the beginning point

      if(index == 0){ //If the place requested by is user is the first on the list:
        newPtr->nextPtr = *startPtr;
        *startPtr = newPtr;
        return;//The node is inserted at the beginning and returns to the interface
      }

      while (indexplus--) {//The while starts to iterate until the index reaches 0
                                              
        if (indexplus == 0) { //When getting to the to final loop (which is 0), insert the new node
       
          newPtr->data = data;
          newPtr->nextPtr = NULL;
          newPtr->nextPtr = currentPtr;  

          if (currentPtr != prevPtr) //If previous and current pointer are not pointing at the same pointer
            prevPtr->nextPtr = newPtr;  //The previous pointer links with the new node
          else 
            *startPtr = newPtr; //But if they are, the starting pointer links to the new pointer
          } 
          
        else{//Otherwise, both pointers moves to their next nodes, being current one node ahead
          prevPtr = currentPtr;
          currentPtr = currentPtr->nextPtr; 
        }
      } 
    }
  }
  else//If there is not available memory, the program send an error and comes back to the interface 
    printf( "\nYour data: '%c' was not inserted. No memory available.\n", data );
  fflush(stdin);//Cleans the buffer
};

//Function that deletes an specific node given a specific index(location)
void deleteNode(struct listNode **startPtr, int index){
  //Nodes definition and variables
  int size = 0;
  struct listNode *currentPtr, *tempPtr, *sizePtr;  

  sizePtr = *startPtr; //An independant struct for measuring the size

  while(sizePtr != NULL){
    ++size;
    sizePtr = sizePtr->nextPtr;
  }//Iterative form to calculate the size of the list
  
  if (index < 0 || index > size-1){//If the index typed exceeds the size of the list, the program do not allow the insertion of the node
  printf("\nInvalid position\n\n");
  fflush(stdin);
  return;}//Cleans the buffer and returns to the interface

  if (*startPtr == NULL) //If the list is empty, does nothing
    return;
 
  currentPtr = *startPtr; 
 
  if (index == 0){//If the first node is being deleted:
      *startPtr = currentPtr->nextPtr;//The starting pointer change the value of the address to the next pointer
      free(currentPtr);
      return;//The pointer is cleaned and the program returns to the menu
  }
 
  for (int i = 0; currentPtr != NULL && i < index - 1; i++)
    currentPtr = currentPtr->nextPtr;//Else, the program iterates and locate the node given the index:

  tempPtr = currentPtr->nextPtr->nextPtr;//A temporal node takes the address of the next next pointer and saves the address
 
  free(currentPtr->nextPtr);//The address of the next pointer current's pointer is cleaned 
 
  currentPtr->nextPtr = tempPtr; //The address of the current pointer is change to the temporal pointer and the pointer is finally deleted

  fflush(stdin);//Cleans the buffer
}

//Function to print the list 
void printList(struct listNode *startPtr){
  //Nodes definition 
  struct listNode *currentPtr;

  currentPtr = startPtr;//The current pointer start pointing at the beginning of the list

  if (currentPtr == NULL){
    printf("\nList is empty.\n");
  }//If the value of the starting pointer is NULL then the current pointer is also NULL, the list is empty
  else{//If not:
    printf("\n");
    while(currentPtr != NULL){

      printf("%c->", currentPtr->data);//While the pointer is different from NULL it prints the pointers name(currentPtr->data)

      currentPtr = currentPtr->nextPtr;//The pointer points at the next pointer
    }
    printf("NULL");//If there is no node left, the program prints NULL and finishes
    printf("\n");
  }
}

struct listNode *searchNode(struct listNode **head, char data){

  fflush(stdin);//Cleans the buffer
  //Nodes definition and variables definition
  searchindex = 0;
  struct listNode *currentPtr = *head;

  while(currentPtr != NULL){//While the list is not empty

    if(currentPtr->data == data)
      return currentPtr;//Returns the pointer where the data is found

    currentPtr = currentPtr->nextPtr;//The current pointer take the address of the next pointer
    searchindex++;//Searches for the index where the data is stored
  }
  return 0;//If the data is not in the list, returns 0
}

//Function that prints a linked list backwards
void printListBackwards(struct listNode *startPtr) {
   if(startPtr == NULL) {//The first node is printed as NULL
      printf("NULL");
      return;
   }
   
   printListBackwards(startPtr->nextPtr);//Using a basic resursion method, the "second" round of the recursion goes backwards printing the values until the first one 
   printf("->%c",startPtr->data);
}