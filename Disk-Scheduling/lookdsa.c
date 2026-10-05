#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, req[20], total = 0, current;
    char dir;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (u/d): ");
    scanf(" %c", &dir);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int t = req[i];
                req[i] = req[j];
                req[j] = t;
            }

    current = head;
    printf("\nSeek Sequence: %d", current);

    if (dir == 'u') {
        // Move upward
        for (int i = 0; i < n; i++)
            if (req[i] >= head) {
                total += abs(req[i] - current);
                current = req[i];
                printf(" -> %d", current);
            }

        // Reverse without going to disk boundary
        for (int i = n - 1; i >= 0; i--)
            if (req[i] < head) {
                total += abs(req[i] - current);
                current = req[i];
                printf(" -> %d", current);
            }
    } else {
        // Move downward
        for (int i = n - 1; i >= 0; i--)
            if (req[i] <= head) {
                total += abs(req[i] - current);
                current = req[i];
                printf(" -> %d", current);
            }

        // Reverse without going to disk boundary
        for (int i = 0; i < n; i++)
            if (req[i] > head) {
                total += abs(req[i] - current);
                current = req[i];
                printf(" -> %d", current);
            }
    }

    printf("\n\nTotal Head Movement = %d\n", total);

    return 0;
}