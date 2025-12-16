/*

Experiment 4: Round Robin (RR)
Algorithm
1. Input time quantum.
2. Maintain a queue of ready processes.
3. Run each process for time quantum or remaining time.
4. If incomplete, push back into queue.
5. Compute CT, TAT, WT.

*/
//Program (RR.c)
#include <stdio.h>
struct Process {
 int pid, at, bt, ct, tat, wt, rt;
};
int main() {
  int n, tq;
  printf("Enter number of processes: ");
  scanf("%d", &n);
  struct Process p[n];
  for (int i = 0; i < n; i++) {
    p[i].pid = i + 1;
    printf("Enter Arrival Time and Burst Time of Process %d: ", i + 1);
    scanf("%d %d", &p[i].at, &p[i].bt);
    p[i].rt = p[i].bt;
  }
 printf("Enter Time Quantum: ");
 scanf("%d", &tq);
 int time = 0, completed = 0, sumTAT = 0, sumWT = 0;
 while (completed < n) {
    int flag = 0;
    for (int i = 0; i < n; i++) {
       if (p[i].rt > 0 && p[i].at <= time) {
          flag = 1;
          if (p[i].rt > tq) {
              time += tq;
              p[i].rt -= tq;
          } else {
             time += p[i].rt;
             p[i].rt = 0;
             p[i].ct = time;
             p[i].tat = p[i].ct - p[i].at;
             p[i].wt = p[i].tat - p[i].bt;
             sumTAT += p[i].tat;
             sumWT += p[i].wt;
             completed++;
         }
     }
  }
  if (!flag) time++;
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
Enter Arrival Time and Burst Time of Process 2: 1 4
Enter Arrival Time and Burst Time of Process 3: 2 2
Enter Time Quantum: 2
PID AT BT CT TAT WT
1 0 5 11 11 6
2 1 4 12 11 7
3 2 2 6 4 2
Average TAT = 8.67
Average WT = 5.00

*/