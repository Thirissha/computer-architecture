#include <stdio.h>
#include <string.h>
#include <math.h>

// Function to convert binary to decimal
int binaryToDecimal(long long binaryNumber) {
    int decimalNumber = 0, i = 0, remainder;

    while (binaryNumber != 0) {
        remainder = binaryNumber % 10;
        binaryNumber /= 10;
        decimalNumber += remainder * pow(2, i);
        ++i;
    }

    return decimalNumber;
}

// Function to convert decimal to octal
int decimalToOctal(int decimalNumber) {
    int octalNumber = 0, i = 1;

    while (decimalNumber != 0) {
        octalNumber += (decimalNumber % 8) * i;
        decimalNumber /= 8;
        i *= 10;
    }

    return octalNumber;
}

int main() {
    long long binaryNumber;
    int decimalNumber, octalNumber;

    // Get the binary number
    printf("Enter a binary number: ");
    scanf("%lld", &binaryNumber);

    // Convert binary to decimal
    decimalNumber = binaryToDecimal(binaryNumber);

    // Convert decimal to octal
    octalNumber = decimalToOctal(decimalNumber);

    // Print the octal number
    printf("The octal representation is: %d\n", octalNumber);

    return 0;
}

