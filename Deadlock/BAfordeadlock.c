#include <stdio.h>
 
#define P 5   // number of processes
#define R 3   // number of resource types
 
int main() {
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };
 
    int max[P][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };
 
    int avail[R] = {3, 3, 2};
 
    int need[P][R];
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = max[i][j] - alloc[i][j];
 
    int finish[P] = {0};
    int safe_seq[P];
    int work[R];
    for (int j = 0; j < R; j++) work[j] = avail[j];
 
    int count = 0;
    while (count < P) {
        int found = 0;
 
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                int can_allocate = 1;
                for (int j = 0; j < R; j++)
                    if (need[i][j] > work[j]) { can_allocate = 0; break; }
 
                if (can_allocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += alloc[i][j];
                    safe_seq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
 
        if (!found) {
            printf("System is NOT in a safe state.\n");
            return 0;
        }
    }
 
    printf("System is in a SAFE state.\n");
    printf("Safe sequence: ");
    for (int i = 0; i < P; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");
    return 0;
}
