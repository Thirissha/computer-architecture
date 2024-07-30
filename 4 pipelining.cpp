#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_STAGES 4
#define BUFFER_SIZE 100

typedef struct {
    int data;
} Instruction;

typedef struct {
    Instruction instruction;
    int valid;
} PipelineStage;

void fetch(PipelineStage *stage, int data) {
    stage->instruction.data = data;
    stage->valid = 1;
    printf("Fetch: %d\n", data);
}

void decode(PipelineStage *stage) {
    if (stage->valid) {
        printf("Decode: %d\n", stage->instruction.data);
    }
}

void execute(PipelineStage *stage) {
    if (stage->valid) {
        printf("Execute: %d\n", stage->instruction.data);
    }
}

void write_back(PipelineStage *stage) {
    if (stage->valid) {
        printf("Write Back: %d\n", stage->instruction.data);
        stage->valid = 0;
    }
}

void pipeline_step(PipelineStage pipeline[]) {
    // Process stages in reverse order to simulate pipeline progression
    write_back(&pipeline[3]);
    execute(&pipeline[2]);
    decode(&pipeline[1]);
    fetch(&pipeline[0], rand() % 100);
}

void pipeline_shift(PipelineStage pipeline[]) {
    for (int i = NUM_STAGES - 1; i > 0; i--) {
        pipeline[i] = pipeline[i - 1];
    }
    pipeline[0].valid = 0; // New fetch stage
}

int main() {
    PipelineStage pipeline[NUM_STAGES] = {0};

    for (int cycle = 0; cycle < 10; cycle++) {
        printf("Cycle %d:\n", cycle + 1);
        pipeline_step(pipeline);
        pipeline_shift(pipeline);
        sleep(1); // Simulate time delay for each cycle
        printf("\n");
    }

    return 0;
}

