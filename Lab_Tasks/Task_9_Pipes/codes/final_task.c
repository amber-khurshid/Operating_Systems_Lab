#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define BUFFER_SIZE 256

int main() {
    int pfd1[2]; 
    int pfd2[2]; 
    char message[BUFFER_SIZE];
    pid_t pid;

    // Create pipes
    if (pipe(pfd1) == -1 || pipe(pfd2) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // Child process
        close(pfd1[1]);
        close(pfd2[0]);

        while (1) {
            // Read message from Pipe 1
            read(pfd1[0], message, BUFFER_SIZE);
            printf("P1 SAYS: %s\n", message);

            // Write message to Pipe 2
            printf("P2: ");
            fgets(message, BUFFER_SIZE, stdin);
            write(pfd2[1], message, strlen(message) + 1);
        }

        close(pfd1[0]);
        close(pfd2[1]);
    } else { // Parent process
        close(pfd1[0]);
        close(pfd2[1]);

        while (1) {
            // Write message to Pipe 1
            printf("P1: ");
            fgets(message, BUFFER_SIZE, stdin);
            write(pfd1[1], message, strlen(message) + 1);

            // Read message from Pipe 2
            read(pfd2[0], message, BUFFER_SIZE);
            printf("P2 SAYS: %s\n", message);
        }

        close(pfd1[1]);
        close(pfd2[0]);
    }

    return 0;
}