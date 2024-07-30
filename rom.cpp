#include <stdio.h>

int main() {
    int num;  
    printf("Enter a number: ");
    scanf("%d", &num);
    printf("The memory address of num is: %p\n", (void*)&num);  
    return 0;
}
