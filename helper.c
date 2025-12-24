#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include "main.h"

int neg = 0;    //global variable to track negative result

//Insert at the beginning of the doubly linked list
int insert_at_first(DLL **head, DLL ** tail, int n_data)
{
    DLL *new = malloc(sizeof(DLL));
    if(new == NULL)
    {
        return FAILURE;
    }

    new -> data = n_data;
    new -> prev = NULL;
    new -> next = NULL;

    if(*head == NULL)
    {
        *head = new;
        new->next = NULL;
        *tail = new;
    }
    else
    {
        (*head) -> prev = new;
        new->next = *head;
        *head = new;
    }

    return SUCCESS;
}

//Insert at the end of the doubly linked list
int insert_at_last(DLL **head, DLL ** tail, int n_data)
{
    DLL *new = malloc (sizeof(DLL));
    if(new == NULL)
    {
        return FAILURE;
    }

    new -> data = n_data;
    new -> next = NULL;
    new -> prev = NULL;

    if(*head == NULL)
    {
        *head = new;
        *tail = new;
    }
    else
    {
        (*tail) -> next = new;
        new -> prev = *tail;
        *tail = new;
    }

    return SUCCESS;
}

// Function to print the list
int print_list(DLL *head)
{
    if(head == NULL)
    {
        printf("List is empty\n");
        return FAILURE;
    }
    else
    {
        if(neg == 1)
        {
            printf("-");
        }
        while(head->next != NULL)
        {
            printf("%d", head -> data);
            head = head -> next;
        }
        printf("%d\n", head -> data);
    }
    return SUCCESS;
}

// Function to delete the list
int delete_list(DLL **head, DLL **tail)
{
    DLL *temp = *head;
    while(temp != NULL)
    {
        *head = temp -> next;
        free(temp);
        temp = *head;
    }
    *head = NULL;
    *tail = NULL;
    return SUCCESS;
}

// Function to convert string to list
int string_to_list(const char *str, DLL **head, DLL **tail)
{
    int i = 0;

    if(str[0] == '-')
    {
        i = 1; // Start from index 1 if negative sign is present
    }
    int len = strlen(str);

    while(i < len)
    {
        if(!(isdigit(str[i])))
        {
            return FAILURE;
        }

        int digit = str[i] - '0'; // Convert character to integer
        insert_at_last(head, tail, digit);
        i++;
    }
    return SUCCESS;
}

// Function to get the sign of the number
int get_sign(const char *str)
{
    if(str[0] == '-')
    {
        return -1; // Negative
    }
    return 1; // Positive
}

// Function to check operator and adjust lists accordingly
int check_operator(const char *str1, DLL **head1, DLL **tail1, const char *str2, DLL **head2, DLL **tail2)
{
    int sign1 = (str1[0] == '-');
    int sign2 = (str2[0] == '-');

    int len1 = strlen(str1) - sign1;
    int len2 = strlen(str2) - sign2;

    //Compare lengths 
    if (len1 > len2)
    {
        return SUCCESS;
    }

    if (len2 > len1)
    {
        neg = 1;
        DLL *h = *head1; *head1 = *head2; *head2 = h;
        DLL *t = *tail1; *tail1 = *tail2; *tail2 = t;
        return SUCCESS;
    }

    //Same length → compare digit-by-digit
    for (int i = 0; i < len1; i++)
    {
        char c1 = str1[i + sign1];
        char c2 = str2[i + sign2];

        if (c1 > c2)
            return SUCCESS;

        if (c2 > c1)
        {
            neg = 1;
            DLL *h = *head1; *head1 = *head2; *head2 = h;
            DLL *t = *tail1; *tail1 = *tail2; *tail2 = t;
            return SUCCESS;
        }
    }
    return SUCCESS; // numbers are equal
}


// Function to remove leading zeros from the list
void remove_leading_zeros(DLL **head, DLL **tail) 
{
    while (*head && (*head)->data == 0 && (*head)->next) 
    {
        DLL *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }
    if (*head == NULL) 
    {
        *head = malloc(sizeof(DLL));
        if (!*head) return;
        (*head)->data = 0;
        (*head)->prev = (*head)->next = NULL;
        *tail = *head;
    }
}


/* SIMPLE compare function*/
int compare_lists(DLL *num1, DLL *num2) 
{
    DLL *t1 = num1, *t2 = num2;
    int len1 = 0, len2 = 0;
    while (t1) 
    { 
        len1++;
        t1 = t1->next;
    }
    while (t2) 
    { 
        len2++; 
        t2 = t2->next; 
    }

    if (len1 > len2) 
    {
        return 1;
    }
    if (len1 < len2) 
    {
        return 0;
    }

    t1 = num1; t2 = num2;
    while (t1 && t2) 
    {
        if (t1->data > t2->data) return 1;
        if (t1->data < t2->data) return 0;
        t1 = t1->next;
        t2 = t2->next;
    }
    return 1; // equal numbers
}