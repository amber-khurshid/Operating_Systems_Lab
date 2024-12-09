#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t p1, p2, p3;

    p1 = fork();

    p2 = fork();

    if (p2 == 0) {
        p3 = fork();
    }

    printf("Process: PID = %d, PPID = %d\n", getpid(), getppid());

    sleep(30);

    return 0;
}