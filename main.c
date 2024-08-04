#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/stack.h"

#define NUM_REGISTERS 6

typedef enum {
    PSH,
    ADD,
    SUB,
    MUL,
    DIV,
    POP,
    SET,
    JMP,
    JZ,
    JNZ,
    HLT
} InstructionSet;

typedef enum {
    A, B, C, D, E, F,
    IP, NUM_OF_REGISTERS
} Registers;

typedef struct {
    int registers[NUM_OF_REGISTERS];
    Stack stack;
    int *instructions;
    int running;
} VM;

void init_vm(VM *vm, int *program) {
    memset(vm->registers, 0, sizeof(vm->registers));
    init_stack(&vm->stack);
    vm->instructions = program;
    vm->registers[IP] = 0;
    vm->running = 1;
}

void fetch(VM *vm) {
    vm->registers[IP]++;
}

int decode_execute(VM *vm) {
    int instr = vm->instructions[vm->registers[IP]];

    switch (instr) {
        case PSH: {
            int value = vm->instructions[++vm->registers[IP]];
            push(&vm->stack, value);
            break;
        }
        case ADD: {
            int a = pop(&vm->stack);
            int b = pop(&vm->stack);
            push(&vm->stack, a + b);
            break;
        }
        case SUB: {
            int a = pop(&vm->stack);
            int b = pop(&vm->stack);
            push(&vm->stack, b - a);
            break;
        }
        case MUL: {
            int a = pop(&vm->stack);
            int b = pop(&vm->stack);
            push(&vm->stack, a * b);
            break;
        }
        case DIV: {
            int a = pop(&vm->stack);
            int b = pop(&vm->stack);
            if (a != 0) {
                push(&vm->stack, b / a);
            } else {
                printf("Division by zero error\n");
                return -1;
            }
            break;
        }
        case POP: {
            int value = pop(&vm->stack);
            printf("%d\n", value);
            break;
        }
        case SET: {
            int reg = vm->instructions[++vm->registers[IP]];
            int value = vm->instructions[++vm->registers[IP]];
            vm->registers[reg] = value;
            break;
        }
        case JMP: {
            int addr = vm->instructions[++vm->registers[IP]];
            vm->registers[IP] = addr - 1; // -1 to offset the upcoming IP increment
            break;
        }
        case JZ: {
            int addr = vm->instructions[++vm->registers[IP]];
            if (pop(&vm->stack) == 0) {
                vm->registers[IP] = addr - 1;
            }
            break;
        }
        case JNZ: {
            int addr = vm->instructions[++vm->registers[IP]];
            if (pop(&vm->stack) != 0) {
                vm->registers[IP] = addr - 1;
            }
            break;
        }
        case HLT: {
            vm->running = 0;
            break;
        }
        default: {
            printf("Unknown instruction: %d\n", instr);
            return -1;
        }
    }

    return 0;
}

void run(VM *vm) {
    while (vm->running) {
        if (decode_execute(vm) == -1) break;
        fetch(vm);
    }
}

int main() {
    int program[] = {
        PSH, 5,
        PSH, 10,
        ADD,
        POP,
        PSH, 5,
        PSH, 10,
        MUL,
        POP,
        PSH, 10,
        PSH, 5,
        DIV,
        POP,
        PSH, 10,
        PSH, 5,
        SUB,
        POP,
        PSH, 1,  // Push 1 (true) onto the stack
        JZ, 24,  // If top of the stack is 0, jump to instruction at index 24 (HALT)
        PSH, 0,  // Push 0 (false) onto the stack
        JNZ, 24, // If top of the stack is not 0, jump to instruction at index 24 (HALT)
        PSH, 42, // This instruction will be skipped if JZ or JNZ conditions are met
        POP,
        HLT
    };

    VM vm;
    init_vm(&vm, program);
    run(&vm);

    return 0;
}
