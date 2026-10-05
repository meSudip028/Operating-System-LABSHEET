#include <stdio.h>
 
int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);
 
    int at[n], bt[n], rt[n], ct[n], tat[n], wt[n];
 
    for (int i = 0; i < n; i++) {
        printf("Enter Arrival Time and Burst Time for P%d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }
 
    printf("Enter Time Quantum: ");
    scanf("%d", &tq);
 
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
 
    int queue[1000], front = 0, rear = 0;
    int in_queue[n];
    for (int i = 0; i < n; i++) in_queue[i] = 0;
 
    for (int i = 0; i < n; i++)          // enqueue processes that arrive at time 0
        if (at[i] <= time && !in_queue[i]) { queue[rear++] = i; in_queue[i] = 1; }
 
    while (completed < n) {
        if (front == rear) {             // queue empty -> jump to next arrival
            time++;
            for (int i = 0; i < n; i++)
                if (at[i] <= time && !in_queue[i]) { queue[rear++] = i; in_queue[i] = 1; }
            continue;
        }
 
        int idx = queue[front++];
        int run_time = (rt[idx] < tq) ? rt[idx] : tq;
        time += run_time;
        rt[idx] -= run_time;
 
        // enqueue any process that arrived during this time slice
        for (int i = 0; i < n; i++)
            if (at[i] <= time && !in_queue[i]) { queue[rear++] = i; in_queue[i] = 1; }
 
        if (rt[idx] > 0) {
            queue[rear++] = idx;         // not finished -> back of the queue
        } else {
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