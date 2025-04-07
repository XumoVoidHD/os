#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

// Semaphores
sem_t empty;
sem_t full;

// Mutex
pthread_mutex_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);     // Decrease empty count
        pthread_mutex_lock(&mutex);  // Lock buffer access

        buffer[in] = item;
        printf("Produced: %d at index %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock buffer access
        sem_post(&full);              // Increase full count

        sleep(1); // Simulate time
    }
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);             // Decrease full count
        pthread_mutex_lock(&mutex);  // Lock buffer access

        item = buffer[out];
        printf("Consumed: %d from index %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex); // Unlock buffer access
        sem_post(&empty);             // Increase empty count

        sleep(2); // Simulate time
    }
}

int main() {
    pthread_t prod, cons;

    sem_init(&empty, 0, BUFFER_SIZE);  // Initially all empty
    sem_init(&full, 0, 0);             // Initially no full slots
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}



#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5

int buff[SIZE];
int in = 0, out = 0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int item = 0;
    while (1) {
        item++;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buff[in] = item;
        printf("\nProduct made- %d", item);
        in = (in + 1) % SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}

void *consumer(void *arg) {
    while (1) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buff[out];
        printf("\nProduct consumed- %d", item);
        out = (out + 1) % SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}

int main() {
    pthread_t producer, consumer;
    sem_init(&empty, 0, SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&producer, NULL, producer, NULL);
    pthread_create(&consumer, NULL, consumer, NULL);
    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}
