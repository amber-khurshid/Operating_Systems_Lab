#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int i, pid;
    pid = fork();

    if (pid > 0)
    {
        // Parent process sleeps for 120 seconds
        sleep(120);
    }
    else if (pid == 0)
    {
        // Child process exits immediately
        exit(0);
    }

    return 0;
}
