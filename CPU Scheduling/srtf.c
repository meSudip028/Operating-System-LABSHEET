#include <stdio.h>
#include <limits.h>
 
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n], done[n];
 
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];  // remaining time
        done[i] = 0;
    }
 
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
 
    while (completed < n) {
        int idx = -1, min_rt = INT_MAX;
 
        // pick the process with shortest remaining time among those arrived
        for (int i = 0; i < n; i++)
            if (!done[i] && at[i] <= time && rt[i] > 0 && rt[i] < min_rt) {
                min_rt = rt[i];
                idx = i;
            }
 
        if (idx == -1) { time++; continue; } // CPU idle
 
        rt[idx]--;   // run the chosen process for 1 unit of time
        time++;
 
        if (rt[idx] == 0) {
            done[idx] = 1;
            completed++;
            ct[idx] = time;
            tat[idx] = ct[idx] - at[idx];
            wt[idx] = tat[idx] - bt[idx];
            total_tat += tat[idx];
            total_wt += wt[idx];
        }
    }
 
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               i + 1, at[i], bt[i], ct[i], tat[i], wt[i]);
 
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time   = %.2f\n", total_wt / n);
    return 0;
}
