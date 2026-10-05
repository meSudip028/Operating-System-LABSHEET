#include <stdio.h>
#include <pthread.h>
 
void* printMessage(void* arg) {
    int id = *((int*)arg);
    printf("Hello from thread %d (Thread ID = %lu)\n", id, (unsigned long)pthread_self());
    return NULL;
}
 
int main() {
    int n = 3;
    pthread_t threads[n];
    int ids[n];
 
    for (int i = 0; i < n; i++) {
        ids[i] = i + 1;
        pthread_create(&threads[i], NULL, printMessage, &ids[i]);
    }
 
    for (int i = 0; i < n; i++)
        pthread_join(threads[i], NULL); // wait for each thread to finish
 
    printf("All threads finished execution.\n");
    return 0;
}