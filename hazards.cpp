#include <stdio.h>
#include <stdbool.h>

#define NUM_INSTRUCTIONS 5

// Define instruction structure
typedef struct {
    char opcode[10];
    int src1, src2, dest;
    bool isBranch;
    int branchTarget;
} Instruction;

// Function to check for data hazard (RAW)
bool checkDataHazard(Instruction prev, Instruction curr) {
    if ((curr.src1 == prev.dest || curr.src2 == prev.dest) && !prev.isBranch) {
        return true;
    }
    return false;
}

// Function to check for control hazard
bool checkControlHazard(Instruction instr) {
    return instr.isBranch;
}

int main() {
    // Example instruction set
    Instruction instructions[NUM_INSTRUCTIONS] = {
        {"ADD", 1, 2, 3, false, 0},
        {"SUB", 3, 4, 5, false, 0},
        {"MUL", 5, 6, 7, false, 0},
        {"BEQ", 7, 8, 0, true, 2}, // Branch to instruction index 2 if equal
        {"DIV", 7, 3, 9, false, 0}
    };

    // Simulate pipeline
    for (int i = 1; i < NUM_INSTRUCTIONS; i++) {
        printf("Checking instruction %d:\n", i);

        // Check for data hazard
        if (checkDataHazard(instructions[i-1], instructions[i])) {
            printf("Data hazard detected between instruction %d and %d\n", i-1, i);
            // Insert NOP or stall pipeline (for demonstration, just print a message)
            printf("Inserting NOP to resolve data hazard\n");
        }

        // Check for control hazard
        if (checkControlHazard(instructions[i])) {
            printf("Control hazard detected at instruction %d\n", i);
            // Handle branch prediction or pipeline flush (for demonstration, just print a message)
            printf("Handling branch prediction/pipeline flush\n");
        }

        printf("\n");
    }

    return 0;
}

