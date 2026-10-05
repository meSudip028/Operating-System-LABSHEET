#include <stdio.h>
 
struct Process {
    int pid, at, bt, pr, ct, tat, wt, completed;
};
 
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].completed = 0;
        printf("Enter Arrival Time, Burst Time, Priority for P%d: ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
    }
 
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
 
    while (completed < n) {
        int idx = -1, best_pr = 9999; // lower number = higher priority
 
        for (int i = 0; i < n; i++)
            if (!p[i].completed && p[i].at <= time && p[i].pr < best_pr) {
                best_pr = p[i].pr;
                idx = i;
            }
 
        if (idx == -1) { time++; continue; }
 
        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        p[idx].completed = 1;
        completed++;
 
        total_tat += p[idx].tat;
        total_wt += p[idx].wt;
    }
 
    printf("\nPID\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, p[i].tat, p[i].wt);
 
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time   = %.2f\n", total_wt / n);
    return 0;
}
