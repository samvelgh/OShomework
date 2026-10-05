#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>  

int main() {
    int *arr;
    int n=10;
    int newN=5;


    arr = (int *)malloc(n*sizeof(int));
    int actual_size = malloc_usable_size(arr);
    printf("actual_size = %d\n", actual_size);

    if (arr == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }
   
    for (int i = 0; i < n; i++) {
        printf("enter arr[%d] digit\n",i);
        scanf("%d", &arr[i]);
      
    }
    
    int *new_arr = (int *)realloc(arr, newN * sizeof(int));
    
    if (new_arr == NULL) {
        printf("Memory reallocation failed!\n");
        free(arr);  // Free the original memory if realloc fails
        return 1;
    }
    printf("\nAfter realloc:\n");
    for (int i = 0; i < newN; i++) {
        printf("new_arr[%d] = %d\n", i, new_arr[i]);
    }

    

    free(arr);

    return 0;
}
