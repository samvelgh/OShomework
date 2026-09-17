#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main() 
{       
        
       int ret=fork();
       
       if(ret==0){
           int ret1=fork();
           if(ret1==0){
               execl("/usr/bin/ls", "ls", NULL);
           }else{
               wait(NULL);
		execl("/bin/date", "date", (char *) NULL);
           }
           
        //  execl("/bin/date", "date", (char *) NULL); exec can here to
       }else{
           wait(NULL);
           printf("Parent process done\n");
       }
 
       
        return 0; 
} 
