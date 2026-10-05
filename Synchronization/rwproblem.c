#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
 
sem_t *wrt;                // named semaphore: exclusive access for writers
pthread_mutex_t mutex;     // protects read_count
int read_count = 0;
int shared_data = 0;
 
void* reader(void* arg) {
    int id = *((int*)arg);
 
    pthread_mutex_lock(&mutex);
    read_count++;
    if (read_count == 1)
        sem_wait(wrt);       // first reader locks out writers
    pthread_mutex_unlock(&mutex);
 
    printf("Reader %d: read shared_data = %d\n", id, shared_data);
    sleep(1);
 
    pthread_mutex_lock(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(wrt);       // last reader lets writers in again
    pthread_mutex_unlock(&mutex);
    return NULL;
}
 
void* writer(void* arg) {
    int id = *((int*)arg);
 
    sem_wait(wrt);           // exclusive access
    shared_data += 10;
    printf("Writer %d: wrote shared_data = %d\n", id, shared_data);
    sleep(1);
    sem_post(wrt);
    return NULL;
}
 
int main() {
    // Named semaphore (sem_open) instead of sem_init(): portable to both
    // Linux and macOS, since macOS does not implement unnamed semaphores.
    sem_unlink("/os_lab12_wrt");
    wrt = sem_open("/os_lab12_wrt", O_CREAT | O_EXCL, 0644, 1);
    pthread_mutex_init(&mutex, NULL);
 
    pthread_t r[3], w[2];
    int rid[3] = {1, 2, 3};
    int wid[2] = {1, 2};
 
    pthread_create(&w[0], NULL, writer, &wid[0]);
    pthread_create(&r[0], NULL, reader, &rid[0]);
    pthread_create(&r[1], NULL, reader, &rid[1]);
    pthread_create(&w[1], NULL, writer, &wid[1]);
    pthread_create(&r[2], NULL, reader, &rid[2]);
 
    pthread_join(w[0], NULL);
    pthread_join(r[0], NULL);
    pthread_join(r[1], NULL);
    pthread_join(w[1], NULL);
    pthread_join(r[2], NULL);
 
    sem_close(wrt);
    sem_unlink("/os_lab12_wrt");
    pthread_mutex_destroy(&mutex);
    return 0;
}
