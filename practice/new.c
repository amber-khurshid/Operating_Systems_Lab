// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// #define BUFFER_SIZE 256

// void PV1(int pipe_fd[2]) {
//     close(pipe_fd[0]); // Close unused read end

//     // Predefined list of video files
//     char *video_files[] = {"video1.mp4", "video2.mp4", "video3.mp4"};
//     int num_files = sizeof(video_files) / sizeof(video_files[0]);

//     for (int i = 0; i < num_files; i++) {
//         write(pipe_fd[1], video_files[i], strlen(video_files[i]) + 1);
//     }

//     close(pipe_fd[1]); // Close write end
//     exit(0);
// }

// void PV2(int pipe_fd1[2], int pipe_fd2[2]) {
//     close(pipe_fd1[1]); // Close unused write end
//     close(pipe_fd2[0]); // Close unused read end

//     char buffer[BUFFER_SIZE];
//     while (read(pipe_fd1[0], buffer, BUFFER_SIZE) > 0) {
//         strcat(buffer, "_transcoded");
//         write(pipe_fd2[1], buffer, strlen(buffer) + 1);
//     }

//     close(pipe_fd1[0]); // Close read end
//     close(pipe_fd2[1]); // Close write end
//     exit(0);
// }

// void PV3(int pipe_fd2[2], int pipe_fd3[2]) {
//     close(pipe_fd2[1]); // Close unused write end
//     close(pipe_fd3[0]); // Close unused read end

//     char buffer[BUFFER_SIZE];
//     while (read(pipe_fd2[0], buffer, BUFFER_SIZE) > 0) {
//         strcat(buffer, "_QC_Passed");
//         write(pipe_fd3[1], buffer, strlen(buffer) + 1);
//     }

//     close(pipe_fd2[0]); // Close read end
//     close(pipe_fd3[1]); // Close write end
//     exit(0);
// }

// void PV4(int pipe_fd3[2]) {
//     close(pipe_fd3[1]); // Close unused write end

//     char buffer[BUFFER_SIZE];
//     while (read(pipe_fd3[0], buffer, BUFFER_SIZE) > 0) {
//         printf("Distributed: %s\n", buffer);
//     }

//     close(pipe_fd3[0]); // Close read end
//     exit(0);
// }

// int main() {
//     int pipe_fd1[2], pipe_fd2[2], pipe_fd3[2];

//     if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1 || pipe(pipe_fd3) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid_t pid1 = fork();
//     if (pid1 == 0) {
//         PV1(pipe_fd1);
//     }

//     pid_t pid2 = fork();
//     if (pid2 == 0) {
//         PV2(pipe_fd1, pipe_fd2);
//     }

//     pid_t pid3 = fork();
//     if (pid3 == 0) {
//         PV3(pipe_fd2, pipe_fd3);
//     }

//     pid_t pid4 = fork();
//     if (pid4 == 0) {
//         PV4(pipe_fd3);
//     }

//     close(pipe_fd1[0]);
//     close(pipe_fd1[1]);
//     close(pipe_fd2[0]);
//     close(pipe_fd2[1]);
//     close(pipe_fd3[0]);
//     close(pipe_fd3[1]);

//     wait(NULL);
//     wait(NULL);
//     wait(NULL);
//     wait(NULL);

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/wait.h>

// #define BUFFER_SIZE 256
// #define MAX_FILES 100

// void PV1(int pipe_fd[2]) {
//     close(pipe_fd[0]);

//     char video_files[MAX_FILES][BUFFER_SIZE];
//     int num_files = 0;
    
//     printf("PV1: Searching for MP4 files...\n");

//     FILE *fp = popen("ls *.mp4", "r");
//     if (fp == NULL) {
//         perror("popen");
//         exit(EXIT_FAILURE);
//     }

//     while (fgets(video_files[num_files], BUFFER_SIZE, fp) != NULL) {
//         video_files[num_files][strcspn(video_files[num_files], "\n")] = '\0';
//         printf("PV1: Found file: %s\n", video_files[num_files]);
//         num_files++;
//     }
//     pclose(fp);

//     for (int i = 0; i < num_files; i++) {
//         write(pipe_fd[1], video_files[i], strlen(video_files[i]) + 1);
//     }
    
//     // Write special marker to indicate end of files
//     char end_marker = '\0';
//     write(pipe_fd[1], &end_marker, 1);
    
//     close(pipe_fd[1]);
//     exit(0);
// }

// void PV2(int pipe_fd1[2], int pipe_fd2[2]) {
//     close(pipe_fd1[1]);
//     close(pipe_fd2[0]);

//     char buffer[BUFFER_SIZE];
//     while (1) {
//         memset(buffer, 0, BUFFER_SIZE);
//         ssize_t bytes_read = read(pipe_fd1[0], buffer, BUFFER_SIZE);
        
