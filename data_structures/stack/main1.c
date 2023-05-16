#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    int data;
    struct item * next;
} Item;

typedef struct {
    Item *top;
} Stack;


Stack* init()
{
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack != NULL) {
        stack->top = NULL;
    }
    return stack;
}

int push(Stack *stack, int value)
{
    Item *new = (Item*)malloc(sizeof(Item));
    if (new != NULL) {
        new->data = value;
        new->next = stack->top;
        stack->top = new;
        return 0;
    }
    return -1;
}


int show(Stack *stack)
{
    Item *top = stack->top;
    while (top != NULL) {
        printf("%d\n",top->data);
        top = top->next;
    }
    return 0;
}

int destroy(Stack *stack)
{
    Item *top = stack->top;
    Item *dest;
    while (top != NULL) {
        dest = top;
        top = top->next;
        free(dest);
    }
    free(stack);
    return 0;
}

int main()
{
    printf("Stack\n");
    Stack *stack = init();
    if (stack == NULL) {printf("ERROR: Failed to allocate Stack!\n"); return -1;}
    if (push(stack, 2) == -1) {printf("ERROR: Failed to allocate memory for the first Item!\n"); return -2;}
    if (push(stack, 5) == -1) {printf("ERROR: Failed to allocate memory for the second Item!\n"); return -3;}
    if (push(stack, 8) == -1) {printf("ERROR: Failed to allocate memory for the third Item!\n"); return -4;}
    printf("All Items added OK!\nList of Items:\n");
    show(stack);
    destroy(stack);
    return 0;
}
