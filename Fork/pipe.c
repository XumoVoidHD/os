#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd[2]; // fd[0] for reading, fd[1] for writing
    pid_t pid;
    char write_msg[] = "Hello from parent";
    char read_msg[100];

    pipe(fd); // Create a pipe
    pid = fork(); // Create a child process

    if (pid == 0) {
        // Child Process
        close(fd[1]); // Close write end
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]);
    } else {
        // Parent Process
        close(fd[0]); // Close read end
        write(fd[1], write_msg, strlen(write_msg)+1);
        close(fd[1]);
    }

    return 0;
}
