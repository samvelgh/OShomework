#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30,21,321};
    int *ptr=&arr[0];
    
    for (int i = 0; i < 5; i++) {
        printf("Value of arr[%d]: %d\n", i, *(ptr + i)); 
        
    }
    for (int i = 0; i < 5; i++) {
        *(ptr+i)=*(ptr+i)+23;
        
    }
    for (int i = 0; i < 5; i++) {
        printf("Value of arr[%d]with pointer: %d\n", i, *(ptr + i)); 
        
    }
    for (int i = 0; i < 5; i++) {
        printf("Value of arr[%d] with arrname: %d\n", i,arr[i]); 
        
    }
    
}
