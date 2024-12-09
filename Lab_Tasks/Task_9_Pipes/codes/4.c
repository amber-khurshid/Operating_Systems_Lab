#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main()
{
    int pid; // for storing fork() return
    int pfd[2]; // for pipe file descriptors
    char aString[20] = ""; 
    
    pipe(pfd); // create our pipe
    pid = fork();
    
    if (pid == 0) // For child process
    {
        write(pfd[1], "Hello", 5); // Write "Hello" to the pipe
        
    }
    else // For parent process
    {
        // Before the read call
        printf("Before read: '%s'\n", aString);
        
        // Read from pipe
        read(pfd[0], aString, 5); 
        aString[5] = '\0'; 
        
        // After the read call
        printf("After read:  '%s'\n", aString);
    }

  
    return 0;
}
