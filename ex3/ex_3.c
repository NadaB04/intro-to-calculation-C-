/***********************
* Nadav Banay
* 326277910
* ass03
***********************/
#define SIZE 50
#define LIMIT 50


#include <stdio.h>
#include <math.h>
int ex2(), reversDigits(), IsPali(), IsPrime(), Max_Sequence(), FindMax(), ex4();
void Print_dis_Primes(), ex3(), ex1();

int main() {
/******************
* Function Name: main
* Input: None
* Output: None(prints)
* Function Operation: the function asks the user to chose between the written functions, and then operates it.
 * if the choice is invalid the function prints "Wrong option!"
******************/

    int option = 0;
    printf("1: primes\n"
           "2: goldbach\n"
           "3: lychrel\n"
           "4: max set\n");
    scanf("%d", &option);
    if (option == 1) {
        ex1();
    }else if (option == 2) {
        ex2();
    }else if (option == 3) {
        ex3();
    }else if (option == 4) {
        int len = 0;
        printf("Enter the number of elements\n");
        scanf("%d", &len);
        int sequnce[len];
        for(int i = 0; i < len; i++) {
            scanf("%d", &sequnce[i]);
        }

        printf("%d", ex4(sequnce, len));
    } else {
        printf("Wrong option!");
    }

    return 0;
}



int reversDigits(int num, int base)
{
/******************
* Function Name: reverseDigits
* Input: int num( num > 0 ), int base( base > 0 )
* Output: int( positive)
* Function Operation: takes a number in a given base and reverse it
******************/
    int rev_num = 0;
    while (num > 0) {
        rev_num = rev_num * base + num % base;
        num = num / base;
    }
    return rev_num;
}

void ex1() {
/******************
* Function Name: ex1
* Input: None
* Output: None(prints)
* Function Operation: the function prints all the prime numbers until the defined "SIZE"
******************/
    printf("%d", 2);
    for(int num = 3; num < (SIZE); num++) {
        if(IsPrime(num)) {
            printf(" %d", num);
        }
    }
}







int ex2() {
/******************
* Function Name: ex2
* Input: None
* Output: None(prints)
* Function Operation: the function prints up to 2 prime numbers combinations of even numbers, while both of the numbers in the combinations aren't bigger than SIZE
******************/
    int num = 4;
    int max_prime = 2;
    for(int i = 2; i < SIZE; i++) {
        if (IsPrime(i)){
            max_prime = i;
        }
    }
    while (num <= 2*max_prime){
        Print_dis_Primes(num);
        num+=2;
    }
}

void Print_dis_Primes (int num) {
/******************
* Function Name: Print_dis_Primes
* Input: int num
* Output: None(prints)
* Function Operation: the function prints up to 2 combinations of int num, while the numbers with the biggest gap are printed last and both of the numbers aren't bigger than SIZE.
******************/

    double middle = num/2, min = (pow(num,2)+1);
    double dis_from_middle[num];
    for(int i = 0; i < num; i++) {
        dis_from_middle[i] = pow(num,2);
    }
    for(int i = 2; i < num; i++) {
        if (IsPrime(num-i) && IsPrime(i)) {
            dis_from_middle[i] = (pow((middle - i), 2) + pow((middle - num + i), 2));
        }
    }

    // finds the minimum
    for(int i = 2; i < num; i++) {
        min = (dis_from_middle[i] >= min) ? min : dis_from_middle[i];
    }
    for(int i = 2; i < num; i++) {
        if (dis_from_middle[i] == min) {

            // searches for the last prime before those who are the closest to the middle
            int j = i-1;
            while((dis_from_middle[j] == pow(num, 2)) && (j>1)) {
                j=j-1;
            }


            if((j>1) && (dis_from_middle[j] < pow(num, 2)) && (num-j)<=SIZE) {
                printf("%d = %d + %d\n", num, j, (num-j));
                printf("%d = %d + %d\n", num, i, (num-i));
                break;
            } else {
                printf("%d = %d + %d\n", num, i, (num-i));
                break;
            }
        }
    }

}


int IsPrime(int num) {
/******************
* Function Name: IsPrime
* Input: int num
* Output: int (0 or 1)
* Function Operation: returns 1 if the number is a prime number and 0 if not.
******************/

    if(num < 2) {
        return 0;
    }
    if (num == 2) {
        return 1;
    }
    for (int i = 2; i < num; ++i) {
        if (num%i == 0) {
            return 0;
        }
    }
    return 1;
}







void ex3() {
/******************
* Function Name: ex3
* Input: None
* Output: None(prints)
* Function Operation: the function goes over the numbers until LIMIT and prints them if they are palindroms and prints the proccess until a palindrom is recieved(the proccess is summing the number with its reverse digits).
******************/

    int result = 0, num = 0;
    for(int unchanged_num = 1; unchanged_num < LIMIT; unchanged_num++) {
        num = unchanged_num;
        printf("%d", num);
        while (!IsPali(num)) {
            result = num + reversDigits(num, 10);
            printf(":%d+%d=%d", num, reversDigits(num, 10), result);
            num = result;
        }
        printf("\n");
    }
}

int IsPali(int result) {
/******************
* Function Name: IsPali
* Input: int result(>=0, integer)
* Output: int (0 or 1)
* Function Operation: the function returns 1 if result is a palindrom, and 0 if not
******************/

    if (result == 0) {
        return 1;
    }
    int len = (log10(result)/1)+1;
    int result_without_right_dig=0;
    if (len == 1) {
        return 1;
    }
    if (result%10 != reversDigits(result, 10)%10) {
        return 0;
    }

    result_without_right_dig = (result/10);
    return IsPali(reversDigits((reversDigits(result_without_right_dig, 10)/10), 10));

}



int ex4(int sequnce[], int len) {
/******************
* Function Name: ex4
* Input: int sequnce[], int len(needs to be equal to the size of the array).
* Output: int
* Function Operation: the function returns the biggest monotonically incresing sequnce that can be made using the int sequnce[]'s elements
******************/

    int maxims[len];
    for(int i = 0; i < len; i++) {
        maxims[i] = 0;
    }


    for( int first_idx = 0; first_idx < (len-1); first_idx++) {
        maxims[first_idx] = Max_Sequence(sequnce, len, first_idx);
    }
    return FindMax(maxims, len);
}

int Max_Sequence(int sequnce[], int len, int first_idx) {
/******************
* Function Name: Max_Sequence
* Input: int sequence[](elements need to be positive integers), int len(needs to be equal to the size of the array), int first_idx(needs to be within the indexes of the array).
* Output: int
* Function Operation: the function returns the biggest increasing that can be made starting from sequnce[first_idx]
******************/

    int last = sequnce[first_idx];
    int maxims[len], temp[len];
    // setting up the initial values in the array

    for (int i = 0; i < len; i++) {
        maxims[i] = 1;
        temp[i] = sequnce[i];
    }



    for (int i = (first_idx + 1); i < len; i++) {
        if (sequnce[i] > last) {
            last = sequnce[i];
            temp[i] = 0;
            maxims[i] = Max_Sequence(temp, len, first_idx);
            maxims[0] = maxims[0] + 1;
        }
    }


    return FindMax(maxims, len);
}

int FindMax(int nums[], int len) {
/******************
* Function Name: FindMax
* Input: int nums[](with positive integers), int len(needs to be equal to the size of the array).
* Output: int (elements are within the values of nums]
* Function Operation: the function returns the biggest element in the nums[] array.
******************/
    int max = -1;
    for(int i = 0; i < len; i++){
        if (nums[i] > max) {
            max = nums[i];
        }
    }
    return max;
}


