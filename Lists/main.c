#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct IntElement
{
    struct IntElement* next;
    int data;
} list;

int main()
{
    printf("Hello, world");


    return 0;
}

void push(struct IntElement* list, int data)
{
    struct IntElement* item = (struct IntElement*)(malloc(sizeof(struct IntElement)));

}

int pop(struct IntElement* list)
{

}