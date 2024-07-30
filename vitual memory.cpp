#include <stdio.h>
#include <stdlib.h>

#define PAGE_SIZE 1024       // Size of a page in bytes
#define NUM_PAGES 16         // Number of pages in physical memory
#define VIRTUAL_ADDRESS_SPACE  (NUM_PAGES * PAGE_SIZE) // Virtual address space

typedef unsigned char byte;  // Define byte as an alias for unsigned char

// Page table entry
typedef struct {
    int frame_number;  // Physical frame number (or -1 for invalid)
    int valid;         // Valid bit to indicate if the page is in memory
} PageTableEntry;

// Page table
typedef struct {
    PageTableEntry entries[NUM_PAGES];
} PageTable;

// Physical memory
typedef struct {
    byte memory[NUM_PAGES * PAGE_SIZE];
} PhysicalMemory;

// Initialize page table
void initialize_page_table(PageTable *pt) {
    for (int i = 0; i < NUM_PAGES; i++) {
        pt->entries[i].frame_number = -1;  // Page not in memory
        pt->entries[i].valid = 0;          // Page is invalid
    }
}

// Initialize physical memory
void initialize_physical_memory(PhysicalMemory *pm) {
    // Physical memory is initialized to zero by default
    // No explicit initialization needed
}

// Translate virtual address to physical address
int translate_address(PageTable *pt, int virtual_address) {
    int page_number = virtual_address / PAGE_SIZE;
    int offset = virtual_address % PAGE_SIZE;

    if (page_number >= NUM_PAGES || !pt->entries[page_number].valid) {
        printf("Page fault at virtual address %d\n", virtual_address);
        return -1;  // Page fault
    }

    int frame_number = pt->entries[page_number].frame_number;
    return frame_number * PAGE_SIZE + offset;
}

// Simulate reading from virtual memory
byte read_from_virtual_memory(PageTable *pt, PhysicalMemory *pm, int virtual_address) {
    int physical_address = translate_address(pt, virtual_address);
    if (physical_address == -1) {
        exit(EXIT_FAILURE);  // Exit on page fault
    }
    return pm->memory[physical_address];
}

// Simulate writing to virtual memory
void write_to_virtual_memory(PageTable *pt, PhysicalMemory *pm, int virtual_address, byte value) {
    int physical_address = translate_address(pt, virtual_address);
    if (physical_address == -1) {
        exit(EXIT_FAILURE);  // Exit on page fault
    }
    pm->memory[physical_address] = value;
}

int main() {
    PageTable page_table;
    PhysicalMemory physical_memory;

    initialize_page_table(&page_table);
    initialize_physical_memory(&physical_memory);

    // Example setup: Map virtual page 1 to physical frame 2
    page_table.entries[1].frame_number = 2;
    page_table.entries[1].valid = 1;

    // Write to virtual address 1 * PAGE_SIZE + 100
    int virtual_address = 1 * PAGE_SIZE + 100;
    byte value = 42;
    write_to_virtual_memory(&page_table, &physical_memory, virtual_address, value);

    // Read from the same virtual address
    byte read_value = read_from_virtual_memory(&page_table, &physical_memory, virtual_address);
    printf("Read value %d from virtual address %d\n", read_value, virtual_address);

    return 0;
}

