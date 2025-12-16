/*

Experiment 1: FCFS Scheduling

Algorithm:
1. Sort processes by arrival time.
2. Compute Completion Time (CT):
3. CT=max(AT,prev_CT)+BT
4. Compute TAT = CT – AT.
5. Compute WT = TAT – BT.
6. Calculate Average TAT and Average WT.

*/

// Program (FCFS.c)
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
    printf("Enter Arrival Time and Burst Time of Process %d: ", i + 1);
    scanf("%d %d", &p[i].at, &p[i].bt);
 }
 // Sort by Arrival Time
 for (int i = 0; i < n - 1; i++) {
      for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
         }
      }
 int time = 0, sumTAT = 0, sumWT = 0;
 for (int i = 0; i < n; i++) {
      if (time < p[i].at) time = p[i].at;
         time += p[i].bt;
         p[i].ct = time;
         p[i].tat = p[i].ct - p[i].at;
         p[i].wt = p[i].tat - p[i].bt;
         sumTAT += p[i].tat;
         sumWT += p[i].wt;
        }
 printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
 for (int i = 0; i < n; i++) {
 printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
 }
 printf("\nAverage TAT = %.2f", (float)sumTAT/n);
 printf("\nAverage WT = %.2f\n", (float)sumWT/n);
 return 0;
}

/*
Sample Output:
Enter number of processes: 3
Enter Arrival Time and Burst Time of Process 1: 0 5
Enter Arrival Time and Burst Time of Process 2: 1 3
Enter Arrival Time and Burst Time of Process 3: 2 8
PID AT BT CT TAT WT
1 0 5 5 5 0
2 1 3 8 7 4
3 2 8 16 14 6
Average TAT = 8.67
Average WT = 3.33

*/