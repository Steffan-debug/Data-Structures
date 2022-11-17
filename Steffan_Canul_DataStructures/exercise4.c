#include <stdio.h>

int main(void)
{
    struct inventory{
      char partName[30];
      int partNumber;
      float pointPrice;
      int stock;
      int reorder
    };
    
    struct address{
        char streetAddress[25];
        city[20];
        state[3];
        zipCode[6];
    };
    
    struct student{
        char firstName[15];
        char lastName[15];
        struct address homeAddress;
    };

    return 0;
}