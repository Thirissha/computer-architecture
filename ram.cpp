#include <stdio.h>
#include <stdlib.h>

#define RAM_SIZE 1024  // Size of RAM in bytes

typedef unsigned char byte;  // Define byte as an alias for unsigned char

typedef struct {
    byte memory[RAM_SIZE];  // Array to simulate RAM
} RAM;

// Function to initialize RAM
void initialize_ram(RAM *ram) {
    for (int i = 0; i < RAM_SIZE; i++) {
        ram->memory[i] = 0;  // Set all bytes to 0
    }
}

// Function to write a byte to a specific address in RAM
void write_to_ram(RAM *ram, int address, byte value) {
    if (address >= 0 && address < RAM_SIZE) {
        ram->memory[address] = value;
    } else {
        printf("Error: Address out of bounds.\n");
    }
}

// Function to read a byte from a specific address in RAM
byte read_from_ram(RAM *ram, int address) {
    if (address >= 0 && address < RAM_SIZE) {
        return ram->memory[address];
    } else {
        printf("Error: Address out of bounds.\n");
        return 0;  // Return 0 if address is out of bounds
    }
}

int main() {
    RAM ram;  // Create an instance of RAM
    initialize_ram(&ram);  // Initialize RAM

    // Example usage
    int address = 100;  // Address to write/read
    byte value = 42;    // Value to write

    printf("Writing %d to address %d.\n", value, address);
    write_to_ram(&ram, address, value);  // Write value to RAM

    byte read_value = read_from_ram(&ram, address);  // Read value from RAM
    printf("Read %d from address %d.\n", read_value, address);

    return 0;
}

