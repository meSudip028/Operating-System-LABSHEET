#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, req[20], total = 0, current, split;

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &req[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    // Sort requests
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (req[i] > req[j]) {
                int t = req[i];
                req[i] = req[j];
                req[j] = t;
            }

    // Find first request >= head
    split = 0;
    while (split < n && req[split] < head)
        split++;

    current = head;
    printf("\nSeek Sequence: %d", current);

    // Service requests on the right
    for (int i = split; i < n; i++) {
        total += abs(req[i] - current);
        current = req[i];
        printf(" -> %d", current);
    }

    // Jump to smallest request
    if (split > 0) {
        total += abs(req[0] - current);
        current = req[0];
        printf(" -> %d", current);

        // Service remaining requests
        for (int i = 1; i < split; i++) {
            total += abs(req[i] - current);
            current = req[i];
            printf(" -> %d", current);
        }
    }

    printf("\n\nTotal Head Movement = %d\n", total);

    return 0;
}