//         if (bytes_read <= 0 || buffer[0] == '\0') break;
        
//         printf("PV2: Processing: %s\n", buffer);
//         strcat(buffer, "_transcoded");
//         write(pipe_fd2[1], buffer, strlen(buffer) + 1);
//     }

//     // Write end marker
//     char end_marker = '\0';
//     write(pipe_fd2[1], &end_marker, 1);

//     close(pipe_fd1[0]);
//     close(pipe_fd2[1]);
//     exit(0);
// }

// void PV3(int pipe_fd2[2], int pipe_fd3[2]) {
//     close(pipe_fd2[1]);
//     close(pipe_fd3[0]);

//     char buffer[BUFFER_SIZE];
//     while (1) {
//         memset(buffer, 0, BUFFER_SIZE);
//         ssize_t bytes_read = read(pipe_fd2[0], buffer, BUFFER_SIZE);
        
//         if (bytes_read <= 0 || buffer[0] == '\0') break;
        
//         printf("PV3: Quality checking: %s\n", buffer);
//         strcat(buffer, "_QC_Passed");
//         write(pipe_fd3[1], buffer, strlen(buffer) + 1);
//     }

//     // Write end marker
//     char end_marker = '\0';
//     write(pipe_fd3[1], &end_marker, 1);

//     close(pipe_fd2[0]);
//     close(pipe_fd3[1]);
//     exit(0);
// }

// void PV4(int pipe_fd3[2]) {
//     close(pipe_fd3[1]);

//     char buffer[BUFFER_SIZE];
//     while (1) {
//         memset(buffer, 0, BUFFER_SIZE);
//         ssize_t bytes_read = read(pipe_fd3[0], buffer, BUFFER_SIZE);
        
//         if (bytes_read <= 0 || buffer[0] == '\0') break;
        
//         printf("Distributed: %s\n", buffer);
//     }

//     close(pipe_fd3[0]);
//     exit(0);
// }

// int main() {
//     int pipe_fd1[2], pipe_fd2[2], pipe_fd3[2];

//     if (pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1 || pipe(pipe_fd3) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     pid_t pid1 = fork();
//     if (pid1 < 0) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid1 == 0) {
//         PV1(pipe_fd1);
//     }

//     pid_t pid2 = fork();
//     if (pid2 < 0) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid2 == 0) {
//         PV2(pipe_fd1, pipe_fd2);
//     }

//     pid_t pid3 = fork();
//     if (pid3 < 0) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid3 == 0) {
//         PV3(pipe_fd2, pipe_fd3);
//     }

//     pid_t pid4 = fork();
//     if (pid4 < 0) {
//         perror("fork");
//         exit(EXIT_FAILURE);
//     }
//     if (pid4 == 0) {
//         PV4(pipe_fd3);
//     }

//     // Parent closes all pipes
//     close(pipe_fd1[0]);
//     close(pipe_fd1[1]);
//     close(pipe_fd2[0]);
//     close(pipe_fd2[1]);
//     close(pipe_fd3[0]);
//     close(pipe_fd3[1]);

//     // Wait for all children
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
//     waitpid(pid3, NULL, 0);
//     waitpid(pid4, NULL, 0);

//     return 0;
// }

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/wait.h>

// #define BUFFER_SIZE 256

// // PV1: Input Process
// void PV1_Process(int write_fd) {
//     // Open a pipe to execute the "ls *.mp4" command
//     FILE *fp = popen("ls *.mp4", "r");
//     if (fp == NULL) {
//         perror("popen");
//         exit(EXIT_FAILURE);
//     }

//     char filename[BUFFER_SIZE];
//     // Read each filename and send it to PV2
//     while (fgets(filename, BUFFER_SIZE, fp) != NULL) {
//         filename[strcspn(filename, "\n")] = '\0'; // Remove newline character
//         write(write_fd, filename, strlen(filename) + 1);
//     }

//     pclose(fp);
//     close(write_fd);
//     exit(EXIT_SUCCESS);
// }

// // PV2: Transcoding Process
// void PV2_Process(int read_fd, int write_fd) {
//     char buffer[BUFFER_SIZE];

//     // Read filenames from PV1, process, and send to PV3
//     while (read(read_fd, buffer, BUFFER_SIZE) > 0) {
//         strcat(buffer, "_transcoded");
//         write(write_fd, buffer, strlen(buffer) + 1);
//     }

//     close(read_fd);
//     close(write_fd);
//     exit(EXIT_SUCCESS);
// }

// // PV3: Quality Control Process
// void PV3_Process(int read_fd, int write_fd) {
//     char buffer[BUFFER_SIZE];

