#include <stdlib.h>

typedef struct Node
{
    char data;
    struct Node *next;
} Node;

typedef struct
{
    Node *top;
    int size;
} LinkedListStack;

void *newStack()
{
    LinkedListStack *stack = (LinkedListStack *)malloc(sizeof(LinkedListStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

int isEmpty(void *stack)
{
    LinkedListStack *llStack = (LinkedListStack *)stack;
    return llStack->top == NULL;
}

void push(void *stack, char value)
{
    LinkedListStack *llStack = (LinkedListStack *)stack;
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = llStack->top;
    llStack->top = newNode;
    llStack->size++;
}

char pop(void *stack)
{
    LinkedListStack *llStack = (LinkedListStack *)stack;
    if (isEmpty(llStack))
        return -1;
    Node *temp = llStack->top;
    char value = temp->data;
    llStack->top = temp->next;
    free(temp);
    llStack->size--;
    return value;
}

char peek(void *stack)
{
    LinkedListStack *llStack = (LinkedListStack *)stack;
    if (isEmpty(llStack))
        return -1;
    return llStack->top->data;
}

int getSize(void *stack)
{
    LinkedListStack *llStack = (LinkedListStack *)stack;
    return llStack->size;
}

void destroy(void *stack)
{
    LinkedListStack *llStack = (LinkedListStack *)stack;
    while (!isEmpty(llStack))
        pop(llStack);
    free(llStack);
}
