#ifndef MAIN_H
#define MAIN_H

#define SUCCESS 0
#define FAILURE 1

extern int neg;

typedef struct DLL
{
    int data;
    struct DLL *prev;
    struct DLL *next;
}DLL;


int insert_at_first(DLL **head, DLL **tail, int data);
int insert_at_last(DLL **head, DLL **tail, int data);
int get_sign(const char *str);
void remove_leading_zeros(DLL **head, DLL **tail);
int compare_lists(DLL *num1, DLL *num2);
int string_to_list(const char *str, DLL **head, DLL **tail);
int check_operator(const char *str1, DLL **head1, DLL **tail1, const char *str2,DLL **head2, DLL **tail2);
int addition(DLL **head1,DLL **tail1,DLL **head2,DLL **tail2,DLL **head3,DLL **tail3);
int subtraction(DLL **head1,DLL **tail1,DLL **head2,DLL **tail2,DLL **head3,DLL **tail3);
int multiplication(DLL **head1,DLL **tail1,DLL **head2,DLL **tail2,DLL **head3,DLL **tail3);
int division(DLL **head1,DLL **tail1,DLL **head2,DLL **tail2,DLL **head3,DLL **tail3);
int print_list(DLL *head);
int delete_list(DLL **head, DLL **tail);

#endif