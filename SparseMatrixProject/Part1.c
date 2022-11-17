//Noe Lozano, Diana Olivas, Steffan Canul, Jenny Bacab
#include <stdio.h>
#include <stdlib.h>

//Synonyms
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
int delete(Matrix *mx, int row, int column);
void assign(Matrix *mx, int row, int column, int value);
int read(Matrix *mx, int row, int column);
void specialMatrix(); //Exercise 8
int shortestPath(Matrix *mx, int ver1, int ver2); //Exercise 9

void printMatrix(Matrix *mx);
int search(Matrix *mx, int row, int column);

void sum(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);
void product(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC);


int main()
{
    Matrix matrixA = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
    Matrix matrixB = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
    
    int user = 0, numMatrix = 0;

    int initRows, initColumns;

    int row, column, newInfo, returnedInfo, selectMatrix;

    while (user != 9) {   
        printf("\nSparse Matrix Project\n");

        printf("\t1. Create a new matrix empty.\n");
        printf("\t2. Insert a node.\n");
        printf("\t3. Delete a node.\n");
        printf("\t4. Assign a new value.\n");
        printf("\t5. Read node value.\n");
        printf("\t6. Sum two matrix.\n");
        printf("\t7. Multiply two matrix.\n");
        printf("\t8. Print the matrix.\n");
        printf("\t9. Exit.\n");
        printf("\t10. Create the 'special' matrix (Ex. 8) in the current created matrix,\n\tand do exercises 9 and 10.");
        printf("\nChoose an option: ");
        scanf("%d", &user); // Save option

        switch (user)
        {
            case 1:
                printf("\n### Create a new matrix empty ###\n");

                printf("Introduce the size of your matrix...\n");

                printf("Introduce how many rows: "); 
                scanf("\n %d", &initRows);

                printf("Introduce how many columns: "); 
                scanf("\n %d", &initColumns);

                numMatrix++;
                
                if (numMatrix == 1)
                    create(&matrixA, initRows, initColumns);
                
                else if (numMatrix == 2)
                    create(&matrixB, initRows, initColumns);
                
                else
                    printf("There are too many matrices\n"); 

                break;

            case 2:
                printf("\n### Insert a node ###.\n\t1. Matrix A\n\t2. Matrix B\n");
                printf("Choose an option: ");
                scanf(" %d", &selectMatrix);

                if (matrixA.totalRows == 0 && matrixB.totalRows == 0)
                {
                    printf("There are no matrices.\n");
                    break;
                }

                if (selectMatrix != 1 && selectMatrix != 2)
                {
                    printf("Invalid option.\n");
                    break;
                }

                printf("Introduce the positon of your new value:\n");
                printf("Introduce i (the row): ");
                scanf(" %d", &row);
                printf("Introduce j (the column): ");
                scanf(" %d", &column);
                printf("Introduce the new value: ");
                scanf(" %d", &newInfo);
                fflush(stdin);

                if (selectMatrix == 1)
                    insert(&matrixA, row, column, newInfo);
                else
                    insert(&matrixB, row, column, newInfo);
            
                break;

            case 3:
                printf("\n### Delete a node ###.\n\t1. Matrix A\n\t2. Matrix B\n");
                printf("Choose an option: ");
                scanf(" %d", &selectMatrix);

                if (selectMatrix != 1 && selectMatrix != 2)
                {
                    printf("Invalid option.\n");
                    break;
                }

                printf("Introduce the position of the value for removing it... :\n");
                printf("Introduce i (the row): ");
                scanf(" %d", &row);
                printf("Introduce j (the column): ");
                scanf(" %d", &column);
                fflush(stdin);

                if (selectMatrix == 1)
                    returnedInfo = delete(&matrixA, row, column);
                
                else
                    returnedInfo = delete(&matrixB, row, column);
                

                printf("The value deleted is : %d\n", returnedInfo);
                
                break;

            case 4:
                printf("\n### Assign a new value ###.\n\t1. Matrix A\n\t2. Matrix B\n");
                printf("Choose an option: ");
                scanf(" %d", &selectMatrix);

                if (selectMatrix != 1 && selectMatrix != 2)
                {
                    printf("Invalid option.\n"); 
                    break;
                }

                printf("Introduce the positon of your new value:\n");
                printf("Introduce i (the row): ");
                scanf(" %d", &row);
                printf("Introduce j (the column): ");
                scanf(" %d", &column);
                printf("Introduce the new value: ");
                scanf(" %d", &newInfo);
                fflush(stdin);

                if (selectMatrix == 1)
                    assign(&matrixA, row, column, newInfo);

                else
                    assign(&matrixB, row, column, newInfo);

                break;

            case 5:
                printf("\n### Read node value ###.\n\t1. Matrix A\n\t2. Matrix B\n");
                printf("Choose an option: ");
                scanf(" %d", &selectMatrix);

                if (selectMatrix != 1 && selectMatrix != 2)
                {
                    printf("Invalid option.\n");
                    break;
                }

                printf("Introduce the position of the value:\n");
                printf("Introduce the row: ");
                scanf(" %d", &row);
                printf("Introduce the column: ");
                scanf(" %d", &column);

                if (selectMatrix == 1)
                    returnedInfo = read(&matrixA, row, column);

                else
                    returnedInfo = read(&matrixB, row, column);

                printf("The searched value is : %d\n", returnedInfo); 
                break;

            case 6:
                printf("\n### Sum two matrix ###.\n");

                if(matrixA.totalRows == 0 || matrixB.totalRows == 0)
                {
                    printf("Not enough matrices for the operation.\n");
                    break;
                }

                Matrix matrixS = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};

                printf("\nMatrixA + MatrixB = MatrixC");
                sum(&matrixA, &matrixB, &matrixS);

                printf("\nMatrix A: \n");
                printMatrix(&matrixA);

                printf("\nMatrix B: \n");
                printMatrix(&matrixB);

                printf("\nMatrix C: \n");
                printMatrix(&matrixS);
                printf("\n");
                break;

            case 7:
                printf("\n### Multiply two matrix ###.\n");

                if(matrixA.totalRows == 0 || matrixB.totalRows == 0)
                {
                    printf("You need to create some matrices.\n");
                    break;
                }

                Matrix matrixP = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};

                printf("\nMatrixA * MatrixB = MatrixC");
                product(&matrixA, &matrixB, &matrixP);

                printf("\nMatrix A: \n");
                printMatrix(&matrixA);

                printf("\nMatrix B: \n");
                printMatrix(&matrixB);

                printf("\nMatrix C: \n");
                printMatrix(&matrixP);
                printf("\n");
                break;

            case 8:
                printf("\n### Print the matrix ###.\n\t1. Matrix A\n\t2. Matrix B\n");
                printf("Choose an option: ");
                scanf(" %d", &selectMatrix);

                if (selectMatrix != 1 && selectMatrix != 2)
                {
                    printf("Invalid option :c\n");
                    break;
                }

                if (selectMatrix == 1)
                    printMatrix(&matrixA);

                else
                    printMatrix(&matrixB);    

                break;

            case 9:
                printf("Goodbye c:\n");
                exit(0);
                break;

            case 10:
                numMatrix++;
                
                if (numMatrix == 1){
                  printf("\n~~~Special Matrix Created in Matrix A~~~\n");
                    specialMatrix(&matrixA);
                    
                    printf("\tThe shortest path length beetween vertices 1,2 is: %d\n", shortestPath(&matrixA, 1, 2));
                    printf("\tThe shortest path length beetween vertices 1,6 is: %d\n", shortestPath(&matrixA, 1, 6));
                    printf("\tThe shortest path length beetween vertices 1,8 is: %d\n", shortestPath(&matrixA, 1, 8)); 
                }

                else if (numMatrix == 2){ 
                  printf("\n~~~Special Matrix Created in Matrix B~~~\n");       
                    specialMatrix(&matrixB);

                    printf("\tThe shortest path length beetween vertices 1,2 is: %d\n", shortestPath(&matrixB, 1, 2));
                    printf("\tThe shortest path length beetween vertices 1,6 is: %d\n", shortestPath(&matrixB, 1, 6));
                    printf("\tThe shortest path length beetween vertices 1,8 is: %d\n", shortestPath(&matrixB, 1, 8)); 
                }
                
                else
                    printf("There are too many matrices\n"); 
                break;

            default:
                printf("Invalid option, introduce the correct number\n");
                break;
        }
    }
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
    {//checks if it is the first insertion

        newNode->nextColumn = currentRow->nextColumn;
        currentRow->nextColumn = newNode;

        newNode->nextRow = currentCol->nextRow;
        currentCol->nextRow = newNode;
        return;
    }

    else if (currentRow->nextColumn == currentRow && currentCol->nextRow != currentCol)
    {//If is not the first insertion on the column

        newNode->nextColumn = currentRow->nextColumn;
        currentRow->nextColumn = newNode;

        prevNode = currentCol;
        tempNode = currentCol;
        tempNode = tempNode->nextRow;
         //It iterates to look until it find te last
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
    {//If is not the first insertion on the row

        newNode->nextRow = currentCol->nextRow;
        currentCol->nextRow = newNode;

        prevNode = currentRow;
        tempNode = currentRow;
        tempNode = tempNode->nextColumn;

        while (tempNode != currentRow)
        {//It iterates to look until it find te last
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
    {//But if is there already insertions

        
        prevNode = currentRow;
        tempNode = currentRow;
        tempNode = tempNode->nextColumn;

        while (tempNode != currentRow)
        {//iterates columns and rows to find the postion and insert the node by pointing and making point back
            if (tempNode->column > column)
            {
                newNode->nextColumn = tempNode;
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

            prevNode = tempNode;
            tempNode = tempNode->nextColumn;
        }

        newNode->nextColumn = prevNode->nextColumn;
        prevNode->nextColumn = newNode;

        
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

void printMatrix(Matrix *mx)
{
    Node *currentRow = mx->headNode, *currentCol;

    if (mx->headNode != NULL)
    {//If the matrix exists it print iterating
        while (currentRow->nextRow != mx->headNode)
        {//print the elements of the row until in it reaches the headnnode
            currentCol = currentRow;
            do
            {
                printf("[%d]", currentCol->info);
                currentCol = currentCol->nextColumn;
            } while (currentCol != currentRow);

            printf("\n");
            currentRow = currentRow->nextRow;
        }

        currentCol = currentRow;

        do
        {//print the elements of the columns until in it reaches the headnnode
            printf("[%d]", currentCol->info);
            currentCol = currentCol->nextColumn;
        } while (currentCol != currentRow);
        printf("\n");
    }
}

int search(Matrix *mx, int row, int column)
{
    Node *currentRow = mx->headNode, *currentCol;
    //Check if the requested search is on the range
    if (row > mx->totalRows || column > mx->totalColumns)
    {
        printf("Out of range, try another position.\n");
        return 0;
    }

    for (int i = 0; i <= row - 1; i++)//Iterates until it find the specific row which is onto
    {
      currentRow = currentRow->nextRow;
    }
    
    currentCol = currentRow;
    currentCol = currentCol->nextColumn;

    while (currentCol != currentRow)
    {//it iterates until it finds the correct column, if it find it, return true = 1
        if (currentCol->column == column)
            return 1;

        currentCol = currentCol->nextColumn;
    }
    return 0;
}

void assign(Matrix *mx, int row, int column, int value)
{
    Node *currentRow = mx->headNode;
    Node *currentCol;
    int nodeExist;

    //If the node does not exists, the function stops
    nodeExist = search(mx, row, column);
    if (nodeExist != 1)
        return;

    //Move through rows
    for (int i = 0; i <= row - 1; i++)
    {
        currentRow = currentRow->nextRow;
    }

    //Changing positions for moving now through columns
    currentCol = currentRow;
    currentCol = currentCol->nextColumn;

    //Move through columns until we find the searched node
    while (currentCol != currentRow)
    {
        if (currentCol->column == column)
        {
            currentCol->info = value; //Asigns the new value
            return;
        }
        currentCol = currentCol->nextColumn;
    }
}

int read(Matrix *mx, int row, int column)
{
    Node *currentRow = mx->headNode;
    Node *currentCol;
    int nodeExist;

    nodeExist = search(mx, row, column);
    if (nodeExist != 1)//Uses the search function to find if it exist  before read it
        return 0;

    for (int i = 0; i <= row - 1; i++)
    {//Iterates to locate the row
        currentRow = currentRow->nextRow;
    }

    currentCol = currentRow;
    currentCol = currentCol->nextColumn;

    while (currentCol != currentRow)
    {//By using the address of the row it iterates to find the column, if it find it, return the info side the node
        if (currentCol->column == column)
        {
            return currentCol->info;
        }
        currentCol = currentCol->nextColumn;
    }
    return 0;
}

int delete(Matrix *mx, int row, int column)
{
    Node *currentRow, *currentCol, *prevNode, *tempNode;
    int nodeExist, deletedinfo, counter = 0;

    nodeExist = search(mx, row, column);//use the function search to find if the node exist
    if (nodeExist != 1)
        return 0;

    for (currentRow = mx->headNode; currentRow->row != row; currentRow = currentRow->nextRow)
    {
        for (currentCol = mx->headNode; currentCol->column != column; currentCol = currentCol->nextColumn)
        {
            counter++;
        }
    }

    if (currentRow->nextColumn != currentRow && currentCol->nextRow != currentCol)
    {
        tempNode = currentRow;
        prevNode = currentRow;
        tempNode = tempNode->nextColumn;

        while (tempNode != currentRow)
        {
            if (tempNode->row == row && tempNode->column == column)
            {
                prevNode->nextColumn = tempNode->nextColumn;
                tempNode->nextColumn = tempNode;

                tempNode = currentCol;
                prevNode = currentCol;
                tempNode = tempNode->nextRow;

                while (tempNode != currentCol)
                {
                    if (tempNode->row == row && tempNode->column == column)
                    {
                        prevNode->nextRow = tempNode->nextRow;
                        tempNode->nextRow = tempNode;
                        deletedinfo = tempNode->info;
                        free(tempNode);
                        return deletedinfo;
                    }

                    prevNode = tempNode;
                    tempNode = tempNode->nextRow;
                }
            }

            prevNode = tempNode;
            tempNode = tempNode->nextColumn;
        }
    }
    return 0;
}

void sum(Matrix *matrixA, Matrix *matrixB, Matrix *matrixC)
{
    // Validación solo se puede sumar matrices del mismo orden
    if(matrixA->totalRows != matrixB->totalRows && matrixA->totalColumns && matrixB->totalColumns)
    {
        printf("\nTwo matrices have to have an equal number of rows and columns to be able to add them.\n");
        return;
    }

    int valueA = 0, valueB = 0, result = 0;

    // Se crea la matrix resultante
    create(matrixC, matrixA->totalRows, matrixA->totalColumns);

    for (int i = 1; i <= matrixC->totalRows; i++)
    {
        for (int j = 1; j <= matrixC->totalColumns; j++)
        {
            valueA = read(matrixA, i, j);
            valueB = read(matrixB, i, j);

            result = valueA + valueB;

            insert(matrixC, i, j, result);
        }
    }
    return;
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
  //creates the sparse matrix initialazing it and filling it
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
  //Declare empty matrixes
  Matrix matrixFinal = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
  Matrix matrixTemp = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
  int verInfo, rounds = 0, power = 1;

  verInfo = read(mx, ver1, ver2);
  
  if(verInfo == 0){//If the node is 0, there is no path, so it level the power to find if there is any path
    ++power;
    product(mx, mx, &matrixTemp);
    verInfo = read(&matrixTemp, ver1, ver2);

      while (verInfo == 0){//Even if there is not a path
        if(rounds == 0){//Elevate it once more in order to find a path
          product(&matrixTemp, mx, &matrixFinal);
          verInfo = read(&matrixFinal, ver1, ver2);

          ++power;
          ++rounds;
        }

        else{
          if(rounds == 1){//after eleving the grade of the matrix
            Matrix *prevMatrix = (Matrix *)malloc(sizeof(Matrix));
            //It saves the matrix in prev matrix
            prevMatrix = &matrixFinal;
            //reset the values of final matrix
            Matrix matrixFinal = { .totalRows = 0, .totalColumns = 0, .headNode = NULL};
            //and elevate it once more to find a path until !=0
            product(prevMatrix, mx, &matrixFinal);
            ++power;

            verInfo = read(&matrixFinal, ver1, ver2);
          } 
        }
      }
    }
    
  return power; //Returns the exponent
}