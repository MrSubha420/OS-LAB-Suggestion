/* 

Experiment 3: SRTF Scheduling (Preemptive)
Algorithm
1. At each time, select the process with shortest remaining time among arrived.
2. Execute 1 unit, update remaining time.
3. When a process finishes, record CT, TAT, WT.
4. Compute averages.

*/
//Program (SRTF.c)
#include <stdio.h>
struct Process {
 int pid, at, bt, ct, tat, wt, rt;
};
int main() {
 int n, time = 0, completed = 0;
 printf("Enter number of processes: ");
 scanf("%d", &n);
 struct Process p[n];
 for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    printf("Enter Arrival Time and Burst Time of Process %d: ", i + 1);
    scanf("%d %d", &p[i].at, &p[i].bt);
    p[i].rt = p[i].bt;
 }
 int sumTAT = 0, sumWT = 0;
 while (completed < n) {
    int idx = -1, minRT = 1e9;
    for (int i = 0; i < n; i++) {
       if (p[i].at <= time && p[i].rt > 0 && p[i].rt < minRT) {
          minRT = p[i].rt;
          idx = i;
      }
   }
   if (idx == -1) {
    time++;
    } else {
        p[idx].rt--;
        time++;
   if (p[idx].rt == 0) {
         p[idx].ct = time;
         p[idx].tat = p[idx].ct - p[idx].at;
         p[idx].wt = p[idx].tat - p[idx].bt;
         completed++;
         sumTAT += p[idx].tat;
         sumWT += p[idx].wt;
      }
   }
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
Sample Output
Enter number of processes: 3
Enter Arrival Time and Burst Time of Process 1: 0 6
Enter Arrival Time and Burst Time of Process 2: 2 4
Enter Arrival Time and Burst Time of Process 3: 4 2
PID AT BT CT TAT WT
1 0 6 12 12 6
2 2 4 8 6 2
3 4 2 6 2 0
Average TAT = 6.67
Average WT = 2.67

*/