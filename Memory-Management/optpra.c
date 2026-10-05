#include <stdio.h>

int main() {
    int n, f, pages[20], frame[10], faults = 0;

    printf("Enter number of pages: ");
    scanf("%d", &n);

    printf("Enter reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (int i = 0; i < f; i++)
        frame[i] = -1;

    for (int i = 0; i < n; i++) {
        int found = 0, pos = -1;

        // Check if page is present
        for (int j = 0; j < f; j++)
            if (frame[j] == pages[i])
                found = 1;

        if (!found) {
            // Find empty frame
            for (int j = 0; j < f; j++)
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }

            // Find page used farthest in future
            if (pos == -1) {
                int farthest = -1;

                for (int j = 0; j < f; j++) {
                    int k;
                    for (k = i + 1; k < n; k++)
                        if (frame[j] == pages[k])
                            break;

                    if (k == n) {
                        pos = j;
                        break;
                    }

                    if (k > farthest) {
                        farthest = k;
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            faults++;
        }

        printf("Page %d -> ", pages[i]);
        for (int j = 0; j < f; j++)
            frame[j] == -1 ? printf("- ") : printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);

    return 0;
}