#include <stdio.h>
#include <unistd.h>
 
int main() {
    printf("Process ID (PID)  : %d\n", getpid());
    printf("Parent PID (PPID) : %d\n", getppid());
    return 0;
}