//     // Read filenames from PV2, process, and send to PV4
//     while (read(read_fd, buffer, BUFFER_SIZE) > 0) {
//         strcat(buffer, "_QC_Passed");
//         write(write_fd, buffer, strlen(buffer) + 1);
//     }

//     close(read_fd);
//     close(write_fd);
//     exit(EXIT_SUCCESS);
// }

// // PV4: Distribution Process
// void PV4_Process(int read_fd) {
//     char buffer[BUFFER_SIZE];

//     // Read filenames from PV3 and distribute (print)
//     while (read(read_fd, buffer, BUFFER_SIZE) > 0) {
//         printf("Distributed: %s\n", buffer);
//     }

//     close(read_fd);
//     exit(EXIT_SUCCESS);
// }

// int main() {
//     int pipe_PV1_PV2[2], pipe_PV2_PV3[2], pipe_PV3_PV4[2];

//     // Create the necessary pipes
//     if (pipe(pipe_PV1_PV2) == -1 || pipe(pipe_PV2_PV3) == -1 || pipe(pipe_PV3_PV4) == -1) {
//         perror("pipe");
//         exit(EXIT_FAILURE);
//     }

//     // Fork PV1 (Input Process)
//     if (fork() == 0) {
//         close(pipe_PV1_PV2[0]); // Close unused read end
//         close(pipe_PV2_PV3[0]); close(pipe_PV2_PV3[1]);
//         close(pipe_PV3_PV4[0]); close(pipe_PV3_PV4[1]);
//         PV1_Process(pipe_PV1_PV2[1]);
//     }

//     // Fork PV2 (Transcoding Process)
//     if (fork() == 0) {
//         close(pipe_PV1_PV2[1]); // Close unused write end
//         close(pipe_PV2_PV3[0]); // Close unused read end
//         close(pipe_PV3_PV4[0]); close(pipe_PV3_PV4[1]);
//         PV2_Process(pipe_PV1_PV2[0], pipe_PV2_PV3[1]);
//     }

//     // Fork PV3 (Quality Control Process)
//     if (fork() == 0) {
//         close(pipe_PV1_PV2[0]); close(pipe_PV1_PV2[1]);
//         close(pipe_PV2_PV3[1]); // Close unused write end
//         close(pipe_PV3_PV4[0]); // Close unused read end
//         PV3_Process(pipe_PV2_PV3[0], pipe_PV3_PV4[1]);
//     }

//     // Fork PV4 (Distribution Process)
//     if (fork() == 0) {
//         close(pipe_PV1_PV2[0]); close(pipe_PV1_PV2[1]);
//         close(pipe_PV2_PV3[0]); close(pipe_PV2_PV3[1]);
//         close(pipe_PV3_PV4[1]); // Close unused write end
//         PV4_Process(pipe_PV3_PV4[0]);
//     }

//     // Parent Process closes all pipe ends
//     close(pipe_PV1_PV2[0]); close(pipe_PV1_PV2[1]);
//     close(pipe_PV2_PV3[0]); close(pipe_PV2_PV3[1]);
//     close(pipe_PV3_PV4[0]); close(pipe_PV3_PV4[1]);

//     // Wait for all child processes to finish
//     for (int i = 0; i < 4; i++) {
//         wait(NULL);
//     }

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_FILENAME_LEN 256
#define NUM_FILES 3  // Number of files to process

// Function to write a null-terminated string to a pipe
void write_string(int fd, const char *str) {
    if (write(fd, str, strlen(str) + 1) == -1) { // Include null terminator
        perror("write_string: write");
        exit(EXIT_FAILURE);
    }
}

// Function to read a null-terminated string from a pipe
int read_string(int fd, char *buffer, size_t max_len) {
    size_t i = 0;
    char ch;
    ssize_t n;

    while (i < max_len - 1) { // Reserve space for null terminator
        n = read(fd, &ch, 1);
        if (n == 0) {
            // EOF
            if (i == 0)
                return 0;
            break;
        } else if (n < 0) {
            perror("read_string: read");
            return -1;
        }

        if (ch == '\0') {
            break;
        }

        buffer[i++] = ch;
    }
    buffer[i] = '\0';
    return 1;
}

// PV1: Input Process
void PV1_Process(int write_fd) {
    // Filenames to process
    char *fileNames[NUM_FILES] = {"video1.mp4", "video2.mkv", "video3.avi"};

    // Send each filename to PV2
    for (int i = 0; i < NUM_FILES; i++) {
        write_string(write_fd, fileNames[i]);
    }

    // Close write end and exit
    close(write_fd);
    exit(EXIT_SUCCESS);
}

