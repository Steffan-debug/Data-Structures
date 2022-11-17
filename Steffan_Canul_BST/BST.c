#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 500

struct treeNode{
	struct treeNode *leftPtr;
	int data;
	struct treeNode *rightPtr;
};

//Global Variables and their definition
struct treeNode* queue[MAX];
int rear = 0;
int front = -1;

//Functions prototypes 
void insert(struct treeNode **PtrtorootPtr, int value);
struct treeNode *max(struct treeNode *nodePtr);
struct treeNode *search(struct treeNode *rootPtr, int value);

int depth(struct treeNode *nodePtr);
int countLeaves(struct treeNode *nodePtr);
void printLevel(struct treeNode *rootPtr, int level);

void levelOrder(struct treeNode* root);
struct treeNode *pop();

struct  treeNode* deleteNode(struct  treeNode* nodePtr, int data);

int main()
{
  int user = -1, value;
  struct treeNode *rootPtr = NULL, *auxPtr;

  while (user != 0) {   
  printf("Enter your choice: \n"
	"1 to insert a new node\n"
  "2 to find the dept of the tree\n"
  "3 to find how many leaves the tree has\n"
  "4 to print the leaves are at that level\n"
  "5 to print the Level Order Traversal\n"
  "6 to delete a node\n"
  "0 to exit\n"
	);

    printf("? ");
	  scanf(" %d", &user);

    switch (user){

    case 1:
        printf("Enter value to be inserted: ");
	    scanf(" %d", &value);

		auxPtr = search(rootPtr, value);

		if (auxPtr == NULL){
		insert(&rootPtr, value);

        memset(&queue, 0, sizeof queue);
        rear = 0;
        front = -1;
        }
				
		else
		    printf("Duplicate data!\n");
				
        break;

    case 2:
		if (rootPtr == NULL)
            printf("There are no nodes!\n");
				
		else
            printf("The depth of the tree is: %d\n", depth(rootPtr));

		break;


	case 3:
		if(rootPtr == NULL)
            printf("There are no nodes\n");

        else{
            printf("\n The count of the leaves is: %d\n", countLeaves(rootPtr));
            printf("\n");
        }

		break;

	case 4:
        if(rootPtr == NULL)
            printf("There are no nodes\n");

        else{
            printf("Enter the level: ");
            scanf("%d", &value);

            int height = depth(rootPtr);

            if (value - 1 > height)
                printf("Out of range\n");

            else{
                printLevel(rootPtr,value);
                printf("\n");
            }
        }
		break;

	case 5:
        if(rootPtr == NULL)
            printf("There are no nodes\n");

        else{
            levelOrder(rootPtr);
            printf("\n");
        }
        break;

    case 6:
		if(rootPtr == NULL)
            printf("There are no nodes\n");

        else{
            printf("Delete a node: ");
            scanf(" %d", &value);

            auxPtr = search(rootPtr, value);

            if (auxPtr == NULL)
                printf("The node does not exist. It was not erased\n");
          
            else{
                deleteNode(rootPtr, value);

                memset(&queue, 0, sizeof queue);
                rear = 0;
                front = -1;
            }
        }
		break;
      
    case 0:
        break;

	default:
		printf("Invalid choice!\n\n");
		break;
        }
    }
    return 0;
}


void insert(struct treeNode **PtrtorootPtr, int value){
	struct treeNode *newPtr, *previousPtr, *currentPtr;

	/* Create new node */
	newPtr = malloc(sizeof(struct treeNode));

	/* Check if newPtr is not NULL */
	if (newPtr != NULL){
		newPtr->data = value;
		newPtr->rightPtr = NULL;
		newPtr->leftPtr = NULL;

		/* Iterate until right position */
		previousPtr = NULL;
		// *PtrtorootPtr = rootPtr
		currentPtr = *PtrtorootPtr;

		while(currentPtr != NULL){

			/* previousPtr Update */
			previousPtr = currentPtr;

			/* currentPtr Update */
			if (value > currentPtr->data){
				currentPtr = currentPtr->rightPtr;
			}
			else{
				currentPtr = currentPtr->leftPtr;
			}

		}

		/* Check if tree is empty */
		if (previousPtr == NULL){
			/* rootPtr (*PtrtorootPtr) Update */
			*PtrtorootPtr = newPtr;
		}
		/* Insert node to the right */
		else if (value > previousPtr->data){
			previousPtr->rightPtr = newPtr;
		}
		/* Insert node to the left */
		else{
			previousPtr->leftPtr = newPtr;
		}
	}
	else{
		printf("No memory available.\n");
	}
}

struct treeNode *max(struct treeNode *nodePtr){
	struct treeNode *temp = nodePtr;

