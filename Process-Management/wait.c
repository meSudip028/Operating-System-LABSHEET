#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
 
int main() {
    setvbuf(stdout, NULL, _IOLBF, 0);
    pid_t pid = fork();
 
    if (pid == 0) {
        // Child process
        printf("Child  : started (PID = %d)\n", getpid());
        sleep(2); // simulate some work
        printf("Child  : work finished\n");
        exit(0);
    }
    else {
        // Parent process
        printf("Parent : waiting for child (PID = %d) using wait()\n", pid);
        wait(NULL); // blocks parent until child terminates
        printf("Parent : child finished, resuming execution\n");
    }
 
    return 0;
}