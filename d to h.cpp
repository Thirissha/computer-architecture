#include <stdio.h>

int main() {
    int decimalNumber;
    char hexadecimalNumber[100];
    int i = 0;

    // Get the decimal number
    printf("Enter a decimal number: ");
    scanf("%d", &decimalNumber);

    // Handle zero case
    if (decimalNumber == 0) {
        printf("The hexadecimal representation is: 0\n");
        return 0;
    }

    // Convert decimal to hexadecimal
    while (decimalNumber != 0) {
        int temp = decimalNumber % 16;

        if (temp < 10) {
            hexadecimalNumber[i] = temp + 48; // Convert integer to character (0-9)
        } else {
            hexadecimalNumber[i] = temp + 55; // Convert integer to character (A-F)
        }

        decimalNumber /= 16;
        i++;
    }

    // Print the hexadecimal number in reverse order
    printf("The hexadecimal representation is: ");
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", hexadecimalNumber[j]);
    }
    printf("\n");

    return 0;
}

