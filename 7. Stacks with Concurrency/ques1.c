#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int buffer[50000];
    int position;
} Stack;

Stack* create_stack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    stack->position = 0;
    return stack;
}

void push(Stack* stack, int value) {
    if (stack->position < 50000) {
        stack->buffer[stack->position] = value;
        stack->position++;
    } else {
        printf("Stack Overflow: Cannot push element, stack is full\n");
    }
}

int pop(Stack* stack) {
    if (stack->position > 0) {
        stack->position--;
        return stack->buffer[stack->position];
    } else {
        printf("Stack Underflow: Cannot pop element, stack is empty\n");
        return -1; 
    }
}

void print_stack(Stack* stack) {
    if (stack->position == 0) {
        printf("Stack is empty\n");
    } else {
        printf("Stack elements:\n");
        for (int i = stack->position - 1; i >= 0; i--) {
            printf("%d\n", stack->buffer[i]);
        }
    }
}

int main() {
    Stack* stack = create_stack();
    for (int i = 0; i < 10; i++) {
        push(stack, i);
    }

    print_stack(stack);
    for (int i = 0; i < 5; i++) {
        int popped_element = pop(stack);
        printf("Popped element: %d\n", popped_element);
    }

    print_stack(stack);
    free(stack);
    return 0;
}