	while(temp->rightPtr != NULL){
		temp = temp->rightPtr;
	}

	return temp;
}

struct treeNode *search(struct treeNode *rootPtr, int value){
	struct treeNode *currentPtr;
	currentPtr = rootPtr;

	while(currentPtr != NULL && currentPtr->data != value){
		if (value > currentPtr->data){
			currentPtr = currentPtr->rightPtr;
		}
		else{
			currentPtr = currentPtr->leftPtr;
		}
	}

	return currentPtr;
}

int depth(struct treeNode* nodePtr){
    if (nodePtr == NULL)
        return 0;

    else {
        int leftDpth = depth(nodePtr->leftPtr);
        int rightDpth = depth(nodePtr->rightPtr);
 
        if (leftDpth > rightDpth)
            return (++leftDpth);
        else
            return (++rightDpth);
    }
}

int countLeaves(struct treeNode* nodePtr){
  if(nodePtr == NULL)      
    return 0;

  if(nodePtr->leftPtr == NULL && nodePtr->rightPtr==NULL)     
    return 1;    
           
  else
    return countLeaves(nodePtr->leftPtr) + countLeaves(nodePtr->rightPtr);     
}

void printLevel(struct treeNode* rootPtr, int level){

    if (rootPtr == NULL)
        return;

    else if (level == 1)
        printf("%d ", rootPtr->data);

    else if (level > 1){
        printLevel(rootPtr->leftPtr, level - 1);
        printLevel(rootPtr->rightPtr, level - 1);
		}
    
	return;
}

struct treeNode *pop()
{
    return queue[++front];
}

void levelOrder(struct treeNode* root)
{
    struct treeNode* temp = root;
    while(temp)
    {
        printf("%d ",temp->data);
        if(temp->leftPtr)
            queue[rear++] = temp->leftPtr;

        if(temp->rightPtr)
            queue[rear++] =temp->rightPtr;
      
      temp = pop();
    }
}

struct  treeNode* deleteNode(struct  treeNode* nodePtr, int data){
  //Recursion algorithm used to move within the tree and delete a node
  
  /*If the value given by the user is bigger than the value of the current node,
   it uses the delete recursion algorithm to keep moving to the right until find a different value from the previous statement*/

  if(nodePtr->data < data)
    nodePtr->rightPtr = deleteNode(nodePtr->rightPtr, data);

  /*If the value of the current node is bigger than the value given bt the user,
   it uses the delete recursion algorithm to keep moving to the left until find
  a different value from the previous statement*/
    
  else if(nodePtr->data > data)
    nodePtr->leftPtr = deleteNode(nodePtr->leftPtr, data);

  //If the nodePtr data is equal to the introduced one, we briefly stop the recursion and delete that node
  else
  {
    //Case1
    //If the node do not have any thing to point at (left and right pointers point to null), it freely deletes the node
    if(nodePtr->leftPtr == NULL && nodePtr->rightPtr == NULL)
    {
      free(nodePtr);
      printf("The node was erased\n\n");
      return NULL;
    }

    //Case 2 (Left and Right)
    /*If the selected node has the right pointer pointing to a node,
    it stores in a temporary node the information of the leaf and deletes at all the pointer and return the temporary pointer,
    the next recursive round the returned node will take the place of the erased node*/
  
    else if(nodePtr->leftPtr == NULL && nodePtr->rightPtr!=NULL)
    { 
      struct treeNode *temp = nodePtr->rightPtr;
      free(nodePtr);
      printf("The node was erased\n\n");
      return temp;
    }
        
    /*If the selected node has the left pointer pointing to a node, 
    it stores in a temporary node the information of the leaf and deletes at all the pointer and return the temporary pointer,
     the next recursive round the returned node will take the place of the erased node*/
    else if(nodePtr->rightPtr == NULL&&nodePtr->leftPtr != NULL)
    {
      struct treeNode *temp = nodePtr->leftPtr;
      free(nodePtr);
      printf("The node was erased\n\n");
      return temp;
    }
  
    //Case 3
    //If the node has both pointers (left and right) pointing to another node:
    else
    {
      int leftMax = max(nodePtr->leftPtr)->data;//Look for the maximum value of the left node subtree by using the function max() defined previously and store it in leftmax

      nodePtr->data = leftMax; //It writes the max value of the left node subtree into the nodePtr data for replacing it. 

      nodePtr->leftPtr = deleteNode(nodePtr->leftPtr, leftMax);/*By using recursion in the subtree of the left node, we find the node with the value used for replacing 
      the one we wanted to "erase" and erase that node, which is at the end of the subtree (Case 1).*/
    }
  }

  return nodePtr;
}