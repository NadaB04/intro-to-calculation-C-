/***********************
* Nadav Banay
* 326277910
* ex_6
***********************/



#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <string.h>
#include "person.h"

#define MSG_KILL "%s kills %s"
#define MSG_KILL_AND " and %s"
#define ASK_NAME "Name:\n"
#define ASK_ID "ID:\n"
#define ASK_NUM_KIDS "Num of kids:\n"
#define ASK_NAME_KID "Kid #%d name:\n"
#define MSG_NAME "Name: %s\n"
#define MSG_ID "ID: %d\n"
#define MSG_NAME_KID "Kid #%d: %s\n"



//comparsions:
int comparePersonByFirstName(void* a, int i, int j){
/******************
* Function Name: comparePersonByFirstName
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: int
* Function Operation: the function returns value greater than 0 if a[i].firstName is greater than a[j].firstName in the lexigraphic order, 0 if its equal, less than 0 if its lower.
******************/
    Person *arr = (Person *)a;
    return strcmp(arr[i].firstName, arr[j].firstName);
}
int comparePersonByLastName(void* a, int i, int j){
/******************
* Function Name: comparePersonByLastName
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: int
* Function Operation: the function returns value greater than 0 if a[i].lastName is greater than a[j].lastName in the lexigraphic order, 0 if its equal, less than 0 if its lower.
******************/
    Person *arr = (Person *)a;
    return strcmp(arr[i].lastName, arr[j].lastName);
}
int comparePersonByWeight(void* a, int i, int j){
/******************
* Function Name: comparePersonByWeight
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: int
* Function Operation: the function returns 1 if a[i].weight is greater than a[j].weight, 0 if its equal, -1 if its lower.
******************/
    Person *arr = (Person *)a;
    if (arr[i].weight > arr[j].weight){
        return 1;
    }
    else if (arr[i].weight == arr[j].weight){
        return 0;
    } else {
        return -1;
    }
}
int comparePersonByHeight(void* a, int i, int j){
/******************
* Function Name: comparePersonByHeight
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: int
* Function Operation: the function returns 1 if a[i].height is greater than a[j].height, 0 if its equal, -1 if its lower.
******************/
    Person *arr = (Person *)a;
    if (arr[i].height > arr[j].height){
        return 1;
    }
    else if (arr[i].height == arr[j].height){
        return 0;
    } else {
        return -1;
    }
}
int comparePersonByBMI(void* a, int i, int j){
/******************
* Function Name: comparePersonByBMI
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: int
* Function Operation: the function returns 1 if the bmi of a[i] is greater than the bmi of a[j], 0 if its equal, -1 if its lower.
******************/
    Person *arr = (Person *)a;
    double bmi1 = (arr[i].weight)/(arr[i].height*arr[i].height);
    double bmi2 = (arr[j].weight)/(arr[j].height*arr[j].height);
    if (bmi1 > bmi2){
        return 1;
    }
    else if (bmi1 == bmi2){
        return 0;
    } else {
        return -1;
    }
}
int comparePersonByDate(void* a, int i, int j){
/******************
* Function Name: comparePersonByDate
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: int
* Function Operation: the function returns -1 a[i] was born sooner than a[j], -1 if not, and 0 if they were born in the same date.
******************/
    Person *arr = (Person *)a;
    if (arr[i].dateOfBirth.year < arr[j].dateOfBirth.year){
        return -1;
    } else if (arr[i].dateOfBirth.year > arr[j].dateOfBirth.year){
        return 1;
    } else{
        if (arr[i].dateOfBirth.month < arr[j].dateOfBirth.month){
            return -1;
        } else if (arr[i].dateOfBirth.month > arr[j].dateOfBirth.month){
            return 1;
        } else{
            if (arr[i].dateOfBirth.day < arr[j].dateOfBirth.day){
                return -1;
            } else if (arr[i].dateOfBirth.day > arr[j].dateOfBirth.day){
                return 1;
            } else{
                return 0;
            }
        }
    }
}

//swappers:
void swapPersons(void* a, int i, int j){
/******************
* Function Name: swapPersons
* Input: void *a(valid value - a Person array), int i(valid values between the array size and 0), int j(valid values between the array size and 0)
* Output: None
* Function Operation: the function returns 1 if the bmi of a[i] is greater than the bmi of a[j], 0 if its equal, -1 if its lower.
******************/
    Person *arr = (Person *)a;
    Person temp_person = arr[i];
    arr[i] = arr[j];
    arr[j] = temp_person;
}


//load and save
void load(const char* inputFile, Person persons[], int* numOfPersonsPtr){
/******************
* Function Name: load
* Input: const char* inputFie(valid value - legal path), Person persons[], int* numOfPersonsPtr
* Output: None
* Function Operation: the function stores the "person data" int the persons[] array, while using the given file. Moreover, the function saves the number of added persons.
******************/
    FILE* fp = fopen(inputFile, "r");

    if (!fp)
        printf("Can't open file\n");
    else {
        char buffer[MAX_STR_LEN];


        while (fgets(buffer,MAX_STR_LEN, fp)) {
            char *word;
            int field_counter = 0;
            for (char *word = strtok(buffer,DELIM); word != NULL; word = strtok(NULL, DELIM))
            {
                if (field_counter == 0){
                    strcpy(persons[*numOfPersonsPtr].firstName, word);
                } else if (field_counter == 1){
                    strcpy(persons[*numOfPersonsPtr].lastName, word);
                } else if (field_counter == 2){
                    persons[*numOfPersonsPtr].dateOfBirth.day = atoi(word);
                } else if (field_counter == 3){
                    persons[*numOfPersonsPtr].dateOfBirth.month = atoi(word);
                } else if (field_counter == 4){
                    persons[*numOfPersonsPtr].dateOfBirth.year = atoi(word);
                } else if (field_counter == 5){
                    persons[*numOfPersonsPtr].height = atoi(word);
                } else if (field_counter == 6){
                    persons[*numOfPersonsPtr].weight = atof(word);
                } else{
                    break;
                }
                field_counter++;
            }
            *numOfPersonsPtr = *numOfPersonsPtr+1;

        }
    }
    if (fclose(fp)) {
        printf("Error with closing file: %s\n", inputFile);
    }
}


void save(const char* outputFile, Person persons[], int numOfPersons){
/******************
* Function Name: save
* Input: const char* outputFie(valid value - legal path), Person persons[], int numOfPersonsPtr
* Output: None
* Function Operation: the function loads the data in the persons[] array to the outputFile according to the format
******************/
    FILE* output = fopen(outputFile, "a");
    for(int person_index = 0; person_index < numOfPersons; person_index++){
        fprintf(output,"%s,%s,%d,%d,%d,%d,%.2f\n", persons[person_index].firstName, persons[person_index].lastName, persons[person_index].dateOfBirth.day, persons[person_index].dateOfBirth.month, persons[person_index].dateOfBirth.year, persons[person_index].height, persons[person_index].weight);
    }
    if (fclose(output)) {
        printf("Error with closing file: %s\n", outputFile);
    }
}