#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
 
int main() {
    int fd[2];              // fd[0] = read end, fd[1] = write end
    char buffer[100];
    char message[] = "Hello from parent process!";
 
    if (pipe(fd) == -1) {
        printf("Pipe creation failed\n");
        return 1;
    }
 
    pid_t pid = fork();
 
    if (pid == 0) {
        // Child process: reads from the pipe
        close(fd[1]);                        // close unused write end
        read(fd[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(fd[0]);
    }
    else {
        // Parent process: writes to the pipe
        close(fd[0]);                        // close unused read end
        write(fd[1], message, strlen(message) + 1);
        close(fd[1]);
        wait(NULL);
    }
 
    return 0;
}