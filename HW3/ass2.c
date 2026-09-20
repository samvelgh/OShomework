#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    int status;

    int child1 = fork();

    if (child1 == 0)
    {
        printf("Child 1 : %d\n", getpid());
	exit(1);       
    }

    int child2 = fork();

    if (child2 == 0)
    {
        printf("Child 2 : %d\n", getpid());
        exit(2);
    }

    printf("Parent PID: %d\n", getpid());

    waitpid(child1, &status, 0);
    printf("Child 1 exit status: %d\n", WEXITSTATUS(status));

    wait(&status);
    printf("Child 2 exit status: %d\n", WEXITSTATUS(status));

    return 0;
}
