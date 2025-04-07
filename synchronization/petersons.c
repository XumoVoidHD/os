#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

bool flag[2] = {false, false};  // Flags for each process
int turn;                       // Whose turn is it?

void* process(void* arg) {
    int id = (int)arg;        // Process ID (0 or 1)
    int other = 1 - id;

    // Entry section
    flag[id] = true;
    turn = other;
    while (flag[other] && turn == other);  // Wait if the other process wants to enter

    // Critical section
    printf("Process %d is in the critical section\n", id);
    sleep(1);  // Simulate some work

    // Exit section
    flag[id] = false;

    // Remainder section
    printf("Process %d is out of the critical section\n", id);
    return NULL;
}

int main() {
    pthread_t t0, t1;
    int id0 = 0, id1 = 1;

    pthread_create(&t0, NULL, process, &id0);
    pthread_create(&t1, NULL, process, &id1);

    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}