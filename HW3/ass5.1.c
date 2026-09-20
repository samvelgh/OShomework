#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();

    if (pid == 0)
    {
        printf("Child finished\n");
        exit(0);
    }
    else
    {
        wait(NULL);
        printf("Parent collected child\n");
    }

    return 0;
}
