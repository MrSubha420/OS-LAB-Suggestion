/*

Experiment 2: SJF Scheduling (Non-preemptive)
Algorithm
1. Sort processes by arrival time.
2. At each step, choose process with shortest burst time among available ones.
3. Compute CT, TAT, WT.
4. Calculate averages.

*/

// Program (SJF.c)
#include <stdio.h>
struct Process {
 int pid, at, bt, ct, tat, wt, done;
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
    p[i].done = 0;
  }
 int time = 0, completed = 0, sumTAT = 0, sumWT = 0;
 while (completed < n) {
    int idx = -1, minBT = 1e9;
      for (int i = 0; i < n; i++) {
         if (!p[i].done && p[i].at <= time && p[i].bt < minBT) {
             minBT = p[i].bt;
             idx = i;
         }
      }
     if (idx == -1) {
     time++;
     } else {
            time += p[idx].bt;
            p[idx].ct = time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            p[idx].done = 1;
            completed++;
            sumTAT += p[idx].tat;
            sumWT += p[idx].wt;
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
Sample Output : 
Enter number of processes: 3
Enter Arrival Time and Burst Time of Process 1: 0 7
Enter Arrival Time and Burst Time of Process 2: 2 4
Enter Arrival Time and Burst Time of Process 3: 4 1
PID AT BT CT TAT WT
1 0 7 7 7 0
3 4 1 8 4 3
2 2 4 12 10 6
Average TAT = 7.00
Average WT = 3.00
Experiment 3: SRTF Scheduling (Preemptive)
Algorithm
1. At each time, select the process with shortest remaining time among arrived.
2. Execute 1 unit, update remaining time.
3. When a process finishes, record CT, TAT, WT.
4. Compute averages.
*/