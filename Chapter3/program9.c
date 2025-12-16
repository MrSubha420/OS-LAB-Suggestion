/*
Experiment  4 : Process Synchronization using Test-and-Set Lock
with Binary Semaphore.
Algorithm :-
1. START
2. INIT lock = 0
3. INIT process_state[NUM_PROCESSES] = WAITING
4. CREATE binary_semaphore = 1
5. WHILE (not all processes completed):
 DISPLAY process table
 SHOW available processes
 INPUT process_id
 IF invalid process_id → CONTINUE
 IF process COMPLETED → CONTINUE
 IF CS locked → CONTINUE
 START process thread
 WAIT for thread to finish
 CLOSE thread handle
 UPDATE completed_count
6. PRINT "All processes completed"
7. CLOSE semaphore
8. END

*/
// Program :-
#include <stdio.h>
#include <windows.h>
#define NUM_PROCESSES 3
// Process states
#define WAITING 0
#define RUNNING 1
#define COMPLETED 2
int lock = 0;
HANDLE binary_semaphore;
int process_state[NUM_PROCESSES] = {WAITING, WAITING, WAITING};
int process_ids[NUM_PROCESSES] = {0, 1, 2};
// Test-and-Set Lock
int test_and_set(int *target)
{
   int rv = *target;
   *target = 1;
   return rv;
}
// Display process table
void display_table()
{
   printf("\n-------------------------------------------------------\n");
   printf("| Process | State |\n");
   printf("-------------------------------------------------------\n");
   for (int i = 0; i < NUM_PROCESSES; i++)
   {
      printf("| P%d | ", i);
      if (process_state[i] == WAITING)
         printf("WAITING |\n");
      else if (process_state[i] == RUNNING)
         printf("RUNNING |\n");
      else
         printf("COMPLETED |\n");
   }
   printf("-------------------------------------------------------\n");
}
// Process function
DWORD WINAPI process(LPVOID arg)
{
   int process_id = *(int *)arg;
   // Acquire semaphore
   WaitForSingleObject(binary_semaphore, INFINITE);
   // Busy-wait if locked
   while (test_and_set(&lock))
      ;
   process_state[process_id] = RUNNING;
   display_table();
   printf(">> Process P%d ENTERED critical section\n", process_id);
   int choice;
   while (1)
   {
      printf("\nProcess P%d is inside CS. Choose an option:\n", process_id);
      printf("1. Exit process\n");
      printf("2. Continue next process without exiting\n");
      printf("Enter your choice: ");
      scanf("%d", &choice);
      if (choice == 1)
      {
         printf(">> Process P%d EXITING critical section\n", process_id);
         process_state[process_id] = COMPLETED;
         lock = 0; // Release lock
         ReleaseSemaphore(binary_semaphore, 1, NULL);
         break;
      }
      else if (choice == 2)
      {
         printf(">> Process P%d stays inside critical section. No other process can enter!\n",
                process_id);
      }
      else
      {
         printf("Invalid choice! Try again.\n");
      }
   }
   return 0;
}
int main()
{
   printf("=== Process Synchronization using Test-and-Set Lock + Binary Semaphore (Galvin) ===\n");
   HANDLE threads[NUM_PROCESSES];
   // Create binary semaphore (value = 1)
   binary_semaphore = CreateSemaphore(NULL, 1, 1, NULL);
   int choice;
   int completed_count = 0;
   while (completed_count < NUM_PROCESSES)
   {
      display_table();
      printf("\nAvailable Processes: ");
      for (int i = 0; i < NUM_PROCESSES; i++)
      {
         if (process_state[i] == WAITING)
            printf("P%d ", i);
      }
      printf("\nChoose a process to execute (0-%d): ", NUM_PROCESSES - 1);
      scanf("%d", &choice);
      if (choice < 0 || choice >= NUM_PROCESSES)
      {
         printf("Invalid process! Please enter a valid ID.\n");
         continue;
      }
      if (process_state[choice] == COMPLETED)
      {
         printf("Process P%d has ALREADY completed. Choose another.\n", choice);
         continue;
      }
      if (lock == 1 && process_state[choice] == WAITING)
      {
         printf("Process P%d cannot execute because the CS is LOCKED by another process.\n",
                choice);
         continue;
      }
      // Start the chosen process
      threads[choice] = CreateThread(NULL, 0, process, &process_ids[choice], 0, NULL);
      // Wait for the thread to finish
      WaitForSingleObject(threads[choice], INFINITE);
      CloseHandle(threads[choice]);
      // Check completed count
      completed_count = 0;
      for (int i = 0; i < NUM_PROCESSES; i++)
      {
         if (process_state[i] == COMPLETED)
            completed_count++;
      }
   }
   printf("\n=== All processes have COMPLETED ===\n");
   CloseHandle(binary_semaphore);
   return 0;
}

/*
Output: -
=== Process Synchronization using Test-and-Set Lock + Binary Semaphore
(Galvin) ===
-------------------------------------------------------
| Process | State |
-------------------------------------------------------
| P0 | WAITING |
| P1 | WAITING |
| P2 | WAITING |
-------------------------------------------------------
Available Processes: P0 P1 P2
Choose a process to execute (0-2): 0
-------------------------------------------------------
| Process | State |
-------------------------------------------------------
| P0 | RUNNING |
| P1 | WAITING |
| P2 | WAITING |
-------------------------------------------------------
>> Process P0 ENTERED critical section
Process P0 is inside CS. Choose an option:
1. Exit process
2. Continue next process without exiting
Enter your choice: 1
>> Process P0 EXITING critical section
-------------------------------------------------------
| Process | State |
-------------------------------------------------------
| P0 | COMPLETED |
| P1 | WAITING |
| P2 | WAITING |
-------------------------------------------------------
Available Processes: P1 P2
Choose a process to execute (0-2): 1
-------------------------------------------------------
| Process | State |
-------------------------------------------------------
| P0 | COMPLETED |
| P1 | RUNNING |
| P2 | WAITING |
-------------------------------------------------------
>> Process P1 ENTERED critical section
Process P1 is inside CS. Choose an option:
1. Exit process
2. Continue next process without exiting
Enter your choice: 2
>> Process P1 stays inside critical section. No other process can enter!
Process P1 is inside CS. Choose an option:
1. Exit process
2. Continue next process without exiting
Enter your choice: 1
>> Process P1 EXITING critical section
-------------------------------------------------------
| Process | State |
-------------------------------------------------------
| P0 | COMPLETED |
| P1 | COMPLETED |
| P2 | WAITING |
-------------------------------------------------------
Available Processes: P2
Choose a process to execute (0-2): 2
-------------------------------------------------------
| Process | State |
-------------------------------------------------------
| P0 | COMPLETED |
| P1 | COMPLETED |
| P2 | RUNNING |
-------------------------------------------------------
>> Process P2 ENTERED critical section
Process P2 is inside CS. Choose an option:
1. Exit process
2. Continue next process without exiting
Enter your choice: 2
>> Process P2 stays inside critical section. No other process can enter!
Process P2 is inside CS. Choose an option:
1. Exit process
2. Continue next process without exiting
Enter your choice: 1
>> Process P2 EXITING critical section
=== All processes have COMPLETED ===

*/