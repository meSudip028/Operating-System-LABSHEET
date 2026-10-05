#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
 
#define N 5
 
sem_t *forks[N];
pthread_mutex_t mutex;     // makes "pick up both forks" atomic -> prevents deadlock
 
void* philosopher(void* arg) {
    int id = *((int*)arg);
    int left = id;
    int right = (id + 1) % N;
 
    for (int i = 0; i < 2; i++) {         // each philosopher eats twice
        printf("Philosopher %d is thinking...\n", id);
        sleep(1);
 
        pthread_mutex_lock(&mutex);       // pick up both forks together
        sem_wait(forks[left]);
        sem_wait(forks[right]);
        pthread_mutex_unlock(&mutex);
 
        printf("Philosopher %d is eating...\n", id);
        sleep(1);
 
        sem_post(forks[left]);
        sem_post(forks[right]);
        printf("Philosopher %d put down forks.\n", id);
    }
    return NULL;
}
 
int main() {
    // Named semaphores (sem_open) instead of sem_init(): portable to both
    // Linux and macOS, since macOS does not implement unnamed semaphores.
    char name[20];
    for (int i = 0; i < N; i++) {
        sprintf(name, "/os_lab13_fork%d", i);
        sem_unlink(name);
        forks[i] = sem_open(name, O_CREAT | O_EXCL, 0644, 1);
    }
    pthread_mutex_init(&mutex, NULL);
 
    pthread_t phil[N];
    int ids[N];
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&phil[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < N; i++)
        pthread_join(phil[i], NULL);
 
    for (int i = 0; i < N; i++) {
        sem_close(forks[i]);
        sprintf(name, "/os_lab13_fork%d", i);
        sem_unlink(name);
    }
    pthread_mutex_destroy(&mutex);
    return 0;
}
