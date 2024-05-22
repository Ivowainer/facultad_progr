#include <stdio.h>
#include <stdlib.h>

#ifndef __STACK_H__
#define __STACK_H__

typedef struct _SNode
{
    void *data;
    struct _SNode *next;

} SNode;

typedef struct
{
    SNode *first;
    SNode *last;
} Stack;

typedef void *(CopyFunc)(void *);
typedef void (*VisitorFunc)(void *);
typedef void (*DestroyerFunc)(void *);

Stack *stack_create();
void stack_push(Stack *stack, void *data, CopyFunc copy);
void stack_map(Stack *stack, VisitorFunc visitor);
void stack_pop(Stack *stack, DestroyerFunc destr);

int stack_is_empty(Stack *stack);
void *stack_top(Stack *stack);

#endif