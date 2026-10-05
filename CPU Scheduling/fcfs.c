#include <stdio.h>
 
struct Process {
    int pid, at, bt, ct, tat, wt;
};
 
int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    struct Process p[n];
 
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
 
    // Sort processes by Arrival Time (simple bubble sort)
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
 
    int time = 0;
    float total_tat = 0, total_wt = 0;
 
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;      // CPU stays idle until process arrives
 
        time += p[i].bt;
        p[i].ct = time;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
 
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
 
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
 
    printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
    printf("Average Waiting Time   = %.2f\n", total_wt / n);
    return 0;
}