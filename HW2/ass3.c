#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() 
{       
        
       int ret=fork();
       
       if(ret==0){
         execl("/usr/bin/echo", "echo", "Hello from the child process", NULL);
       }else{
           wait(NULL);
           printf("Parent process done\n");
       }
 
       
        return 0; 
} 
