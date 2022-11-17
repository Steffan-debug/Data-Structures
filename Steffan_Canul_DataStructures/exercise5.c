#include <stdio.h>
struct customer
{
    char lastName[15];
    char firstName[15];
    int costumerNumber;
    struct
    {
        char phoneNumber[11];
        char address[50];
        char city[15];
        char state[3];
        char zipCode[6];
    }personal;
} customerRecord, *customerPtr;
struct customer *customerPtr=&customerRecord;

int main (void){
    customerRecord.lastName; //1
    customerPtr->lastName; //2
    customerRecord.firstName; //3
    customerPtr->firstName; //4
    customerRecord.costumerNumber; //5
    customerPtr->costumerNumber; //6
    customerRecord.personal.phoneNumber; //7
    customerPtr->personal.phoneNumber; //8
    customerRecord.personal.address; //9
    customerPtr->personal.address;//10
    customerRecord.personal.city; //11
    customerPtr->personal.city; //12
    customerRecord.personal.state; //13
    customerPtr->personal.state; //14
    customerRecord.personal.zipCode; //15
    customerPtr->personal.zipCode; //16
}
