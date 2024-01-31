#include <stdio.h>
#include "stack.h"

int main()
{
    void *stack = newStack();
    char choice;

    while (1)
    {
        printf("Stack Menu:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Is Empty?\n");
        printf("5. Get Size\n");
        printf("6. Quit\n");

        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            printf("Enter a character to push: ");
            char value;
            scanf(" %c", &value);
            push(stack, value);
            break;
        case '2':
            if (!isEmpty(stack))
            {
                printf("Popped: %c\n", pop(stack));
            }
            else
            {
                printf("Stack is empty.\n");
            }
            break;
        case '3':
            if (!isEmpty(stack))
            {
                printf("Top: %c\n", peek(stack));
            }
            else
            {
                printf("Stack is empty.\n");
            }
            break;
        case '4':
            if (isEmpty(stack))
            {
                printf("Stack is empty.\n");
            }
            else
            {
                printf("Stack is not empty.\n");
            }
            break;
        case '5':
            printf("Size of the stack: %d\n", getSize(stack));
            break;
        case '6':
            destroy(stack);
            return 0;
        default:
            printf("Invalid choice. Please try again.\n");
            break;
        }
    }

    return 0;
}