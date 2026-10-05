#include <stdio.h>
 
struct Process {
    int pid, at, bt, ct, tat, wt, completed;
};
 
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
 
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
 
    while (completed < n) {
        int idx = -1, min_bt = 9999;
 
        // pick the shortest-burst process among those that have arrived
        for (int i = 0; i < n; i++)
            if (!p[i].completed && p[i].at <= time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
 
        if (idx == -1) { time++; continue; } // CPU idle, nothing has arrived yet
 
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;
        completed++;
 
        total_tat += p[idx].tat;
        total_wt += p[idx].wt;
    }
 
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
 
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time   = %.2f\n", total_wt / n);
    return 0;
}
