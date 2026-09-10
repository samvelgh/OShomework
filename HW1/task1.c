#include <stdio.h>

int main() {
    int n = 4478;

    int *ptr=&n;

    printf("Address of num with pointer: %p\n", ptr); 
    printf("Address of num: %p\n", &n);       
    *ptr=7767;
    printf("new value of num: %d\n", n);       
    return 0;
}
