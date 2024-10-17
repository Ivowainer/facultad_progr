#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int is_one(long n, int b)
{
    return (n & (1 << b)) != 0;
}

void print_bi(int a)
{
    for (int i = 31; i >= 0; i--)
    {
        printf("%d", is_one(a, i));
        if (i % 8 == 0)
            printf(" ");
    }
    printf("\n");
}

void print_string_bytes(char *a)
{
    int len = strlen(a);
    int len_bytes = len * 8;

    for (int i = 0; i < len; i++)
    {
        for (int j = 7; j >= 0; j--)
        {
            printf("%d", is_one(a[i], j));
        }
        printf(" ");
    }
    printf("\n");
}

void print_last_4_digit(int a)
{
    for (int i = 7; i >= 0; i--)
    {
        printf("%d", (a & (1 << i)) != 0);
    }
}

void swap_triple(int a, int b, int c)
{
    print_bi(a);
    print_bi(b);
    print_bi(c);
    printf("\n");

    a = a ^ b;
    b = a ^ b;
    a = a ^ b;

    a = a ^ c;
    c = a ^ c;
    a = a ^ c;

    print_bi(a);
    print_bi(b);
    print_bi(c);
    printf("\n");
}

void xor_password_encode(int key, char *password)
{

    // algorithm
    for (int i = 0; i < strlen(password); i++)
        password[i] = password[i] ^ key;
    print_string_bytes(password);
}

void xor_password_decode(int key, char *password)
{
    xor_password_encode(key, password);
}

int main(int argc, char *argv[])
{
    int key = atoi(argv[1]);
    char *password = argv[2];
    /* if (key > 127 || key < -127)
    {
        printf("La key no puede ser mayor 127 o menor a 127\n");
        return -1;
    } */

    /* printf("%d, %s\n", key, password); */

    // print
    print_string_bytes(password);
    for (int i = 0; i < strlen(password); i++)
    {
        print_last_4_digit(key);
        printf(" ");
    }
    printf("\n");

    xor_password_encode(key, password);
    xor_password_decode(key, password);

    return 0;
}