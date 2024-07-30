#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_to_binary(int num, int* binary, int size) {
    for (int i = 0; i < size; i++) {
        binary[size - i - 1] = (num >> i) & 1;
    }
}

// Function to convert binary representation to integer
int binary_to_int(int* binary, int size) {
    int num = 0;
    for (int i = 0; i < size; i++) {
        num = (num << 1) | binary[i];
    }
    return num;
}

// Function to perform binary subtraction
void binary_subtraction(int* A, int* B, int size) {
    int borrow = 0;
    for (int i = size - 1; i >= 0; i--) {
        int diff = A[i] - B[i] - borrow;
        if (diff < 0) {
            A[i] = diff + 2;
            borrow = 1;
        } else {
            A[i] = diff;
            borrow = 0;
        }
    }
}

// Function to perform binary addition
void binary_addition(int* A, int* B, int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        int sum = A[i] + B[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
}

// Function to perform a left shift on register A and Q
void left_shift(int* A, int* Q, int* Qn, int size) {
    int temp = A[0];
    for (int i = 0; i < size - 1; i++) {
        A[i] = A[i + 1];
    }
    A[size - 1] = Q[0];
    for (int i = 0; i < size - 1; i++) {
        Q[i] = Q[i + 1];
    }
    Q[size - 1] = *Qn;
    *Qn = temp;
}

// Function to compute the two's complement of a binary number
void twos_complement(int* binary, int size) {
    int carry = 1;
    for (int i = size - 1; i >= 0; i--) {
        if (binary[i] == 0) {
            binary[i] = 1 - carry;
            carry = 0;
        } else {
            binary[i] = 1 - carry;
        }
    }
}

// Non-Restoring Division Algorithm
void non_restoring_division(int dividend, int divisor) {
    int size = sizeof(int) * 8;
    int M[size], Q[size], A[size], negM[size];
    int Qn = 0; // Qn is the extra bit

    memset(M, 0, size * sizeof(int));
    memset(Q, 0, size * sizeof(int));
    memset(A, 0, size * sizeof(int));
    memset(negM, 0, size * sizeof(int));

    int_to_binary(dividend, Q, size);
    int_to_binary(divisor, M, size);

    // Compute -M for subtraction
    memcpy(negM, M, size * sizeof(int));
    twos_complement(negM, size); // Get -M by computing the two's complement

    // Non-Restoring Division Process
    for (int i = 0; i < size; i++) {
        left_shift(A, Q, &Qn, size);
        binary_subtraction(A, M, size);

        if (A[0] == 1) { // If A < 0, restore A
            binary_addition(A, M, size);
            Q[size - 1] = 0;
        } else { // Otherwise, set Q to 1
            Q[size - 1] = 1;
        }
    }

    // Convert the result from binary to decimal
    int quotient = binary_to_int(Q, size);
    printf("Quotient: %d\n", quotient);
}

int main() {
    int dividend = 14;
    int divisor = 3;

    non_restoring_division(dividend, divisor);

    return 0;
}

