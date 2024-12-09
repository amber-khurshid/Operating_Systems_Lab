#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // Add this to declare exit()

int main()
{
    int i, pid;
    pid = fork();

    if (pid > 0)
    {
        // Parent process
        sleep(2);
        exit(0); 
    }
    else if (pid == 0)
    {
        // Child process
        for (i = 0; i < 5; i++)
        {
            printf("My parent is %d\n", getppid()); // Get PPID (Parent PID)
            sleep(1);
        }
    }

    return 0;
}
