#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

//Point 6, exercise 10.21
float bmip, bmik, weightinpounds, weightinkilograms, heightinmeters, heightininches;
int c, x=1, a=1;
 
struct HealthProfile{
    char lastname[50];
    char firstname[50];
    struct{
        int date;
        int month;
        int year;
        int age;
    }birth;
    struct{
        char us[20];
        float weight;
        float height;
        char gender[1];
        float BMI;
        int HR;
    }personal;
} patient;

int bmif()
{
    printf("Which metrical system you use? (Type 1 to SI or 2 to Imperial):");
    scanf("%d", &c);
    if(c==1)
    {
        strcpy(patient.personal.us, "SI");
    }
    else
    {
        strcpy(patient.personal.us, "IS");
    }
    switch (c)
    {
        case 1:
        printf("Type your weight in kilograms: ");
        scanf("%f", &weightinkilograms);
        weightinkilograms=weightinkilograms*2.2;
        printf("Type your height in meters: ");
        scanf("%f",&heightinmeters);
        heightinmeters=heightinmeters*39.3701;
        patient.personal.weight=weightinkilograms;
        patient.personal.height=heightinmeters;
        bmip=((weightinkilograms * 703)/(pow(heightinmeters, 2)));
        patient.personal.BMI=bmip;
        break;

        case 2:
        printf("Type your height in inches: ");
        scanf("%f",&heightininches);
        printf("Type your weight in pounds: ");
        scanf("%f",&weightinpounds);
        patient.personal.height=heightininches;
        patient.personal.weight=weightinpounds;
        bmip=((weightinpounds * 703)/(pow(heightininches, 2)));
        patient.personal.BMI=bmip;
        break;

        default:
        printf("There's an error in your input");
        return 1;
        break;
    }
    return 0;
}

void hrf(int age)
{
    int hr=220-age;
    patient.personal.HR=hr;
}

void age(int present_year, int birth_year)
{

   int final_year = present_year - birth_year;
   patient.birth.age=final_year;
}

int main (void)
{
  int temp, eg, md;
  printf("Date of today 21/09/2021");
    while (x==1)
    {
        printf("\nConfigure the patient->1\n");
        printf("Display the informartion of the patient->2\n");
        printf("Exit the program->3\nYour Choice is:");
        scanf("%d", &temp);
        if(temp==1){
            printf("Input the first name: ");
            scanf("%s", patient.firstname);
            printf("Input the last name: ");
            scanf("%s", patient.lastname);
            printf("Input birth date: ");
            scanf("%d", &patient.birth.date);
            printf("Input birth month (1-12): ");
            scanf("%d", &patient.birth.month);
            printf("Which gender is the patient(M-F-O): ");
            scanf("%s", patient.personal.gender);
            if (patient.birth.month>12) return 1;
            printf("Input birth year: ");
            scanf("%d", &patient.birth.year);
            if (patient.birth.year>2021) return 1;
            age( 2021, patient.birth.year);
            bmif();
            hrf(patient.birth.age);
            eg=(.85 * patient.personal.HR);
            md=(.5 * patient.personal.HR);

        }
        else if (temp==2){
            printf("The first name of the patient is: %s\n", patient.firstname);
            printf("The last name of the patient is: %s\n", patient.lastname);
            printf("The age of the patient is: %d years\n", patient.birth.age);
            printf("The gender of the patient is: %s\n", patient.personal.gender);
            printf("The patient weights: %.2f pounds\n", patient.personal.weight);
            printf("The height of the patient is: %.2f inches\n", patient.personal.height);
            printf("The HR of the patient is: %d\n", patient.personal.HR);
            printf("The BMI of the patient is: %.2f", patient.personal.BMI);
            if (patient.personal.BMI<18.5)printf("\nThe patient has underweight");
            else if(patient.personal.BMI>=18.5 && patient.personal.BMI<=24.9)
            printf("\nThe patient BMI is normal");
            else if(patient.personal.BMI>=25 && patient.personal.BMI<=29.9) printf("\nThe patient has overweight");
            else printf("\nThe patient is obese");
            printf("The patient HR appropiate range of %d - %d", eg, md);
        }
        else{
            break;
        }

    }
    return 0;
}
