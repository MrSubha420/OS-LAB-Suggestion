/*
Experiment 8 : Process Synchronization using Counting
Semaphore.
Algorithm :-
1. START
2. INPUT buffer_size → CS slots
3. INPUT total_processes
4. SET count = buffer_size
5. INIT process_state[i] = WAITING for all processes
6. DISPLAY process table
7. WHILE (true):
 INPUT pid
 IF pid == -1 → EXIT program
 IF invalid pid → SHOW error → CONTINUE
 CALL execute_process(pid)
 remaining = count of processes != COMPLETED
 IF remaining == 0 → BREAK
8. FOR all processes still INSIDE:
 signal_semaphore()
 process_state[i] = COMPLETED
9. DISPLAY final process table
10. PRINT "Simulation ended. All processes COMPLETED."
11. END

*/
// Program :-
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define WAITING 0
#define INSIDE 1
#define COMPLETED 2
int buffer_size;
int count;
int total_processes;
int *process_state;
// Decrement semaphore
void wait_semaphore()
{
   count--;
}
// Increment semaphore
void signal_semaphore()
{
   count++;
}
/* Display process table */
void display_table()
{
   printf("\n----------------------------------------------\n");
   printf("| Process | State | Slots = %d |\n", count);
   printf("----------------------------------------------\n");
   for (int i = 0; i < total_processes; i++)
   {
      printf("| P%-5d | ", i + 1);
      if (process_state[i] == WAITING)
         printf("WAITING ");
      else if (process_state[i] == INSIDE)
         printf("INSIDE CS ");
      else
         printf("COMPLETED ");
      printf("|\n");
   }
   printf("----------------------------------------------\n");
}
/* Exit a process manually */
void exit_process()
{
   int pid;
   printf("Enter process number to EXIT (1 - %d): ", total_processes);
   scanf("%d", &pid);
   pid--;
   if (pid < 0 || pid >= total_processes)
   {
      printf("Invalid process ID.\n");
      return;
   }
   if (process_state[pid] == INSIDE)
   {
      signal_semaphore();
      process_state[pid] = COMPLETED;
      printf("Process P%d EXITED critical section.\n", pid + 1);
   }
   else
   {
      printf("Process P%d is NOT inside CS.\n", pid + 1);
   }
   display_table();
}
/* Execute a process */
void execute_process(int pid)
{
   if (process_state[pid] == COMPLETED)
   {
      printf("Process P%d already completed.\n", pid + 1);
      return;
   }
   if (process_state[pid] == INSIDE)
   {
      printf("Process P%d is already inside CS.\n", pid + 1);
      return;
   }
   if (count == 0)
   {
      printf("CS full! Cannot enter P%d.\n", pid + 1);
      printf("Options:\n1. Exit a process\n2. Skip this process\nEnter choice: ");
      int choice;
      scanf("%d", &choice);
      if (choice == 1)
      {
         exit_process();
         if (count > 0)
         {
            execute_process(pid); // Retry after freeing slot
         }
      }
      return;
   }
   // Process can enter CS
   wait_semaphore();
   process_state[pid] = INSIDE;
   display_table();
   printf("Process P%d ENTERED CS.\n", pid + 1);
   // Ask to exit
   int exit_choice;
   printf("Exit P%d now? (1 = Yes, 0 = No): ", pid + 1);
   scanf("%d", &exit_choice);
   if (exit_choice == 1)
   {
      signal_semaphore();
      process_state[pid] = COMPLETED;
      printf("Process P%d EXITED CS.\n", pid + 1);
   }
   else
   {
      printf("Process P%d stays inside CS.\n", pid + 1);
   }
   display_table();
}
int main()
{
   printf("=== Counting Semaphore Process Synchronization ===\n");
   printf("Enter buffer size (CS slots): ");
   scanf("%d", &buffer_size);
   printf("Enter total number of processes: ");
   scanf("%d", &total_processes);
   count = buffer_size;
   process_state = (int *)calloc(total_processes, sizeof(int));
   display_table();
   while (1)
   {
      int pid;
      printf("\nEnter process ID (1 to %d) to execute (-1 to exit): ", total_processes);
      scanf("%d", &pid);
      if (pid == -1)
         break;
      pid--; // convert to 0-based
      if (pid < 0 || pid >= total_processes)
      {
         printf("Invalid process ID!\n");
         continue;
      }
      execute_process(pid);
      // Check if all completed
      int remaining = 0;
      for (int i = 0; i < total_processes; i++)
         if (process_state[i] != COMPLETED)
            remaining++;
      if (remaining == 0)
      {
         printf("\nAll processes completed successfully!\n");
         break;
      }
   }
   // Force exit any remaining processes still inside CS
   for (int i = 0; i < total_processes; i++)
   {
      if (process_state[i] == INSIDE)
      {
         printf("Process P%d was exit from CS.\n", i + 1);
         signal_semaphore();
         process_state[i] = COMPLETED;
      }
   }
   display_table();
   printf("\nSimulation ended. All processes are now COMPLETED.\n");
   free(process_state);
   return 0;
}

