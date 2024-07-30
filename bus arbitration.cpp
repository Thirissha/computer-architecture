#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_DEVICES 4       // Number of I/O devices
#define ACCESS_TIME 2       // Time each device has access to the bus (in seconds)
#define SIMULATION_TIME 10  // Total time to run the simulation (in seconds)

// Function to simulate I/O operation for a device
void perform_io_operation(int device_id) {
    printf("Device %d is accessing the bus.\n", device_id);
    sleep(ACCESS_TIME);  // Simulate the time the device is accessing the bus
}

int main() {
    int current_device = 0;
    int elapsed_time = 0;

    printf("Starting bus arbitration simulation using round-robin method.\n");

    while (elapsed_time < SIMULATION_TIME) {
        // Simulate each device accessing the bus in round-robin order
        for (int i = 0; i < NUM_DEVICES; i++) {
            perform_io_operation(current_device);
            current_device = (current_device + 1) % NUM_DEVICES;  // Move to the next device in round-robin
            elapsed_time += ACCESS_TIME;
            if (elapsed_time >= SIMULATION_TIME) {
                break;
            }
        }
    }

    printf("Simulation completed.\n");

    return 0;
}

