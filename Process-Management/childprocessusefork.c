#include <stdio.h>
#include <unistd.h>
 
int main() {
    setvbuf(stdout, NULL, _IOLBF, 0); // line-buffer stdout for real-time output
    pid_t pid;
 
    printf("Before fork(): PID = %d\n", getpid());
 
    pid = fork();
 
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    else if (pid == 0) {
        // This block runs in the child process
        printf("Child process : PID = %d, Parent PID = %d\n", getpid(), getppid());
    }
    else {
        // This block runs in the parent process
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    }
 
    return 0;
}