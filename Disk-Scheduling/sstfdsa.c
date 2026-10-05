#include <stdio.h>
#include <stdlib.h>
 
int main() {
    int n, head;
    printf("Enter number of requests: ");
    scanf("%d", &n);
 
    int req[n], visited[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) { scanf("%d", &req[i]); visited[i] = 0; }
 
    printf("Enter initial head position: ");
    scanf("%d", &head);
 
    int total_seek = 0, current = head;
    printf("\nSeek Sequence: %d", current);
 
    for (int count = 0; count < n; count++) {
        int min_dist = 999999, idx = -1;
 
        for (int i = 0; i < n; i++)          // pick nearest unvisited request
            if (!visited[i] && abs(req[i] - current) < min_dist) {
                min_dist = abs(req[i] - current);
                idx = i;
            }
 
        visited[idx] = 1;
        total_seek += min_dist;
        current = req[idx];
        printf(" -> %d", current);
    }
 
    printf("\n\nTotal Head Movement = %d\n", total_seek);
    return 0;
}