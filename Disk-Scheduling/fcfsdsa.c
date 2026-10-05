#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);
 
    int req[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
 
    printf("Enter initial head position: ");
    scanf("%d", &head);
 
    int total_seek = 0, current = head;
 
    printf("\nSeek Sequence: %d", current);
    for (int i = 0; i < n; i++) {           // service requests in the order given
        total_seek += abs(req[i] - current);
        current = req[i];
        printf(" -> %d", current);
    }
 
    printf("\n\nTotal Head Movement = %d\n", total_seek);
    return 0;
}