#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Element
{
    struct Element * next;
    void *data;
} Element;


bool createStack(Element **);
bool deleteStack(Element **);
bool push(Element **, void *);
bool pop(Element **, void **);

int main()
{
    printf("Hello, world\n");

    Element *stack;
    if (!createStack(&stack)){
        return -1;
    }

    int i;
    for (i = 0; i < 10; ++i){
        int* j = malloc(sizeof(int));
        *j = i;
        push(&stack, j);
    }

    for (i = 0; i < 10; ++i){
        void *ptr = NULL;
        pop(&stack, &ptr);
        printf("%d\n", *((int*)ptr));
    }


    return 0;
}

bool push(Element **stack, void *data)
{
    Element *next = malloc(sizeof(Element));
    if (!next){
        return false;
    }

    next->data = data;

    if (!(*stack)){
        next->next = NULL;
        *stack = next;
    } else {
        next->next = *stack;
        *stack = next;
    }

    return  true;
}

bool pop(Element **stack, void **data)
{
    if (!(*stack)){
        return false;
    }

    *data = (*stack)->data;
    Element* tmp = *stack;
    *stack = (*stack)->next;
    free(tmp);
    return true;
}

bool createStack(Element **stack)
{
    // Assume stack is NOT null

    *stack = NULL;
    return true;
}

bool deleteStack(Element **stack)
{
    // Assume stack is NOT null

    Element *next;

    /* A bit elegant solution would be */
    /*while (*stack){
        next = (*stack)->next;
        free(*stack);
        *stack = next;
    }

    return true;*/

    if (*stack == NULL) {
        return true;
    }


    while ((next = (*stack)->next) != NULL){
        free (*stack);
        *stack = next;
    }
    free(*stack);
    return true;
}
