#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_INSTRUCTIONS 5

// Instruction structure
typedef struct {
    char instruction[20];
    int data;
} Instruction;

// Pipeline stages
Instruction IF_stage;
Instruction IE_stage;

void fetch(Instruction *instr_memory, int pc) {
    if (pc < NUM_INSTRUCTIONS) {
        IF_stage = instr_memory[pc];
        printf("Fetched instruction: %s %d\n", IF_stage.instruction, IF_stage.data);
    } else {
        printf("No more instructions to fetch.\n");
        strcpy(IF_stage.instruction, "NOP");
    }
}

void execute() {
    IE_stage = IF_stage;
    if (strcmp(IE_stage.instruction, "NOP") != 0) {
        printf("Executing instruction: %s %d\n", IE_stage.instruction, IE_stage.data);
        // Example execution: increment data
        IE_stage.data++;
        printf("Result: %d\n", IE_stage.data);
    } else {
        printf("No instruction to execute.\n");
    }
}

int main() {
    // Instruction memory
    Instruction instr_memory[NUM_INSTRUCTIONS] = {
        {"LOAD", 1},
        {"ADD", 2},
        {"SUB", 3},
        {"MUL", 4},
        {"DIV", 5}
    };

    int pc = 0;

    // Simulating the two-stage pipeline
    while (pc <= NUM_INSTRUCTIONS) {
        execute();
        fetch(instr_memory, pc);
        pc++;
    }

    return 0;
}

