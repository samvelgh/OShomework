#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t child1, child2;

    child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1 is running\n");
        exit(0);
    }

    child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2 is running\n");
        exit(1);
    }

    waitpid(child1, &status, 0);

    if (WIFEXITED(status)){
        printf("Child 1 exited normally with status %d\n",WEXITSTATUS(status));
    }else{
        printf("Child 1 exited with an error\n");
    }

    waitpid(child2, &status, 0);

    if (WIFEXITED(status)){
        printf("Child 2 exited normally with status %d\n",WEXITSTATUS(status));
    }else{
        printf("Child 2 exited with an error\n");
    }
    return 0;
}
