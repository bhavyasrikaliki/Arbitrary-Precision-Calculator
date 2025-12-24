/*
Documentation:
Name : K. Bhavya
Project Name : Arbitrary Precision Calculator (APC) – Big Integer Operations Using Doubly Linked Lists
Description : This project performs arithmetic operations on very large integers using doubly linked lists.
              Each number is stored digit-by-digit, enabling calculations beyond normal integer limits.
              The program supports big integer addition, subtraction, multiplication, and division.
              It efficiently handles sign, carries, borrows, and leading zeros.
Date : 10-12-2025
sample I/O : 
Input: ./a.out 458765 + 123456
output: 582221
Input: ./a.out -12345678901234567890 - 98765432109876543210
output: -111111111011111111100
Input: ./a.out 123456789 x 987654321
output: 121932631112635269
Input: ./a.out 10000000000000000 / 2
output: 5000000000000000
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<stdarg.h>
#include<string.h>
#include "main.h"

int main(int argc, char *argv[])
{
    if(argc < 4)
    {
        printf("Insufficient arguments!\n");
        printf("Usage: ./a.out <num1> <operator> <num2>\n");
        return FAILURE;
    }

    if(strlen(argv[2]) != 1)
    {
        printf("Invalid operator length!\n");
        return FAILURE;
    }
    
    // Initialize doubly linked list heads and tails
    DLL *head1 = NULL, *tail1 = NULL;
    DLL *head2 = NULL, *tail2 = NULL;
    DLL *head3 = NULL, *tail3 = NULL;

    // Get signs of result
    int sign1 = get_sign(argv[1]);
    int sign2 = get_sign(argv[3]);
    int result_sign = 1;

    // Convert input strings to doubly linked lists
    string_to_list(argv[1], &head1, &tail1);
    string_to_list(argv[3], &head2, &tail2);

    char operator = *argv[2];

    switch(operator)
    {
        case '+':
        {
            if(sign1 ==1 && sign2 == 1)
            { 
                addition(&head1,&tail1,&head2,&tail2,&head3,&tail3);  
                result_sign = 1;
            }
            else if((sign1 == 1 && sign2 == -1))
            {
                check_operator(argv[1],&head1,&tail1,argv[3],&head2,&tail2);
                subtraction(&head1,&tail1,&head2,&tail2,&head3,&tail3);
                if(neg == 1)
                {
                    result_sign = -1;
                }
                else
                {
                    result_sign =1;
                }
                neg =0;
            } 
            else if((sign1 == -1 && sign2 ==1))
            {
                check_operator(argv[1],&head1,&tail1,argv[3],&head2,&tail2);
                subtraction(&head1,&tail1,&head2,&tail2,&head3,&tail3);
                if(neg == 1)
                {
                    result_sign = -1;
                }
                else
                {
                    result_sign =1;
                }
                neg =0;
            } 
            else if(sign1 == -1 && sign2 == -1)
            {
                addition(&head1,&tail1,&head2,&tail2,&head3,&tail3);  
                result_sign = -1;
            }
            break;
        }
        case '-':
        {
            if (sign1 == 1 && sign2 == 1) 
            {
                //  positive - positive
                subtraction(&head1, &tail1, &head2, &tail2, &head3, &tail3);
                result_sign = (neg == 1) ? -1 : 1;
                neg = 0;
            }
            else if (sign1 == 1 && sign2 == -1) 
            {
                // positive - negative  => addition
                addition(&head1, &tail1, &head2, &tail2, &head3, &tail3);
                result_sign = 1;
            }
            else if (sign1 == -1 && sign2 == 1) 
            {
                // negative - positive  => -(abs(num1) + num2)
                addition(&head1, &tail1, &head2, &tail2, &head3, &tail3);
                result_sign = -1;
            }
            else if (sign1 == -1 && sign2 == -1) 
            {
                // -num1 - (-num2) = num2 - num1
                subtraction(&head2, &tail2, &head1, &tail1, &head3, &tail3);
                result_sign = (neg == 1) ? -1 : 1;
                neg = 0;
            }
            break;
        }

        case 'x':
        {
            if((sign1 ==1 && sign2 == 1) || (sign1 == -1 && sign2 == -1))
            {
                multiplication(&head1,&tail1,&head2,&tail2,&head3,&tail3);
                result_sign = 1;
            }
            else if((sign1 == 1 && sign2 == -1) || (sign1 == -1 && sign2 ==1))
            {
                multiplication(&head1,&tail1,&head2,&tail2,&head3,&tail3);
                result_sign = -1;
            }
            break;
        }
        case '/':
        {
            if((sign1 ==1 && sign2 == 1) || (sign1 == -1 && sign2 == -1))
            {
                division(&head1,&tail1,&head2,&tail2,&head3,&tail3);
                result_sign = 1;
            }
            else if((sign1 == 1 && sign2 == -1) || (sign1 == -1 && sign2 ==1))
            {
                division(&head1,&tail1,&head2,&tail2,&head3,&tail3);
                result_sign = -1;
            }
            break;
            
        }
        default : 
        {
            printf("Invalid operator\n");
            break;
        }
    }
    if (result_sign == -1 && !(head3->data == 0 && head3->next == NULL))
    {
        printf("-");
    }
    
    print_list(head3);

    return SUCCESS;
}
    