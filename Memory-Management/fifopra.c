#include <stdio.h>

int main() {
    int n, f, pages[20], frame[10], faults = 0, pos = 0;

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
        int found = 0;

        for (int j = 0; j < f; j++)
            if (frame[j] == pages[i])
                found = 1;

        if (!found) {
            frame[pos] = pages[i];
            pos = (pos + 1) % f;
            faults++;
        }

        printf("%d -> ", pages[i]);
        for (int j = 0; j < f; j++)
            printf("%d ", frame[j]);
        printf("\n");
    }

    printf("Total Page Faults = %d\n", faults);

    return 0;
}