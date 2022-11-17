#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct Matrix Matrix;

struct Node
{
    int info;
    int row;
    int column;
    Node *nextColumn; // Next Column
    Node *nextRow; // Next Row
};

struct Matrix
{
    int totalRows;
    int totalColumns;
    int totalElements; //apoyo
    int currentElements; //apoyo
    Node *headNode;
}; 

// Prototypes
void create(Matrix *mx, int rows, int columns);
void insert(Matrix *mx, int row, int column, int value);

int search(Matrix *mx, int row, int column);
int read(Matrix *mx, int row, int column);

void product(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);

void specialMatrix(); //Exercise 8
int shortestPath(Matrix *mx, int ver1, int ver2); //Exercise 9


int main()
{
  Matrix matrixA = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
    printf("\n~~~Source Code 2~~~\n");
      specialMatrix(&matrixA);
                    
      printf("\tThe shortest path length beetween vertices 1,2 is: %d\n", shortestPath(&matrixA, 1, 2));
      printf("\tThe shortest path length beetween vertices 1,6 is: %d\n", shortestPath(&matrixA, 1, 6));
      printf("\tThe shortest path length beetween vertices 1,8 is: %d\n", shortestPath(&matrixA, 1, 8));
      
    return 0;
}

void create(Matrix *mx, int rows, int columns){
    mx->totalRows = rows;
    mx->totalColumns = columns;
    mx->currentElements = 0;
    mx->totalElements = rows * columns;

    Node *initNode, *newNode, *tempNode, *prevNode;

    // Allocate memory
    initNode = (Node *)malloc(sizeof(Node));

    // Verify if there is enough memory
    if (initNode == NULL)
    {
        printf("No memory available, the matrix was not created...\n");
        return;
    }
    
    //Node pointing at (0,0)
    initNode->row = 0;
    initNode->column = 0;
    initNode->info = 0;

    // Init pointer/node links to itself. This will be the equivalent of (0,0)
    initNode->nextColumn = initNode;
    initNode->nextRow = initNode;
 
    // The head node of the used matrix is now the init node 
    mx->headNode = initNode;

    // "for" to insert the extra rows
    for (int i = 1; i <= mx->totalRows; ++i)
    {
        //With every iteration a new node is made
        newNode = (Node *)malloc(sizeof(Node));

        if (newNode != NULL)//If the node is empty
        {
          newNode->info = 0;
          newNode->column = 0;
          newNode->row = i;
          //If the node is pointing at the beginning it points to the next row, but if is not, it iterates to look for the last node in order to point to a new one
            if (initNode->nextRow == initNode)
            {
              newNode->nextRow = initNode->nextRow;
              newNode->nextColumn = newNode;
              initNode->nextRow = newNode;
            }
            else
            {
              tempNode = initNode;
              prevNode = initNode;
              tempNode = tempNode->nextRow;

                while (tempNode != initNode)
                {
                  prevNode = tempNode;
                  tempNode = tempNode->nextRow;
                }

              newNode->nextRow = prevNode->nextRow;
              newNode->nextColumn = newNode;
              prevNode->nextRow = newNode;
            }
        }
    }

    // "for" to insert the extra columns

    for (int j = 1; j <= mx->totalColumns; j++)
    {
        newNode = (Node *)malloc(sizeof(Node));

        if (newNode != NULL)
        {
            newNode->info = 0;
            newNode->column = j;
            newNode->row = 0;
            //If the node is pointing at the beginning it points to the next column, but if is not, it iterates to look for the last node in order to point to a new one
            if (initNode->nextColumn == initNode)
            {

                newNode->nextColumn = initNode->nextColumn;
                newNode->nextRow = newNode;
                initNode->nextColumn = newNode;
            }
            else
            {
                tempNode = initNode;
                prevNode = initNode;
                tempNode = tempNode->nextColumn;

                while (tempNode != initNode)
                {
                    prevNode = tempNode;
                    tempNode = tempNode->nextColumn;
                }

                newNode->nextColumn = prevNode->nextColumn;
                newNode->nextRow = newNode;
                prevNode->nextColumn = newNode;
            }
        }
    }
}

