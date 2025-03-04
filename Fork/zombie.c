#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {  // Parent process
        printf("Parent process, PID: %d\n", getpid());
        sleep(10);  // Keeping parent alive, but not calling wait()
    } else if (pid == 0) {  // Child process
        printf("Child process exiting, PID: %d\n", getpid());
        exit(0);  // Child exits
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
        printf("Parent waiting for child to terminate...\n");
        wait(NULL);  // Wait for child to exit, preventing zombie
        printf("Child terminated. No zombie left.\n");
    } else if (pid == 0) {  // Child process
        printf("Child process running...\n");
        sleep(2);  // Simulating work
        printf("Child process exiting...\n");
        exit(0);
    } else {
        printf("Fork failed!\n");
    }

    return 0;
}
