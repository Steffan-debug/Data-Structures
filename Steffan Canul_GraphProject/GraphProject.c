//Jenny Bacab, Steffan Canul, Noé Lozano, Diana Olivas
#include <stdio.h>
#include <stdlib.h>

/* Adjacency List per node in General List*/
struct nodeAdjInfo{
	int v;
	int value;
};

struct nodeAdj{
	struct nodeAdjInfo item;
	struct nodeAdj *nextAdjPtr;
};

/* General List */
struct nodeGenInfo{
	int u;
	struct nodeAdj *nodeAdjPtr;
};

struct nodeGen{
	struct nodeGenInfo item;
	struct nodeGen *nextGenPtr;
};

/* Prototypes */
void instructions(void);
void printVertices(struct nodeGen *GenPtr);
struct nodeGen *isVertex(struct nodeGen *NodePtr, int u);
struct nodeAdj *isEdge(struct nodeGen *NodePtr, int u, int v);
void addVertex(struct nodeGen **PtrtoGenPtr, int u);
void addEdge(struct nodeGen *GenPtr, int u, int v, int value);

void printList(struct nodeGen *GenPtr);
void printOutDegree(struct nodeGen *GenPtr);
void printInDegree(struct nodeGen *GenPtr);

int main(void){
	int choice, u, v, value;
	struct nodeGen *GenPtr = NULL, *auxGenPtr;
	struct nodeAdj *auxAdjPtr;


	/* Menu */
	instructions();
	printf("? ");
	scanf("%d", &choice);

	while(choice != 0){
		switch(choice){
			case 1:
				printf("Insert node index(u) to be added: ");
				scanf("%d", &u);
				addVertex(&GenPtr, u);
				printVertices(GenPtr);

				break;
			case 2:
				printf("Insert edge to be added:");
				printf("\n u: ");
				scanf("%d", &u);
				printf("\n v: ");
				scanf("%d", &v);
				printf("\n value(w): ");
				scanf("%d", &value);

				addEdge(GenPtr, u, v, value);
				break;
			case 3:
				printf("Insert node to be found: ");
				scanf("%d", &u);

				auxGenPtr = isVertex(GenPtr, u);

				/* Check is auxGenPtr is not NULL */
				if (auxGenPtr != NULL){
					printf("True\n");
					printf("%p\n", auxGenPtr);
					printf("u = %d\n", (auxGenPtr->item).u);
				}
				else{
					printf("False\n");
				}
				break;
			case 4:
				printf("Insert edge to be found:");
				printf("\n u: ");
				scanf("%d", &u);
				printf("\n v: ");
				scanf("%d", &v);

				auxAdjPtr = isEdge(GenPtr, u, v);

				/* Check is auxAdjPtr is not NULL */
				if (auxAdjPtr != NULL){
					printf("True\n");
					printf("%p\n", auxAdjPtr);
					printf("value = %d \n", (auxAdjPtr->item).value);
				}
				else{
					printf("False\n");
				}
				break;
      case 5:
        if (GenPtr == NULL)
          printf("There is no list to print\n");

        else{
          printf("\nEdge list:\n");

          printList(GenPtr);
          }
				break;
      case 6:
       if (GenPtr == NULL)
          printf("There is no list to print\n");

				else{
          printf("\nOut-degree:\n");

				  printOutDegree(GenPtr);
          }
				break;
      case 7:
       if (GenPtr == NULL)
          printf("There is no list to print\n");

				else{
          printf("\nIn-degree:\n");

				  printInDegree(GenPtr);
          }
				break;

			default:
				printf("Invalid choice!\n\n");
				instructions();
				break;

		}
		printf("? ");
		scanf("%d", &choice);
	}

	return 0;

}

void instructions(void){
	printf("Enter your choice:\n"
		"1 to insert a node\n"
		"2 to insert an edge\n"
		"3 to find a node\n"
		"4 to find an edge\n"
    "5 to print the edge list\n"
    "6 to print out-degree\n"
    "7 to print in-degree\n"
		"0 to exit\n"
		);
}

void printVertices(struct nodeGen *currentPtr){

	while(currentPtr != NULL){
		printf("%d ", (currentPtr->item).u);
		currentPtr = currentPtr->nextGenPtr;
	}
	printf("\n");
}

void printList(struct nodeGen *GenPtr){
  struct nodeGen *currentGenPtr;
  struct nodeAdj *currentAdjPtr;

  currentGenPtr = GenPtr;
      
  while(currentGenPtr != NULL){
    printf("%d: ", (currentGenPtr->item).u);

    currentAdjPtr = (currentGenPtr->item).nodeAdjPtr;
    while(currentAdjPtr != NULL){
      printf("%d ", (currentAdjPtr->item).v);

			currentAdjPtr = currentAdjPtr->nextAdjPtr;
		}

    printf("\n");
    currentGenPtr = currentGenPtr->nextGenPtr;
  }
}

void printOutDegree(struct nodeGen *GenPtr){
  struct nodeGen *currentGenPtr;
  struct nodeAdj *currentAdjPtr;
  int counter = 0;

  currentGenPtr = GenPtr;
      
  while(currentGenPtr != NULL){
    printf("%d: ", (currentGenPtr->item).u);

    currentAdjPtr = (currentGenPtr->item).nodeAdjPtr;
    counter = 0;
    while(currentAdjPtr != NULL){
      counter++;
			currentAdjPtr = currentAdjPtr->nextAdjPtr;
		}

    printf("%d", counter);
    printf("\n");
    currentGenPtr = currentGenPtr->nextGenPtr;
  }
}

