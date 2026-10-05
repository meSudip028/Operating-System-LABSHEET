#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
 
#define BUFFER_SIZE 5
#define ITEMS 8
 
int buffer[BUFFER_SIZE];
int in = 0, out = 0;
 
sem_t *empty, *full;                // named semaphores (portable: Linux AND macOS)
pthread_mutex_t mutex;              // protects the buffer
 
void* producer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(empty);                 // wait for an empty slot
        pthread_mutex_lock(&mutex);
 
        buffer[in] = i;
        printf("Producer produced: %d\n", i);
        in = (in + 1) % BUFFER_SIZE;
 
        pthread_mutex_unlock(&mutex);
        sem_post(full);                  // signal that an item is ready
        usleep(100000);
    }
    return NULL;
}
 
void* consumer(void* arg) {
    for (int i = 1; i <= ITEMS; i++) {
        sem_wait(full);                  // wait for an available item
        pthread_mutex_lock(&mutex);
 
        int item = buffer[out];
        printf("Consumer consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;
 
        pthread_mutex_unlock(&mutex);
        sem_post(empty);                 // signal that a slot is free
        usleep(150000);
    }
    return NULL;
}
 
int main() {
    // Named semaphores (sem_open) instead of sem_init(): macOS never
    // implemented unnamed POSIX semaphores, but sem_open works identically
    // on Linux and macOS. Unlink first in case a previous run crashed and
    // left the name behind, then create fresh.
    sem_unlink("/os_lab11_empty");
    sem_unlink("/os_lab11_full");
    empty = sem_open("/os_lab11_empty", O_CREAT | O_EXCL, 0644, BUFFER_SIZE);
    full  = sem_open("/os_lab11_full",  O_CREAT | O_EXCL, 0644, 0);
    pthread_mutex_init(&mutex, NULL);
 
    pthread_t prod, cons;
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
 
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
 
    sem_close(empty);
    sem_close(full);
    sem_unlink("/os_lab11_empty");
    sem_unlink("/os_lab11_full");
    pthread_mutex_destroy(&mutex);
    return 0;
}
