#include <stdio.h>

int main() {
    int n, f, pages[20], frame[10], last[10], faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++)
        frame[i] = last[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0, pos = -1;

        // Check if page is already present
        for (int j = 0; j < f; j++)
            if (frame[j] == pages[i])
                found = 1;

        // Page fault
        if (!found) {
            // Find empty frame
            for (int j = 0; j < f; j++)
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }

            // If no empty frame, find LRU page
            if (pos == -1) {
                pos = 0;
                for (int j = 1; j < f; j++)
                    if (last[j] < last[pos])
                        pos = j;
            }

            frame[pos] = pages[i];
            faults++;
        }

        // Update last used time
        for (int j = 0; j < f; j++)
            if (frame[j] == pages[i])
                last[j] = i;

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < f; j++)
            frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);

    return 0;
}