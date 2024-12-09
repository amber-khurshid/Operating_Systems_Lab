#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>  

int main()
{
    printf("Hello");
    kill(getpid(), 9); // kill the current process
    printf("Goodbye");
    return 0;
}
