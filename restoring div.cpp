#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to perform binary addition
void binary_addition(int* A, int* M, int size) {
    int carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        int sum = A[i] + M[i] + carry;
        A[i] = sum % 2;
        carry = sum / 2;
    }
}

// Function to perform binary subtraction
void binary_subtraction(int* A, int* M, int size) {
    int borrow = 0;
    for (int i = size - 1; i >= 0; i--) {
        int diff = A[i] - M[i] - borrow;
        if (diff < 0) {
            A[i] = diff + 2;
            borrow = 1;
        } else {
            A[i] = diff;
            borrow = 0;
        }
    }
}

// Function to left shift the register A and Q
void left_shift(int* A, int* Q, int* Qn, int size) {
    for (int i = 0; i < size - 1; i++) {
        A[i] = A[i + 1];
    }
    A[size - 1] = Q[0];
    for (int i = 0; i < size - 1; i++) {
        Q[i] = Q[i + 1];
    }
    Q[size - 1] = *Qn;
}

// Function to restore the value of A
void restore(int* A, int* M, int size) {
    binary_addition(A, M, size);
}

int main() {
    int dividend, divisor;
    printf("Enter the dividend: ");
    scanf("%d", &dividend);
    printf("Enter the divisor: ");
    scanf("%d", &divisor);

    if (divisor == 0) {
        printf("Error: Division by zero is not allowed.\n");
        return -1;
    }

    int size = sizeof(int) * 8;
    int A[size], Q[size], M[size];
    int Qn = 0; // Extra bit for quotient

    // Initialize the arrays
    memset(A, 0, size * sizeof(int));
    memset(Q, 0, size * sizeof(int));
    memset(M, 0, size * sizeof(int));

    // Convert dividend and divisor to binary
    for (int i = 0; i < size; i++) {
        Q[size - i - 1] = (dividend >> i) & 1;
        M[size - i - 1] = (divisor >> i) & 1;
    }

    // Perform restoring division
    for (int i = 0; i < size; i++) {
        left_shift(A, Q, &Qn, size);

        binary_subtraction(A, M, size);

        if (A[0] == 1) {
            Q[size - 1] = 0;
            restore(A, M, size);
        } else {
            Q[size - 1] = 1;
        }
    }

    // Convert the quotient and remainder to decimal
    int quotient = 0, remainder = 0;
    for (int i = 0; i < size; i++) {
        quotient = (quotient << 1) | Q[i];
        remainder = (remainder << 1) | A[i];
    }

    printf("Quotient: %d\n", quotient);
    printf("Remainder: %d\n", remainder);

    return 0;
}