// PV2: Transcoding Process
void PV2_Process(int read_fd, int write_fd) {
    char buffer[MAX_FILENAME_LEN];

    // Read filenames from PV1, process, and send to PV3
    while (read_string(read_fd, buffer, MAX_FILENAME_LEN) > 0) {
        strcat(buffer, "_transcoded");
        write_string(write_fd, buffer);
    }

    // Close remaining pipe ends and exit
    close(read_fd);
    close(write_fd);
    exit(EXIT_SUCCESS);
}

// PV3: Quality Control Process
void PV3_Process(int read_fd, int write_fd) {
    char buffer[MAX_FILENAME_LEN];

    // Read filenames from PV2, process, and send to PV4
    while (read_string(read_fd, buffer, MAX_FILENAME_LEN) > 0) {
        strcat(buffer, "_QC_Passed");
        write_string(write_fd, buffer);
    }

    // Close remaining pipe ends and exit
    close(read_fd);
    close(write_fd);
    exit(EXIT_SUCCESS);
}

// PV4: Distribution Process
void PV4_Process(int read_fd) {
    char buffer[MAX_FILENAME_LEN];

    // Read filenames from PV3 and distribute (print)
    while (read_string(read_fd, buffer, MAX_FILENAME_LEN) > 0) {
        printf("Distributed: %s\n", buffer);
    }

    // Close remaining pipe ends and exit
    close(read_fd);
    exit(EXIT_SUCCESS);
}

int main() {
    int pipe_PV1_PV2[2], pipe_PV2_PV3[2], pipe_PV3_PV4[2];

    // Create the necessary pipes
    if (pipe(pipe_PV1_PV2) == -1 || pipe(pipe_PV2_PV3) == -1 || pipe(pipe_PV3_PV4) == -1) {
        perror("main: pipe");
        exit(EXIT_FAILURE);
    }

    // Fork PV1 (Input Process)
    pid_t pv1_pid = fork();
    if (pv1_pid < 0) {
        perror("main: fork PV1");
        exit(EXIT_FAILURE);
    }

    if (pv1_pid == 0) {
        // PV1 Process
        // Close unused pipe ends
        close(pipe_PV1_PV2[0]); // Close read end
        close(pipe_PV2_PV3[0]); close(pipe_PV2_PV3[1]); // Not used
        close(pipe_PV3_PV4[0]); close(pipe_PV3_PV4[1]); // Not used

        PV1_Process(pipe_PV1_PV2[1]);
    }

    // Fork PV2 (Transcoding Process)
    pid_t pv2_pid = fork();
    if (pv2_pid < 0) {
        perror("main: fork PV2");
        exit(EXIT_FAILURE);
    }

    if (pv2_pid == 0) {
        // PV2 Process
        // Close unused pipe ends
        close(pipe_PV1_PV2[1]); // Close write end
        close(pipe_PV2_PV3[0]); // Close read end
        close(pipe_PV3_PV4[0]); close(pipe_PV3_PV4[1]); // Not used

        PV2_Process(pipe_PV1_PV2[0], pipe_PV2_PV3[1]);
    }

    // Fork PV3 (Quality Control Process)
    pid_t pv3_pid = fork();
    if (pv3_pid < 0) {
        perror("main: fork PV3");
        exit(EXIT_FAILURE);
    }

    if (pv3_pid == 0) {
        // PV3 Process
        // Close unused pipe ends
        close(pipe_PV1_PV2[0]); close(pipe_PV1_PV2[1]); // Not used
        close(pipe_PV2_PV3[1]); // Close write end
        close(pipe_PV3_PV4[0]); // Close read end

        PV3_Process(pipe_PV2_PV3[0], pipe_PV3_PV4[1]);
    }

    // Fork PV4 (Distribution Process)
    pid_t pv4_pid = fork();
    if (pv4_pid < 0) {
        perror("main: fork PV4");
        exit(EXIT_FAILURE);
    }

    if (pv4_pid == 0) {
        // PV4 Process
        // Close unused pipe ends
        close(pipe_PV1_PV2[0]); close(pipe_PV1_PV2[1]); // Not used
        close(pipe_PV2_PV3[0]); close(pipe_PV2_PV3[1]); // Not used
        close(pipe_PV3_PV4[1]); // Close write end

        PV4_Process(pipe_PV3_PV4[0]);
    }

    // Parent Process
    // Close all pipe ends as parent doesn't use them
    close(pipe_PV1_PV2[0]); close(pipe_PV1_PV2[1]);
    close(pipe_PV2_PV3[0]); close(pipe_PV2_PV3[1]);
    close(pipe_PV3_PV4[0]); close(pipe_PV3_PV4[1]);

    // Wait for all child processes to finish
    for (int i = 0; i < 4; i++) {
        wait(NULL);
    }

    return 0;
}