#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void init_stack(Stack *stack) {
    stack->sp = -1;
}

void push(Stack *stack, int value) {
    if (stack->sp < STACK_SIZE - 1) {
        stack->data[++stack->sp] = value;
    } else {
        printf("Stack overflow\n");
        exit(1);
    }
}

int pop(Stack *stack) {
    if (stack->sp >= 0) {
        return stack->data[stack->sp--];
    } else {
        printf("Stack underflow\n");
        exit(1);
    }
}

int peek(Stack *stack) {
    if (stack->sp >= 0) {
        return stack->data[stack->sp];
    } else {
        printf("Stack is empty\n");
        exit(1);
    }
}
