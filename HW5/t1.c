#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>  

int main() {
    int *arr;
    int n;
    int sum=0;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    arr = (int *)malloc(n * sizeof(int));
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
    for (int i = 0; i < n; i++) {
        printf("arr[%d] = %d\n", i, arr[i]);  
        sum+=arr[i];
    }
    printf("sum: %d",sum);

    free(arr);

    return 0;
}
