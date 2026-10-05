#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_PROC   20   /* max processes / memory blocks       */
#define MAX_PAGES  50   /* max length of page reference string */
#define MAX_FRAMES 10   /* max memory frames                   */
#define MAX_REQ    50   /* max disk requests                   */

/* ---------------------------------------------------------
   Reads one integer safely. If the input is missing or not
   a valid number, the program exits with a message instead
   of looping forever (this was the main bug in the original).
   --------------------------------------------------------- */
int readInt(void) {
    int value;
    if (scanf("%d", &value) != 1) {
        printf("\nInvalid input. Exiting program.\n");
        exit(1);
    }
    return value;
}

/* =========================================================
   CPU SCHEDULING
   ========================================================= */

void fcfs() {
    int n, i;
    int bt[MAX_PROC], wt[MAX_PROC], tat[MAX_PROC];
    float avgWT = 0, avgTAT = 0;

    printf("\nEnter number of processes: ");
    n = readInt();
    if (n <= 0 || n > MAX_PROC) {
        printf("Invalid number of processes (1-%d allowed).\n", MAX_PROC);
        return;
    }

    for (i = 0; i < n; i++) {
        printf("Burst time of P%d: ", i + 1);
        bt[i] = readInt();
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", i + 1, bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
}

void sjf() {
    int n, i, j;
    int bt[MAX_PROC], p[MAX_PROC], wt[MAX_PROC], tat[MAX_PROC];
    float avgWT = 0, avgTAT = 0;

    printf("\nEnter number of processes: ");
    n = readInt();
    if (n <= 0 || n > MAX_PROC) {
        printf("Invalid number of processes (1-%d allowed).\n", MAX_PROC);
        return;
    }

    for (i = 0; i < n; i++) {
        p[i] = i + 1;
        printf("Burst time of P%d: ", i + 1);
        bt[i] = readInt();
    }

    /* Sort processes by burst time (shortest job first) */
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (bt[i] > bt[j]) {
                int temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    wt[0] = 0;
    for (i = 1; i < n; i++)
        wt[i] = wt[i - 1] + bt[i - 1];

    for (i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
        avgWT += wt[i];
        avgTAT += tat[i];
    }

    printf("\nProcess\tBT\tWT\tTAT\n");
    for (i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\n", p[i], bt[i], wt[i], tat[i]);

    printf("\nAverage Waiting Time = %.2f", avgWT / n);
    printf("\nAverage Turnaround Time = %.2f\n", avgTAT / n);
}

void cpuScheduling() {
    int choice;

    do {
        printf("\n===== CPU SCHEDULING =====\n");
        printf("1. FCFS\n");
        printf("2. SJF\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1: fcfs(); break;
            case 2: sjf();  break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}

/* =========================================================
   MEMORY ALLOCATION
   ========================================================= */

void memoryAllocation() {
    int nb, np, i, j, choice;
    int block[MAX_PROC], process[MAX_PROC], allocation[MAX_PROC];

    printf("\nEnter number of memory blocks: ");
    nb = readInt();
    if (nb <= 0 || nb > MAX_PROC) {
        printf("Invalid number of blocks (1-%d allowed).\n", MAX_PROC);
        return;
    }

    for (i = 0; i < nb; i++) {
        printf("Size of block %d: ", i + 1);
        block[i] = readInt();
    }

    printf("Enter number of processes: ");
    np = readInt();
    if (np <= 0 || np > MAX_PROC) {
        printf("Invalid number of processes (1-%d allowed).\n", MAX_PROC);
        return;
    }

    for (i = 0; i < np; i++) {
        printf("Memory required by P%d: ", i + 1);
        process[i] = readInt();
        allocation[i] = -1;
    }

    printf("\n1. First Fit\n");
    printf("2. Best Fit\n");
    printf("3. Worst Fit\n");
    printf("Enter choice: ");
    choice = readInt();

    if (choice < 1 || choice > 3) {
        printf("Invalid choice.\n");
        return;
    }

    for (i = 0; i < np; i++) {
        int selected = -1;

        if (choice == 1) {
            /* First Fit: first block big enough */
            for (j = 0; j < nb; j++) {
                if (block[j] >= process[i]) {
                    selected = j;
                    break;
                }
            }
        }
        else if (choice == 2) {
            /* Best Fit: smallest block that still fits */
            int best = INT_MAX;
            for (j = 0; j < nb; j++) {
                if (block[j] >= process[i] && block[j] - process[i] < best) {
                    best = block[j] - process[i];
                    selected = j;
                }
            }
        }
        else {
            /* Worst Fit: largest block available */
            int worst = -1;
            for (j = 0; j < nb; j++) {
                if (block[j] >= process[i] && block[j] - process[i] > worst) {
                    worst = block[j] - process[i];
                    selected = j;
                }
            }
        }

        if (selected != -1) {
            allocation[i] = selected;
            block[selected] -= process[i];
        }
    }

    printf("\nProcess\tRequired\tBlock\n");
    for (i = 0; i < np; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\t\tB%d\n", i + 1, process[i], allocation[i] + 1);
        else
            printf("P%d\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }
}

/* =========================================================
   PAGE REPLACEMENT
   ========================================================= */

void fifoPageReplacement() {
    int pages[MAX_PAGES], frames[MAX_FRAMES];
    int n, f, i, j;
    int pointer = 0, faults = 0, hit;

    printf("\nEnter number of pages: ");
    n = readInt();
    if (n <= 0 || n > MAX_PAGES) {
        printf("Invalid number of pages (1-%d allowed).\n", MAX_PAGES);
        return;
    }

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        pages[i] = readInt();

    printf("Enter number of frames: ");
    f = readInt();
    if (f <= 0 || f > MAX_FRAMES) {
        printf("Invalid number of frames (1-%d allowed).\n", MAX_FRAMES);
        return;
    }

    for (i = 0; i < f; i++)
        frames[i] = -1;

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            frames[pointer] = pages[i];
            pointer = (pointer + 1) % f;
            faults++;
        }

        printf("Page %d: ", pages[i]);
        for (j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

void lruPageReplacement() {
    int pages[MAX_PAGES], frames[MAX_FRAMES], recent[MAX_FRAMES];
    int n, f, i, j;
    int faults = 0, hit, pos;

    printf("\nEnter number of pages: ");
    n = readInt();
    if (n <= 0 || n > MAX_PAGES) {
        printf("Invalid number of pages (1-%d allowed).\n", MAX_PAGES);
        return;
    }

    printf("Enter page reference string:\n");
    for (i = 0; i < n; i++)
        pages[i] = readInt();

    printf("Enter number of frames: ");
    f = readInt();
    if (f <= 0 || f > MAX_FRAMES) {
        printf("Invalid number of frames (1-%d allowed).\n", MAX_FRAMES);
        return;
    }

    for (i = 0; i < f; i++) {
        frames[i] = -1;
        recent[i] = 0;
    }

    for (i = 0; i < n; i++) {
        hit = 0;
        for (j = 0; j < f; j++) {
            if (frames[j] == pages[i]) {
                hit = 1;
                recent[j] = i;
                break;
            }
        }

        if (!hit) {
            faults++;

            /* Look for an empty frame first */
            pos = -1;
            for (j = 0; j < f; j++) {
                if (frames[j] == -1) {
                    pos = j;
                    break;
                }
            }

            /* Otherwise replace the least recently used page */
            if (pos == -1) {
                pos = 0;
                for (j = 1; j < f; j++) {
                    if (recent[j] < recent[pos])
                        pos = j;
                }
            }

            frames[pos] = pages[i];
            recent[pos] = i;
        }

        printf("Page %d: ", pages[i]);
        for (j = 0; j < f; j++) {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("\nTotal Page Faults = %d\n", faults);
}

void pageReplacement() {
    int choice;

    do {
        printf("\n===== PAGE REPLACEMENT =====\n");
        printf("1. FIFO\n");
        printf("2. LRU\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1: fifoPageReplacement(); break;
            case 2: lruPageReplacement();  break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}

/* =========================================================
   DISK SCHEDULING
   ========================================================= */

void diskFCFS() {
    int n, i, head;
    int request[MAX_REQ];
    int total = 0;

    printf("\nEnter number of disk requests: ");
    n = readInt();
    if (n <= 0 || n > MAX_REQ) {
        printf("Invalid number of requests (1-%d allowed).\n", MAX_REQ);
        return;
    }

    printf("Enter request queue:\n");
    for (i = 0; i < n; i++)
        request[i] = readInt();

    printf("Enter initial head position: ");
    head = readInt();

    printf("\nSeek Sequence: %d", head);
    for (i = 0; i < n; i++) {
        total += abs(head - request[i]);
        head = request[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void diskSSTF() {
    int n, i, j, head;
    int request[MAX_REQ], visited[MAX_REQ] = {0};
    int total = 0;

    printf("\nEnter number of disk requests: ");
    n = readInt();
    if (n <= 0 || n > MAX_REQ) {
        printf("Invalid number of requests (1-%d allowed).\n", MAX_REQ);
        return;
    }

    printf("Enter request queue:\n");
    for (i = 0; i < n; i++)
        request[i] = readInt();

    printf("Enter initial head position: ");
    head = readInt();

    printf("\nSeek Sequence: %d", head);
    for (i = 0; i < n; i++) {
        int minDistance = INT_MAX;
        int index = -1;

        for (j = 0; j < n; j++) {
            if (!visited[j]) {
                int distance = abs(head - request[j]);
                if (distance < minDistance) {
                    minDistance = distance;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += abs(head - request[index]);
        head = request[index];
        printf(" -> %d", head);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void diskScheduling() {
    int choice;

    do {
        printf("\n===== DISK SCHEDULING =====\n");
        printf("1. FCFS\n");
        printf("2. SSTF\n");
        printf("3. Back\n");
        printf("Enter choice: ");
        choice = readInt();

        switch (choice) {
            case 1: diskFCFS(); break;
            case 2: diskSSTF(); break;
            case 3: break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 3);
}

/* =========================================================
   MAIN MENU
   ========================================================= */

int main() {
    int choice;

    do {
        printf("\n\n====================================\n");
        printf("   OPERATING SYSTEM SIMULATOR\n");
        printf("====================================\n");
        printf("1. CPU Scheduling\n");
        printf("2. Memory Allocation\n");
        printf("3. Page Replacement\n");
        printf("4. Disk Scheduling\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        choice = readInt();

        switch (choice) {
            case 1: cpuScheduling();    break;
            case 2: memoryAllocation(); break;
            case 3: pageReplacement();  break;
            case 4: diskScheduling();   break;
            case 5: printf("\nExiting Operating System Simulator...\n"); break;
            default: printf("\nInvalid choice.\n");
        }
    } while (choice != 5);

    return 0;
}