void insert(Matrix *mx, int row, int column, int value)
{   
    //The program do not insert if the user exceed the range
    if (row > mx->totalRows || column > mx->totalColumns)
    {
        printf("Out of range, try another position.\n");
        return;
    }

    Node *newNode, *currentRow, *currentCol, *tempNode, *prevNode;
    int counter = 0;

    newNode = (Node *)malloc(sizeof(Node));

    
    //The information inside the node is wrote inside the ndoe
    newNode->info = value;
    newNode->row = row;
    newNode->column = column;

    //for knowing how many elements there are in the matrix and for moving through the matrix
    for (currentRow = mx->headNode; currentRow->row != row; currentRow = currentRow->nextRow)
    {
        for (currentCol = mx->headNode; currentCol->column != column; currentCol = currentCol->nextColumn)
            counter++;
    }
        //In order to understand we compare the values of the node locations to find where to locate the insertion
    if (currentRow->nextColumn == currentRow && currentCol->nextRow == currentCol)
    {

        newNode->nextColumn = currentRow->nextColumn;
        currentRow->nextColumn = newNode;

        newNode->nextRow = currentCol->nextRow;
        currentCol->nextRow = newNode;
        return;
    }

    else if (currentRow->nextColumn == currentRow && currentCol->nextRow != currentCol)
    {

        newNode->nextColumn = currentRow->nextColumn;
        currentRow->nextColumn = newNode;

        prevNode = currentCol;
        tempNode = currentCol;
        tempNode = tempNode->nextRow;

        while (tempNode != currentCol)
        {
            if (tempNode->row > row)
            {
                newNode->nextRow = tempNode;
                currentCol->nextRow = newNode;
                return;
            }
            prevNode = tempNode;
            tempNode = tempNode->nextRow;
        }

        newNode->nextRow = prevNode->nextRow;
        prevNode->nextRow = newNode;
        return;
    }

    else if (currentRow->nextColumn != currentRow && currentCol->nextRow == currentCol)
    {

        newNode->nextRow = currentCol->nextRow;
        currentCol->nextRow = newNode;

        prevNode = currentRow;
        tempNode = currentRow;
        tempNode = tempNode->nextColumn;

        while (tempNode != currentRow)
        {
            if (tempNode->column > column)
            {
                newNode->nextColumn = tempNode;
                currentRow->nextColumn = newNode;
                return;
            }
            prevNode = tempNode;
            tempNode = tempNode->nextColumn;
        }

        newNode->nextColumn = prevNode->nextColumn;
        prevNode->nextColumn = newNode;
        return;
    }

    else if (currentRow->nextColumn != currentRow && currentCol->nextRow != currentCol)
    {

        // Row--------------------------
        prevNode = currentRow;
        tempNode = currentRow;
        tempNode = tempNode->nextColumn;

        while (tempNode != currentRow)
        {
            if (tempNode->column > column)
            {
                newNode->nextColumn = tempNode;
                currentRow->nextColumn = newNode;

                // Column--------------------------
                prevNode = currentCol;
                tempNode = currentCol;
                tempNode = tempNode->nextRow;

                while (tempNode != currentCol)
                {
                    if (tempNode->row > row)
                    {
                        newNode->nextRow = tempNode;
                        currentCol->nextRow = newNode;
                        return;
                    }
                    prevNode = tempNode;
                    tempNode = tempNode->nextRow;
                }

                newNode->nextRow = prevNode->nextRow;
                prevNode->nextRow = newNode;
                return;
            }

            prevNode = tempNode;
            tempNode = tempNode->nextColumn;
        }

        newNode->nextColumn = prevNode->nextColumn;
        prevNode->nextColumn = newNode;

        // Column--------------------------
        prevNode = currentCol;
        tempNode = currentCol;
        tempNode = tempNode->nextRow;

        while (tempNode != currentCol)
        {
            if (tempNode->row > row)
            {
                newNode->nextRow = tempNode;
                currentCol->nextRow = newNode;
                return;
            }
            prevNode = tempNode;
            tempNode = tempNode->nextRow;
        }
        newNode->nextRow = prevNode->nextRow;
        prevNode->nextRow = newNode;
    }
}

