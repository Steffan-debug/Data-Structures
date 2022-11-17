//Diana Olivas, Steffan Canul, Noé Lozano, Jenny Bacab
#include<stdio.h>
#define MAX 5

int userswitch;
char arr[MAX], user;
int front = -1 , rear = -1; 

void enqueue(char c[], int b), dequeue(char c[]), printQueue(char c[]);

int main()
{
  char usr;
  while(userswitch != 4)
  {
    printf("\nEnter your Choice");
		printf("\n  1 to print queue");
		printf("\n  2 to enqueue a character");
		printf("\n  3 to dequeue a character");
    printf("\n  4 to exit");
 
		printf("\nEnter Your Choice:");
    scanf("%d",&userswitch);
    switch(userswitch)
    {
      case 1 :
        printQueue(arr);
        break;
      case 2 :
        printf("Input the element for insertion in queue : ");
        scanf(" %c", &usr);
        enqueue(arr,usr);
        break;
      case 3:
        dequeue(arr);
        break;
      case 4:
        break;
      default:
        printf("\nSelect a valid option\n");
      }
  }
  return 0;
}

void printQueue(char c[]){
  int frontTemp = front, rearTemp = rear;

  if(front == -1){
    printf("Queue is empty\n");
    return;
  }

  if( frontTemp <= rearTemp )
    while(frontTemp <= rearTemp){
      printf("%c ",c[frontTemp]);
      frontTemp++;
    }

    else{
      while(frontTemp <= MAX-1){
        printf("%c ",c[frontTemp]);
        frontTemp++;
      }
      
      frontTemp = 0;

      while(frontTemp <= rearTemp){
          printf("%c ",c[frontTemp]);
          frontTemp++;
        }
    }
    printf("\n");
}

void enqueue(char c[], int b)
{
  if((front == 0 && rear == MAX-1) || (front == rear+1)){
    printf("\nPlease, dequeue for adding new elements \n");
    return;
  }

  if(front == -1){
    front = 0;
    rear = 0;
  }

  else{
    if(rear == MAX-1)
      rear = 0;
    else
      rear++;
  }
  c[rear] = b;
}

void dequeue(char c[])
{
  if(front == -1){
    printf("\nThe list in empty\n");
    return; 
  }

  if(front == rear){
    front = -1;
    rear = -1;
  }

  else{
    if(front == MAX-1)
      front = 0;
    else
      ++front;
  }
}