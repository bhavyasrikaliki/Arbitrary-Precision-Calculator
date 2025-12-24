#include "main.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

/*addition function*/
int addition(DLL **head1,DLL **tail1,DLL **head2,DLL **tail2,DLL **head3,DLL **tail3)
{
    DLL *temp1 = *tail1;
    DLL *temp2 = *tail2;
    int carry =0;

    //process from lsb to msb
    while(temp1 != NULL || temp2 !=NULL)
    {
        int digit1 = 0;
        int digit2= 0;

        if(temp1!=NULL)
        {
            digit1 = temp1->data;
        }
        if(temp2 != NULL)
        {
            digit2 =temp2->data;
        }

        int res = digit1+ digit2 + carry;

        if((res)>9)
        {
            carry =1;
            res = res%10;
        }
        else
        {
            carry =0;
        }

        insert_at_first(head3,tail3,res);

        if(temp1 != NULL)
        {
            temp1 = temp1->prev;
        }
        if(temp2 != NULL)
        {
            temp2 = temp2->prev;
        }
    }

    //if an extra carry remains, add it to the front
    if (carry ==1)
    {
        insert_at_first(head3,tail3,1);
    }

    remove_leading_zeros(head3,tail3);
    return SUCCESS;
}

/*subtraction function*/
int subtraction(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3) 
{

    if (head1 == NULL || head2 == NULL) 
    {
        return FAILURE;
    }

    // Step 1: Remove leading zeros from inputs
    remove_leading_zeros(head1, tail1);
    remove_leading_zeros(head2, tail2);

    // Step 2: Determine if result should be negative
    if (!compare_lists(*head1, *head2)) 
    {
        DLL *tmp_h = *head1, *tmp_t = *tail1;
        *head1 = *head2;
        *tail1 = *tail2;
        *head2 = tmp_h;
        *tail2 = tmp_t;
        neg = 1;
    } 
    else 
    {
        neg = 0;
    }

    // Step 3: Subtract digits from tail (least significant)
    DLL *t1 = *tail1;
    DLL *t2 = *tail2;
    int borrow = 0;

    while (t1) 
    {
        int d1 = t1->data;
        int d2 = (t2) ? t2->data : 0;
        int sub = d1 - d2 - borrow;

        if (sub < 0) 
        {
            sub += 10;
            borrow = 1;
        } 
        else 
        {
            borrow = 0;
        }

        DLL *new_node = malloc(sizeof(DLL));
        if (new_node == NULL) 
        {
            return FAILURE;
        }

        new_node->data = sub;
        new_node->prev = NULL;
        new_node->next = *head3;
        if (*head3) 
        {
            (*head3)->prev = new_node;
        }
        *head3 = new_node;
        if (*tail3 == NULL) 
        {
            *tail3 = new_node;
        }

        t1 = t1->prev;
        if (t2) t2 = t2->prev;
    }

    // Step 4: Remove leading zeros from result
    remove_leading_zeros(head3, tail3);

    return SUCCESS;
}

/*multiplication function*/
int multiplication(DLL **head1,DLL **tail1,DLL **head2,DLL **tail2,DLL **head3,DLL **tail3)
{
    DLL *temp2 = *tail2;
    *head3 = NULL;
    *tail3 = NULL;

    int i, zeroes=0;

    DLL *head4 = NULL;
    DLL *tail4 = NULL;
    while(temp2 != NULL)
    {
        DLL *temp1 = *tail1;
        int carry =0;

        //multiply digit of list2 with all digits of list1
        while(temp1 != NULL)
        {
            int digit1 =0;
            int digit2 =0;

            if(temp1 != NULL)
            {
                digit1 = temp1->data;
            }
            if(temp2 != NULL)
            {
                digit2 = temp2->data;
            }

            int digit = digit1 * digit2 +carry;
            carry = digit/10;
            digit = digit%10;

            insert_at_first(&head4,&tail4,digit);
            temp1 = temp1->prev;
        }
        if(carry>0)
        {
            insert_at_first(&head4,&tail4,carry);
        }

        //add zeroes according to place value
        for(i=0;i<zeroes;i++)
        {
            insert_at_last(&head4,&tail4,0);
        }

        //add the partial result to the final result
        if(*head3 == NULL)
        {
            DLL *temp = head4;
            while(temp != NULL)
            {
                insert_at_last(head3,tail3,temp->data);
                temp = temp->next;
            }
        }
        else
        {
            DLL *head5 = NULL;
            DLL *tail5 = NULL;

            addition(head3,tail3,&head4,&tail4,&head5,&tail5);

            delete_list(head3,tail3);

            DLL *t = head5;
            while(t !=NULL)
            {
                insert_at_last(head3,tail3,t->data);
                t = t->next;
            }

            delete_list(&head5,&tail5);
        }

        delete_list(&head4,&tail4);

        zeroes++;
        temp2 = temp2->prev;
    }
    return SUCCESS;
}

/* BIG INTEGER LONG DIVISION (FAST, APC COMPLIANT) */
int division(DLL **head1, DLL **tail1, DLL **head2, DLL **tail2, DLL **head3, DLL **tail3) 
{

    // Remove leading zeros from dividend and divisor
    remove_leading_zeros(head1, tail1);
    remove_leading_zeros(head2, tail2);

    // Handle divide by zero
    if ((*head2)->data == 0 && (*head2)->next == NULL) 
    {
        printf("Error: Division by zero!\n");
        return FAILURE;
    }

    DLL *remainder_head = NULL, *remainder_tail = NULL;
    DLL *cur = *head1;

    while (cur) 
    {
        // Append current digit to remainder
        DLL *new_node = malloc(sizeof(DLL));
        if (new_node == NULL) 
        {
            return FAILURE;
        }
        new_node->data = cur->data;
        new_node->next = NULL;
        new_node->prev = remainder_tail;

        if (remainder_tail) 
        {
            remainder_tail->next = new_node;
        }
        remainder_tail = new_node;
        if (remainder_head == NULL) 
        {
            remainder_head = new_node;
        }

        // Remove leading zeros from remainder
        remove_leading_zeros(&remainder_head, &remainder_tail);

        // Count how many times divisor fits into remainder
        int count = 0;
        while (compare_lists(remainder_head, *head2)) 
        {
            DLL *temp_head = NULL, *temp_tail = NULL;

            // Subtract divisor from remainder
            subtraction(&remainder_head, &remainder_tail, head2, tail2, &temp_head, &temp_tail);

            // Free old remainder
            DLL *temp = remainder_head;
            while (temp) 
            {
                DLL *next = temp->next;
                free(temp);
                temp = next;
            }

            remainder_head = temp_head;
            remainder_tail = temp_tail;

            count++;
        }

        // Append count to quotient
        DLL *q_node = malloc(sizeof(DLL));
        if (q_node == NULL) 
        {
            return FAILURE;
        }
        q_node->data = count;
        q_node->next = NULL;
        q_node->prev = *tail3;
        if (*tail3) 
        {
            (*tail3)->next = q_node;
        }
        *tail3 = q_node;
        if (*head3 == NULL) 
        {
            *head3 = q_node;
        }

        cur = cur->next;
    }

    remove_leading_zeros(head3, tail3);
    return SUCCESS;
}