int search(Matrix *mx, int row, int column)
{
    Node *currentRow = mx->headNode, *currentCol;

    if (row > mx->totalRows || column > mx->totalColumns)
    {
        printf("Out of range, try another position.\n");
        return 0;
    }

    for (int i = 0; i <= row - 1; i++)
    {
        currentRow = currentRow->nextRow;
    }

    currentCol = currentRow;
    currentCol = currentCol->nextColumn;

    while (currentCol != currentRow)
    {
        if (currentCol->column == column)
            return 1;

        currentCol = currentCol->nextColumn;
    }
    return 0;
}

int read(Matrix *mx, int row, int column)
{
    Node *currentRow = mx->headNode;
    Node *currentCol;
    int nodeExist;

    nodeExist = search(mx, row, column);
    if (nodeExist != 1)
        return 0;

    for (int i = 0; i <= row - 1; i++)
    {
        currentRow = currentRow->nextRow;
    }

    currentCol = currentRow;
    currentCol = currentCol->nextColumn;

    while (currentCol != currentRow)
    {
        if (currentCol->column == column)
        {
            return currentCol->info;
        }
        currentCol = currentCol->nextColumn;
    }
    return 0;
}

void product(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC)
{
    if (matrixA->totalColumns != matrixB->totalRows)
    {
        printf("\nThe number of columns in the first matrix must be equal to the number of rows in the second matrix.\n");
        return;
    }

    int valueA = 0, valueB = 0, result = 0;

    // Se crea la matrix resultante
    create(matrixC, matrixA->totalRows, matrixB->totalColumns);

    // Necesitamos hacer esto por cada columna de la segunda matriz (B)
    for (int a = 1; a <= matrixB->totalColumns; a++)
    {
        // Dentro recorremos las filas de la primera (A)
        for (int i = 1; i <= matrixA->totalRows; i++)
        {
            for (int j = 1; j <= matrixA->totalColumns; j++)
            {
                valueA = read(matrixA, i, j);
                valueB = read(matrixB, j, a);

                result += valueA * valueB;
            }
            insert(matrixC, i, a, result);
            result = 0;
        }
    }
  
}

void specialMatrix(Matrix *mx)
{
  create(mx, 8, 8);
  insert(mx, 1, 3, 1);
  insert(mx, 1, 4, 1);
  insert(mx, 2, 3, 1);
  insert(mx, 3, 1, 1);
  insert(mx, 3, 2, 1);
  insert(mx, 3, 5, 1);
  insert(mx, 3, 8, 1);
  insert(mx, 4, 1, 1);
  insert(mx, 4, 5, 1);
  insert(mx, 5, 3, 1);
  insert(mx, 5, 4, 1);
  insert(mx, 5, 7, 1);
  insert(mx, 5, 8, 1);
  insert(mx, 6, 7, 1);
  insert(mx, 7, 5, 1);
  insert(mx, 7, 6, 1);
  insert(mx, 7, 8, 1);
  insert(mx, 8, 3, 1);
  insert(mx, 8, 5, 1);
  insert(mx, 8, 7, 1);
}

int shortestPath(Matrix *mx, int ver1, int ver2)
{
  
  Matrix matrixFinal = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
  Matrix matrixTemp = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
  int verInfo, rounds = 0, power = 1;

  verInfo = read(mx, ver1, ver2);
  
  if(verInfo == 0){
    ++power;
    product(mx, mx, &matrixTemp);
    verInfo = read(&matrixTemp, ver1, ver2);

      while (verInfo == 0){
        if(rounds == 0){
          product(&matrixTemp, mx, &matrixFinal);
          verInfo = read(&matrixFinal, ver1, ver2);

          ++power;
          ++rounds;
        }

        else{
          if(rounds == 1){
            Matrix *prevMatrix = (Matrix *)malloc(sizeof(Matrix));

            prevMatrix = &matrixFinal;
          
            Matrix matrixFinal = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};

            product(prevMatrix, mx, &matrixFinal);
            ++power;

            verInfo = read(&matrixFinal, ver1, ver2);
          } 
        }
      }
    }
  return power;
}