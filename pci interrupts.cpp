#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024  // Size of the buffer to simulate DMA transfer

// Function to simulate a DMA transfer
void dma_transfer(void *src, void *dst, size_t size) {
    // Simulate the data transfer by copying memory
    memcpy(dst, src, size);
}

int main() {
    // Allocate source and destination buffers
    void *src_buffer = malloc(BUFFER_SIZE);
    void *dst_buffer = malloc(BUFFER_SIZE);

    if (!src_buffer || !dst_buffer) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Initialize source buffer with some data
    memset(src_buffer, 'A', BUFFER_SIZE);

    // Simulate DMA transfer
    dma_transfer(src_buffer, dst_buffer, BUFFER_SIZE);

    // Verify that the data was copied correctly
    if (memcmp(src_buffer, dst_buffer, BUFFER_SIZE) == 0) {
        printf("DMA simulation successful: data was copied correctly.\n");
    } else {
        printf("DMA simulation failed: data mismatch.\n");
    }

    // Clean up
    free(src_buffer);
    free(dst_buffer);

    return 0;
}

