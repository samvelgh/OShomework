#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h> 
int main() 
{ 
	printf("This is parent");
        fork();
 
        fork();
 
        fork();
 
       
        return 0; 
} 
