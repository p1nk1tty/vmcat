#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 256

typedef struct {
    int data[STACK_SIZE];
    int sp; // Stack pointer
} Stack;

void init_stack(Stack *stack);
void push(Stack *stack, int value);
int pop(Stack *stack);
int peek(Stack *stack);

#endif // STACK_H
