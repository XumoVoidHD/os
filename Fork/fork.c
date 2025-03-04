#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();  // Create child process

    if (pid > 0) {
        printf("Parent process, PID: %d, Child PID: %d\n", getpid(), pid);
    } else if (pid == 0) {
        printf("Child process, PID: %d, Parent PID: %d\n", getpid(), getppid());
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}