void printInDegree(struct nodeGen *GenPtr){
  struct nodeGen *currentGenPtr, *currentGenPtr2;
  struct nodeAdj *edgePtr, *currentAdjPtr;
  int counter = 0;

  currentGenPtr = GenPtr;
  currentGenPtr2 = GenPtr;
      
  while(currentGenPtr != NULL){
    printf("%d: ", (currentGenPtr->item).u);
    counter = 0;

    currentGenPtr2 = GenPtr;
    while(currentGenPtr2 != NULL){
      currentAdjPtr = (currentGenPtr2->item).nodeAdjPtr;
          
      while(currentAdjPtr != NULL){
        if((currentGenPtr->item).u == (currentAdjPtr->item).v)
          counter++;

        currentAdjPtr = currentAdjPtr->nextAdjPtr;
		  }

      currentGenPtr2 = currentGenPtr2->nextGenPtr;
    }

    printf("%d", counter);
    printf("\n");
    currentGenPtr = currentGenPtr->nextGenPtr;
  }
}

struct nodeGen *isVertex(struct nodeGen *NodePtr, int u){
	/* NodePtr = GenPtr */

	/* Iterate over all nodes (nodeGen) in general list.
	Stop Condition:
		-End of the general list (NodePtr != NULL)
		-Value if found ((NodePtr->item).u != u)
	*/
	while(NodePtr != NULL && (NodePtr->item).u != u){
		NodePtr = NodePtr->nextGenPtr;
	}

	return NodePtr;
}

struct nodeAdj *isEdge(struct nodeGen *NodePtr, int u, int v){
	/* 1. Check if u and v are in the graph */
	struct nodeGen *uPtr, *vPtr;
	struct nodeAdj *NodeAdj;

	uPtr = isVertex(NodePtr, u);
	vPtr = isVertex(NodePtr, v);

	/* If u and v are in the graph use uPtr to find edge(u,v) */
	if (uPtr != NULL && vPtr != NULL){
		/* 2. Find edge(u,v) 
		   Adjacency List starts at (uPtr->item).nodeAdjPtr 
		*/

		NodeAdj = (uPtr->item).nodeAdjPtr;

		/* Check if NodeAdj != NULL */
		if (NodeAdj != NULL){
			/* Iterate over all elements in the Adjacency list until:
				-End of the general list (NodeAdj != NULL)
				-Value if found ((NodeAdj->item).v != v)
			*/
			while(NodeAdj != NULL && (NodeAdj->item).v != v){
				NodeAdj = NodeAdj->nextAdjPtr;
			}
			return NodeAdj;
		}
		else{
			return NULL;
		}
	}
	else{
		return NULL;
	}
}

void addVertex(struct nodeGen **PtrtoGenPtr, int u){
	struct nodeGen *newPtr, *currentPtr;

	/* *PtrtoGenPtr = GenPtr */
	if (isVertex(*PtrtoGenPtr, u)== NULL){
		/* Request for space in memory */
		newPtr = malloc(sizeof(struct nodeGen));

		/* Check if memory is available */
		if (newPtr != NULL){
			/* Update Info(item) */
			(newPtr->item).u = u;
			(newPtr->item).nodeAdjPtr = NULL;

			/* Update nextPtr */
			newPtr->nextGenPtr = NULL;

			/* previousPtr and currentPtr update */
			currentPtr = *PtrtoGenPtr;

			if (currentPtr == NULL){
				*PtrtoGenPtr = newPtr;
			}
			else{
				while(currentPtr->nextGenPtr != NULL && u > ((currentPtr->nextGenPtr)->item).u){
					currentPtr = currentPtr->nextGenPtr;
				}

				newPtr->nextGenPtr = currentPtr->nextGenPtr;
				currentPtr->nextGenPtr = newPtr;
			}

		}
		else{
			printf("No memory available!\n");
		}
	}
	else{
		printf("Vertex is already in the graph!\n");
	}
}

void addEdge(struct nodeGen *GenPtr, int u, int v, int value){
	struct nodeGen *uPtr, *vPtr;
	struct nodeAdj *edgePtr, *currentAdjPtr, *newPtr;

	/* 1. Check if nodes u and v are in the graph */
	uPtr = isVertex(GenPtr, u);
	vPtr = isVertex(GenPtr, v);

	if (uPtr != NULL && vPtr != NULL){

		/* 2. Check if edge(u, v) is already in the graph */
		edgePtr = isEdge(GenPtr, u, v);

		if (edgePtr == NULL){
			/* 3. Create a newPtr */
			newPtr = malloc(sizeof(struct nodeAdj));

			if (newPtr != NULL){
				/* 4. Initialize:
				a) newPtr
				b) currentAdjPtr
				*/

				/* newPtr Update */
				(newPtr->item).v = v;
				(newPtr->item).value = value;

				newPtr->nextAdjPtr = NULL;

				/* currentAdjPtr initialization */
				currentAdjPtr = (uPtr->item).nodeAdjPtr;

				/* 5. Check if edge is the first one in the adj list */
				if (currentAdjPtr == NULL){
					(uPtr->item).nodeAdjPtr = newPtr;
				}
				else{
					/* 6. Iterate until:
						-End of the list: currentAdjPtr->nextAdjPtr is NULL.
						-Correct position: currentPtr->nextAdjPtr has a ((currentPtr->nextAdjPtr )->item).v greater than v.
					*/
					while (currentAdjPtr->nextAdjPtr != NULL && v > ((currentAdjPtr->nextAdjPtr)->item).v){
						currentAdjPtr = currentAdjPtr->nextAdjPtr;
					}

					newPtr->nextAdjPtr = currentAdjPtr->nextAdjPtr;
					currentAdjPtr->nextAdjPtr = newPtr;
				}
			}
			else{
				printf("No memory available!\n");
			}
		}
		else{
			printf("Edge is already in the graph!\n");
		}
	}
	else{
		printf("Nodes are not in the graph!\n");
	}
}