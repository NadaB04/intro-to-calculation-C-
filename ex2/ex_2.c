/*********************************************
 * Nadav Banay
 * 326277910
 * ex_2
 *********************************************/




#include <stdio.h>
#include <math.h>
int ex1(), Decimal_to_Base(), Base_to_Decimal(), ex6(), reversDigits(), ex32(), main();
void ex4(), ex5();
int main() {
    while (1) {
        int num, base;
        int option = 7;
        unsigned long x, n1, n2;
        printf("Choose an option:\n"
               "\t1. hexaDecimal to Decimal\n"
               "\t2. Decimal to Base\n"
               "\t3. Base to Decimal\n"
               "\t4. PLUS\n"
               "\t5. Shape\n"
               "\t6. Count bits\n"
               "\t7. Exit\n");
        scanf("%d", &option);

        if (option == 1) {
            printf("Enter a reversed number in base 16:\n");
            scanf("%x", &num);
            printf("%d\n", num);
            ex1(num);
        }
        else if (option == 2) {
            printf("Enter base and a number:\n");
            scanf("%d %d", &base, &x);
            if (Decimal_to_Base(x, base) == -1) {
                printf("Error!");
            }
            else {
                printf("%d\n", Decimal_to_Base(x, base));
            }
        }
        else if (option == 3) {
            printf("Enter base and a number:\n");
            scanf("%d %d", &base, &x);
            if (Base_to_Decimal(x, base) == -1) {
                printf("Error!");
            }
            else {
                printf("%d\n", Base_to_Decimal(x, base));
            }
        }
        else if (option == 4) {
            printf("Enter 2 binary numbers:\n");
            scanf("%d %d", &n1, &n2);
            ex4(n1, n2);
        }
        else if (option == 5) {
            ex5();
        }
        else if (option == 6) {
            ex6();
        }
        else if (option == 7) {
            return 0;
        }
        else {
            printf("Wrong option!\n");
        }
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
int ex1(int num) {
/******************
* Function Name: ex1()
* Input: int num (in hexadecimal base)
* Output: prints
* Function Operation: converts n to a decimal base and prints it.
******************/
    printf("%d\n", reversDigits(num, 16));
}


int Decimal_to_Base(unsigned long x, int n) {
/******************
* Function Name: Decimal_to_Base
* Input: unsigned long x(integer), int n(>1)
* Output: int
* Function Operation: the function converts the x variable to the nth base
 *                  if the base is illegal the function will return -1 to signal an error.
******************/

    int converted = 0;
    if ((n < 2) || (n > 9) ) {
        return -1;
    }
    while (x > 0) {
        converted = converted*10 + x%n;
        x = x/n;
    }
    converted = reversDigits(converted, 10);
    return converted;
}

int Base_to_Decimal(unsigned long n, int base) {

/******************
* Function Name: Base_to_Decimal
* Input: unsigned long x(integer, 0<=digits_of_x<n), int n(10>=n>=2)
* Output: integer
* Function Operation: converts the given number in the nth base to a decimal number and returns it.
 * if the number's digits are bigger/equal to the base returns -1 to signal error.
******************/

    int dec_n = 0, index = 0;
    while (n > 0) {
        int last_dig = n%10;
        if (last_dig >= base) {
            printf("Error!");
            return -1;
        }
        dec_n = dec_n + last_dig*pow(base, index);
        n = n/10;
        index = index + 1;

    }
    return dec_n;

}


void ex4(unsigned long n1, unsigned long n2) {

/******************
* Function Name: ex4()
* Input: unsigned long n1(assembled only form 0/1), unsigned long n2(assembled only form 0/1)
* Output: prints
* Function Operation: prints the 2 binary numbers(the biggest first), the carry line if needed and the substraction result
******************/
    unsigned long decn1, decn2, result, biggest_num,biggest_size, count, size_n1, size_n2, size_res;
    if ((Base_to_Decimal(n1, 2) != (-1) )&&(Base_to_Decimal(n2, 2) != (-1) )) {
        decn1 = Base_to_Decimal(n1, 2);
        decn2 = Base_to_Decimal(n2, 2);
        result = Decimal_to_Base(decn1 + decn2, 2);
        size_n1 = (n1 == 0) ? 1  : (log10(n1)/1 + 1);
        size_n2 = (n2 == 0) ? 1  : (log10(n2)/1 + 1);
        size_res = (result == 0) ? 1  : (log10(result)/1 + 1);
        biggest_size = (size_n2 > size_n1) ? size_n2 : size_n1;
        if ((size_res-biggest_size)>0) {
            for( int i = 0; i < (size_res - biggest_size); i++) {
                printf("1");
            }
            for( int i = 0; i < biggest_size; i++) {
                printf("0");
            }
            printf("\n");
        }

        if (decn2 > decn1) {
            for (int i = 0; i < (size_res - size_n2); i++) {
                printf("0");
            }
            printf("%d\n+\n", n2);
            for (int i = 0; i < (size_res - size_n1); i++) {
                printf("0");
            }
            printf("%d\n", n1);

        } else {
            for (int i = 0; i < (size_res - size_n1); i++) {
                printf("0");
            }
            printf("%d\n+\n", n1);
            for (int i = 0; i < (size_res - size_n2); i++) {
                printf("0");
            }
            printf("%d\n", n2);
        }

        for (int i = 1; i < size_res; i++) {
            printf("-");
        }
        printf("-\n");
        printf("%d\n", result);
    } else {
        printf("Error!");
    }


}
void ex5() {
/******************
* Function Name: ex5()
* Input: None
* Output: prints
* Function Operation: prints a butterly in height of 2*n-1 and width of 2*n while n is the given integer in the scanf
******************/

    unsigned int n;
    printf("Enter a number:\n");
    scanf("%d", &n);
    n+=1;
    if (n == 1) {
        printf("##\n##\n");
    }
    else if (n == 2) {
        printf("####\n#**#\n####\n");
    }
    else if (n > 2) {
        // prints the first line of the butterfly

        printf("###");
        for (int i = 0; i < (2*n-6); i++) {
            printf(" ");
        }
        printf("###\n");


        // prints the second-to the middle lines of the butterfly

        for (int row_ind = 2; row_ind <= (n-1); row_ind++) {
            printf("#");
            for (int c = 0; c < (row_ind-1); c++) {
                printf("*");
            }
            printf("#");

            for (int c = 0; c < 2*(n-row_ind-1); c++){
                printf(" ");
            }

            printf("#");
            for (int c = 0; c < (row_ind-1); c++) {
                printf("*");
            }
            printf("#\n");
        }


        //prints the middle line of the butterfly

        printf("#");
        for (int c = 0; c < (2*n -2); c++) {
            printf("*");
        }
        printf("#\n");




        //prints the bottom triangles without the bottom and middle lines

        for (int row_ind = (n-1); row_ind >= 2; row_ind--) {
            printf("#");
            for (int c = 0; c < (row_ind-1); c++) {
                printf("*");
            }
            printf("#");

            for (int c = 0; c < 2*(n-row_ind-1); c++){
                printf(" ");
            }

            printf("#");
            for (int c = 0; c < (row_ind-1); c++) {
                printf("*");
            }
            printf("#\n");
        }

        //prints the last line of the triangle

        printf("###");
        for (int i = 0; i < (2*n-6); i++) {
            printf(" ");
        }
        printf("###\n");
    }


}
int ex6() {
/******************
* Function Name: ex6()
* Input: None
* Output: prints
* Function Operation: input a decimal number and prints the sum of digits it has in binary representation.
******************/
    unsigned long num = 1;
    int num_of_2_powers = 0;
    printf("enter a number:\n");
    scanf("%d", &num);
    while (num>0) {
        num_of_2_powers += (log2(num) >= 0 )? 1: 0;
        int lowest_app = log2(num)/1;
        num = (num - pow(2,lowest_app));
    }
    printf("no of bits those are 1 in its binary representation: %d\n", num_of_2_powers);

}