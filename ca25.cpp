#include <stdio.h>
#include <stdlib.h>

#define NUM_INSTRUCTIONS 5
#define NUM_REGISTERS 8

typedef enum { ADD, SUB, LOAD, STORE, BRANCH, NOP } InstructionType;

typedef struct {
    InstructionType type;
    int src1;
    int src2;
    int dest;
} Instruction;

typedef struct {
    Instruction instruction;
    int valid;
} PipelineStage;

// Example instructions
Instruction instructions[NUM_INSTRUCTIONS] = {
    {LOAD, 0, -1, 1},     // LOAD R1
    {ADD, 1, 2, 3},       // ADD R3 = R1 + R2
    {STORE, 3, -1, 4},    // STORE R3 to R4
    {SUB, 1, 3, 5},       // SUB R5 = R1 - R3
    {BRANCH, 0, -1, -1}   // BRANCH (depends on implementation)
};

// Function to detect data hazards
void detect_data_hazards(Instruction* instrs, int num_instrs) {
    for (int i = 0; i < num_instrs - 1; i++) {
        Instruction current = instrs[i];
        Instruction next = instrs[i + 1];

        if (next.src1 == current.dest || next.src2 == current.dest) {
            printf("Data hazard between instruction %d and %d\n", i, i + 1);
        }
    }
}

// Function to detect control hazards
void detect_control_hazards(Instruction* instrs, int num_instrs) {
    for (int i = 0; i < num_instrs; i++) {
        if (instrs[i].type == BRANCH) {
            printf("Control hazard at instruction %d\n", i);
            break;
        }
    }
}

// Function to detect structural hazards
void detect_structural_hazards(PipelineStage* stages, int num_stages) {
    for (int i = 0; i < num_stages; i++) {
        if (stages[i].valid && stages[i].instruction.type == LOAD) {
            for (int j = i + 1; j < num_stages; j++) {
                if (stages[j].valid && stages[j].instruction.type == LOAD) {
                    printf("Structural hazard between stage %d and %d\n", i, j);
                    break;
                }
            }
        }
    }
}

int main() {
    // Initialize pipeline stages
    PipelineStage pipeline[NUM_INSTRUCTIONS];
    for (int i = 0; i < NUM_INSTRUCTIONS; i++) {
        pipeline[i].valid = 0; // Initialize all stages as invalid
    }

    // Detect data hazards in the instruction sequence
    detect_data_hazards(instructions, NUM_INSTRUCTIONS);

    // Detect control hazards in the instruction sequence
    detect_control_hazards(instructions, NUM_INSTRUCTIONS);

    // Simulate pipeline stages
    for (int i = 0; i < NUM_INSTRUCTIONS; i++) {
        pipeline[i].instruction = instructions[i];
        pipeline[i].valid = 1;
    }

    // Detect structural hazards in the pipeline stages
    detect_structural_hazards(pipeline, NUM_INSTRUCTIONS);

    return 0;
}

