#include <stdio.h>

int main() {
 
    char str[]="Hello";
    char *ptr=&str[0];
    
    printf("my string:");
    while(*(ptr)!=NULL){ //there we need to use null for chararacter
        
        printf("%c", *(ptr)); 
        ptr=ptr+1;
    }
    int count=0;
	ptr=str;    
    while(*(ptr)!='\0'){ 
        
        count++;
        ptr=ptr+1;
    }
    printf("\ncount: %d\n", count);  

    return 0;
}
