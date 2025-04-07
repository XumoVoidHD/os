#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <sched.h> // For sched_yield()

// Shared variables
volatile bool flag[2] = {false, false};  // Flags for each thread
volatile int turn;                       // Indicates whose turn it is

// Function for both threads
void* peterson_process(void* arg) {
    int id = *(int*)arg;        // 0 or 1
    int other = 1 - id;

    // Entry section
    flag[id] = true;
    turn = other;
    while (flag[other] && turn == other) {
        sched_yield();  // Yield CPU to avoid busy waiting
    }

    // Critical section
    printf("Thread %d is in the critical section\n", id);
    sleep(1);  // Simulate critical section work

    // Exit section
    flag[id] = false;

    // Remainder section
    printf("Thread %d is out of the critical section\n", id);
    return NULL;
}

int main() {
    pthread_t t0, t1;
    int id0 = 0, id1 = 1;

    // Create two threads
    pthread_create(&t0, NULL, peterson_process, &id0);
    pthread_create(&t1, NULL, peterson_process, &id1);

    // Wait for both threads to finish
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}
