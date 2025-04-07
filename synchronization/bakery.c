#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>

#define N 5  // Number of threads

int choosing[N];     // Indicates if thread i is choosing a number
int number[N];       // Ticket number for thread i

void lock(int id) {
    choosing[id] = 1;

    // Find max number among all threads
    int max = 0;
    for (int i = 0; i < N; i++) {
        if (number[i] > max)
            max = number[i];
    }
    number[id] = max + 1;
    choosing[id] = 0;

    for (int j = 0; j < N; j++) {
        while (choosing[j]);  // Wait if thread j is choosing a number

        // Wait if thread j has a ticket and is ahead in the queue
        while (number[j] != 0 &&
              (number[j] < number[id] || 
              (number[j] == number[id] && j < id)));
    }
}

void unlock(int id) {
    number[id] = 0;
}

void* thread_func(void* arg) {
    int id = *(int*)arg;

    lock(id);

    // Critical Section
    printf("Thread %d is in the critical section\n", id);
    sleep(1);  // Simulate some work
    printf("Thread %d is leaving the critical section\n", id);

    unlock(id);

    return NULL;
}

int main() {
    pthread_t threads[N];
    int ids[N];

    for (int i = 0; i < N; i++) {
        choosing[i] = 0;
        number[i] = 0;
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_func, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
