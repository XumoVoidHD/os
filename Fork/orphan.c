#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        printf("Parent process exiting, PID: %d\n", getpid());
        sleep(2);  // Simulating work
        printf("Parent exits now.\n");
    } else if (pid == 0) {
        sleep(5);  // Child outlives the parent
        printf("Orphan process, PID: %d, new parent PID: %d\n", getpid(), getppid());
    }

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {  // Parent process
        printf("Parent process running, waiting for child...\n");
        wait(NULL);  // Ensures child exits before parent
        printf("Parent exits after child.\n");
    } else if (pid == 0) {  // Child process
        printf("Child process started, PID: %d, Parent PID: %d\n", getpid(), getppid());
        sleep(5);  // Simulating work
        printf("Child process exiting, PID: %d, New Parent PID: %d\n", getpid(), getppid());
        exit(0);
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}
