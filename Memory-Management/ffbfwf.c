#include <stdio.h>

void allocate(int block[], int m, int process[], int n, int type) {
    int b[m], alloc[n];

    for (int i = 0; i < m; i++)
        b[i] = block[i];

    for (int i = 0; i < n; i++)
        alloc[i] = -1;

    for (int i = 0; i < n; i++) {
        int index = -1;

        for (int j = 0; j < m; j++) {
            if (b[j] >= process[i]) {
                if (type == 1) {              // First Fit
                    index = j;
                    break;
                }

                if (type == 2 &&              // Best Fit
                    (index == -1 || b[j] < b[index]))
                    index = j;

                if (type == 3 &&              // Worst Fit
                    (index == -1 || b[j] > b[index]))
                    index = j;
            }
        }

        if (index != -1) {
            alloc[i] = index;
            b[index] -= process[i];
        }
    }

    if (type == 1) printf("\n--- First Fit ---\n");
    if (type == 2) printf("\n--- Best Fit ---\n");
    if (type == 3) printf("\n--- Worst Fit ---\n");

    printf("Process\tSize\tBlock\n");

    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t", i + 1, process[i]);

        if (alloc[i] == -1)
            printf("Not Allocated\n");
        else
            printf("B%d\n", alloc[i] + 1);
    }
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    int block[m];

    printf("Enter block sizes: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &block[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    int process[n];

    printf("Enter process sizes: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &process[i]);

    allocate(block, m, process, n, 1);
    allocate(block, m, process, n, 2);
    allocate(block, m, process, n, 3);

    return 0;
}