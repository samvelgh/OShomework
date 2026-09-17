#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() 
{       
        
       int ret=fork();
       
       if(ret==0){
           execl("/usr/bin/ls", "ls", NULL);
           sleep(5);
           printf("Child process finished.\n");
           exit(0);
       }else{
		printf("Parent process: Waiting for child to finish...\n");
           wait(NULL);
           printf("Parent process done\n");
       }
 
       
        return 0; 
} 
