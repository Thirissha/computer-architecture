#include <stdio.h>
int main() {
    int num;  
    int *ptr; 
    printf("Enter a number: ");
    scanf("%d", &num); 
    ptr = &num;
    printf("The value of num is: %d\n", num);  
    printf("The memory address of num is: %p\n", (void*)&num);  
    printf("The value at the memory address pointed by ptr is: %d\n", *ptr); 
    return 0;
}
