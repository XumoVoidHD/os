#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define THREAD_COUNT 10
#define MAX_CONCURRENT 3  // Maximum number of threads allowed in the critical section

sem_t semaphore;

void* thread_function(void* arg) {
    int thread_id = *(int*)arg;

    // Wait (P operation) — decreases count if > 0, otherwise blocks
    sem_wait(&semaphore);

    // Critical Section
    printf("Thread %d: Entered critical section\n", thread_id);
    sleep(1);  // Simulate work
    printf("Thread %d: Leaving critical section\n", thread_id);

    // Signal (V operation) — increases count
    sem_post(&semaphore);

    return NULL;
}

int main() {
    pthread_t threads[THREAD_COUNT];
    int thread_ids[THREAD_COUNT];

    // Initialize counting semaphore with initial value MAX_CONCURRENT
    sem_init(&semaphore, 0, MAX_CONCURRENT);

    for (int i = 0; i < THREAD_COUNT; i++) {
        thread_ids[i] = i + 1;
        pthread_create(&threads[i], NULL, thread_function, &thread_ids[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy semaphore
    sem_destroy(&semaphore);

    return 0;
}
