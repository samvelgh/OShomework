#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

void first()
{
    printf("first function called\n");
}

void second()
{
    printf("second function called\n");
}

int main()
{
    atexit(first);
    atexit(second);

    printf("running\n");

    exit(0);
}
