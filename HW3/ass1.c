#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>
#include <stdint.h>


int main()
{
    int ret=fork();
    
    if(ret==0){
        printf("child id: %jd\n", (intmax_t)getpid());
    }else{
    printf("parent id: %jd\n", (intmax_t)getpid());
    }
    return 0;
}
