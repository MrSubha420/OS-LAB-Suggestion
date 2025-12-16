/* Experiment 5: Priority Scheduling
Algorithm
1. Input Priority for each process (higher number = higher priority).
2. At each step, choose process with highest priority among arrived.
3. Compute CT, TAT, WT.
4. Compute averages.

*/
//Program (Priority.c)
#include <stdio.h>
struct Process {
 int pid, at, bt, pr, ct, tat, wt, done;
};
int main() {
 int n;
 printf("Enter number of processes: ");
 scanf("%d", &n);
 struct Process p[n];
 for (int i = 0; i < n; i++) {
   p[i].pid = i + 1;
   printf("Enter Arrival Time, Burst Time and Priority of Process %d: ", i + 1);
   scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pr);
   p[i].done = 0;
 }
 int time = 0, completed = 0, sumTAT = 0, sumWT = 0;
 while (completed < n) {
    int idx = -1, maxP = -1;
     for (int i = 0; i < n; i++) {
       if (!p[i].done && p[i].at <= time && p[i].pr > maxP) {
          maxP = p[i].pr;
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
     sumTAT += p[idx].tat;
     sumWT += p[idx].wt;
     p[idx].done = 1;
     completed++;
   }
 }
 printf("\nPID\tAT\tBT\tPR\tCT\tTAT\tWT\n");
 for (int i = 0; i < n; i++) {
   printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pr, p[i].ct, 
   p[i].tat, p[i].wt);
 }
 printf("\nAverage TAT = %.2f", (float)sumTAT/n);
 printf("\nAverage WT = %.2f\n", (float)sumWT/n);
 return 0;
}

/*
Sample Output:
Enter number of processes: 3
Enter Arrival Time, Burst Time and Priority of Process 1: 0 5 2
Enter Arrival Time, Burst Time and Priority of Process 2: 1 3 3
Enter Arrival Time, Burst Time and Priority of Process 3: 2 4 1
PID AT BT PR CT TAT WT
2 1 3 3 4 3 0
1 0 5 2 9 9 4
3 2 4 1 13 11 7
Average TAT = 7.67
Average WT = 3.67

*/