#include <stdio.h>

int main() {
    int n;
    unsigned long long factorial = 1;

    // Get the number for which factorial is to be calculated
    printf("Enter an integer: ");
    scanf("%d", &n);

    // Check if the user entered a negative number
    if (n < 0) {
        printf("Factorial of a negative number doesn't exist.\n");
    } else {
        // Calculate factorial
        for (int i = 1; i <= n; i++) {
            factorial *= i;
        }

        // Print the factorial
        printf("Factorial of %d = %llu\n", n, factorial);
    }

    return 0;
}

