#include <stdio.h>

int main() {
    int num = 42;
    int *pt1=&num; 
    int **pt2=&pt1;     


    printf("Value pointed to by ptr1: %d\n", *pt1);  
    printf("Value pointed to by ptr2: %d\n", **pt2); 

    return 0;
}
