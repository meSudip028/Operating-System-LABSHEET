#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, size, req[20], total = 0, current;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size (max cylinder number): ");
    scanf("%d", &size);

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

    // Move upward
    for (int i = 0; i < n; i++)
        if (req[i] >= head) {
            total += abs(req[i] - current);
            current = req[i];
            printf(" -> %d", current);
        }

    // Go to end
    if (current != size - 1) {
        total += size - 1 - current;
        current = size - 1;
        printf(" -> %d", current);
    }

    // Circular jump to beginning
    total += size - 1;
    current = 0;
    printf(" -> %d", current);

    // Continue upward
    for (int i = 0; i < n; i++)
        if (req[i] < head) {
            total += abs(req[i] - current);
            current = req[i];
            printf(" -> %d", current);
        }

    printf("\n\nTotal Head Movement = %d\n", total);

    return 0;
}