/*
Output: -
Enter buffer size (CS slots): 2
Enter total number of processes: 4
----------------------------------------------
| Process | State | Slots = 2 |
----------------------------------------------
| P1 | WAITING |
| P2 | WAITING |
| P3 | WAITING |
| P4 | WAITING |
----------------------------------------------
Enter process ID (1 to 4) to execute (-1 to exit): 1
----------------------------------------------
| Process | State | Slots = 1 |
----------------------------------------------
| P1 | INSIDE CS |
| P2 | WAITING |
| P3 | WAITING |
| P4 | WAITING |
----------------------------------------------
Process P1 ENTERED CS.
Exit P1 now? (1 = Yes, 0 = No): 1
Process P1 EXITED CS.
----------------------------------------------
| Process | State | Slots = 2 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | WAITING |
| P3 | WAITING |
| P4 | WAITING |
----------------------------------------------
Enter process ID (1 to 4) to execute (-1 to exit): 1
Process P1 already completed.
Enter process ID (1 to 4) to execute (-1 to exit): 2
----------------------------------------------
| Process | State | Slots = 1 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | INSIDE CS |
| P3 | WAITING |
| P4 | WAITING |
----------------------------------------------
Process P2 ENTERED CS.
Exit P2 now? (1 = Yes, 0 = No): 0
Process P2 stays inside CS.
----------------------------------------------
| Process | State | Slots = 1 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | INSIDE CS |
| P3 | WAITING |
| P4 | WAITING |
----------------------------------------------
Enter process ID (1 to 4) to execute (-1 to exit): 3
----------------------------------------------
| Process | State | Slots = 0 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | INSIDE CS |
| P3 | INSIDE CS |
| P4 | WAITING |
----------------------------------------------
Process P3 ENTERED CS.
Exit P3 now? (1 = Yes, 0 = No): 0
Process P3 stays inside CS.
----------------------------------------------
| Process | State | Slots = 0 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | INSIDE CS |
| P3 | INSIDE CS |
| P4 | WAITING |
----------------------------------------------
Enter process ID (1 to 4) to execute (-1 to exit): 4
CS full! Cannot enter P4.
Options:
1. Exit a process
2. Skip this process
Enter choice: 2
Enter process ID (1 to 4) to execute (-1 to exit): 4
CS full! Cannot enter P4.
Options:
1. Exit a process
2. Skip this process
Enter choice: 1
Enter process number to EXIT (1 - 4): 2
Process P2 EXITED critical section.
----------------------------------------------
| Process | State | Slots = 1 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | COMPLETED |
| P3 | INSIDE CS |
| P4 | WAITING |
----------------------------------------------
----------------------------------------------
| Process | State | Slots = 0 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | COMPLETED |
| P3 | INSIDE CS |
| P4 | INSIDE CS |
----------------------------------------------
Process P4 ENTERED CS.
Exit P4 now? (1 = Yes, 0 = No): 1
Process P4 EXITED CS.
----------------------------------------------
| Process | State | Slots = 1 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | COMPLETED |
| P3 | INSIDE CS |
| P4 | COMPLETED |
----------------------------------------------
Enter process ID (1 to 4) to execute (-1 to exit): -1
Process P3 was still inside CS. Forcing EXIT.
----------------------------------------------
| Process | State | Slots = 2 |
----------------------------------------------
| P1 | COMPLETED |
| P2 | COMPLETED |
| P3 | COMPLETED |
| P4 | COMPLETED |
----------------------------------------------
Simulation ended. All processes are now COMPLETED.

*/