#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        printf("Parent sleeping...\n");
        sleep(20);
    }

    return 0;
}
