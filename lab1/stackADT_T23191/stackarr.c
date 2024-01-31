#include <stdlib.h>

typedef struct
{
    char *data;
    int capacity;
    int top;
    int size;
} ArrayStack;

void *newStack()
{
    int capacity = 100;
    ArrayStack *stack = (ArrayStack *)malloc(sizeof(ArrayStack));
    stack->data = (char *)malloc(sizeof(char) * capacity);
    stack->capacity = capacity;
    stack->top = -1;
    stack->size = 0;
    return stack;
}

int isEmpty(void *stack)
{
    ArrayStack *arrStack = (ArrayStack *)stack;
    return arrStack->top == -1;
}

void push(void *stack, char value)
{
    ArrayStack *arrStack = (ArrayStack *)stack;
    if (arrStack->top == arrStack->capacity - 1)
        return;
    arrStack->data[++arrStack->top] = value;
    arrStack->size++;
}

char pop(void *stack)
{
    ArrayStack *arrStack = (ArrayStack *)stack;
    if (isEmpty(arrStack))
        return -1;
    char value = arrStack->data[arrStack->top--];
    arrStack->size--;
    return value;
}

char peek(void *stack)
{
    ArrayStack *arrStack = (ArrayStack *)stack;
    if (isEmpty(arrStack))
        return -1;
    return arrStack->data[arrStack->top];
}

int getSize(void *stack)
{
    ArrayStack *arrStack = (ArrayStack *)stack;
    return arrStack->size;
}

void destroy(void *stack)
{
    ArrayStack *arrStack = (ArrayStack *)stack;
    free(arrStack->data);
    free(arrStack);
}
