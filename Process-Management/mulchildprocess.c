#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main() {
    setvbuf(stdout, NULL, _IOLBF, 0);
    int n = 3; // number of child processes to create
 
    for (int i = 0; i < n; i++) {
        pid_t pid = fork();
 
        if (pid == 0) {
            // Child prints its own PID and exits immediately
            printf("Child %d : PID = %d, Parent PID = %d\n", i + 1, getpid(), getppid());
            exit(0); // stop child here so it does not repeat the loop
        }
    }
 
    // Parent waits for all children to finish
    for (int i = 0; i < n; i++)
        wait(NULL);
 
    printf("Parent : PID = %d created %d child processes\n", getpid(), n);
    return 0;
}