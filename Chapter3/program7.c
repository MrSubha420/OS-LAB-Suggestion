/*

Experiment -7 : Process Synchronization using Turn Variable.
Algorithm :-
1. START
2. INPUT initial turn
3. IF turn not in {0,1} → set turn = 0
4. INPUT number of rounds
5. FOR i = 1 TO rounds DO
 a. DISPLAY current turn
 b. REPEAT
 i. INPUT process_choice
 ii. IF process_choice not in {0,1} → ask again
 iii. IF process_choice != turn → ask again
 iv. ELSE execute critical_section(process_choice)
 turn = 1 - process_choice
 BREAK
 UNTIL valid choice entered
6. DISPLAY "All rounds completed successfully."
7. END

*/
//Program :-
#include <stdio.h>
#include <unistd.h>
int turn; // Shared variable (0 for P0, 1 for P1)
// Function to simulate the critical section
void critical_section(int process_id)
{
   printf("Process %d is ENTERING critical section...\n", process_id);
   sleep(1);
   printf("Process %d is INSIDE critical section\n", process_id);
   sleep(1);
   printf("Process %d is LEAVING critical section...\n", process_id);
   printf("---------------------------------------------\n");
}
int main()
{
   int rounds;
   printf("=== Process Synchronization using Turn Variable ===\n");
   printf("Enter initial turn (0 for Process 0, 1 for Process 1): ");
   scanf("%d", &turn);
   if (turn != 0 && turn != 1)
   {
      printf("Invalid input! Defaulting turn to Process 0.\n");
      turn = 0;
   }
   printf("Enter number of rounds to execute: ");
   scanf("%d", &rounds);
   printf("\nStarting execution...\n\n");
   for (int i = 0; i < rounds; i++)
   {
      int process_choice;
      while (1)
      {
         printf("[Round %d] Current Turn = %d → Process %d should execute\n", i + 1, turn,
                turn);
         printf("Enter the process to execute (0 for P0, 1 for P1): ");
         scanf("%d", &process_choice);
         if (process_choice != 0 && process_choice != 1)
         {
            printf(" Invalid process choice! Please enter 0 or 1.\n\n");
            continue;
         }
         if (process_choice != turn)
         {
            printf(" Process P%d cannot execute because TURN = %d.\n", process_choice, turn);
            printf("Please select Process P%d instead.\n\n", turn);
            continue;
         }
         // If process choice is correct → Execute
         printf(" Process P%d is allowed to execute.\n", process_choice);
         critical_section(process_choice);
         // Switch turn
         turn = 1 - process_choice;
         printf(" Turn changed → Now it's Process P%d's turn.\n\n", turn);
         break;
      }
   }
   printf("All %d rounds completed successfully.\n", rounds);
   return 0;
}

/*Output: -

=== Process Synchronization using Turn Variable ===
Enter initial turn (0 for Process 0, 1 for Process 1): 1
Enter number of rounds to execute: 4
Starting execution...
[Round 1] Current Turn = 1 ΓåÆ Process 1 should execute
Enter the process to execute (0 for P0, 1 for P1): 0 
 Process P0 cannot execute because TURN = 1.
Please select Process P1 instead.
[Round 1] Current Turn = 1 ΓåÆ Process 1 should execute
Enter the process to execute (0 for P0, 1 for P1): 1 
Process P1 is allowed to execute. 
Process 1 is ENTERING critical section...
Process 1 is INSIDE critical section
Process 1 is LEAVING critical section...
---------------------------------------------
Turn changed ΓåÆ Now it's Process P0's turn.
[Round 2] Current Turn = 0 ΓåÆ Process 0 should execute
Enter the process to execute (0 for P0, 1 for P1): 1
 Process P1 cannot execute because TURN = 0.
Please select Process P0 instead.
[Round 2] Current Turn = 0 ΓåÆ Process 0 should execute
Enter the process to execute (0 for P0, 1 for P1): 0
Process P0 is allowed to execute.
Process 0 is ENTERING critical section...
Process 0 is INSIDE critical section
Process 0 is LEAVING critical section...
---------------------------------------------
Turn changed ΓåÆ Now it's Process P1's turn.
[Round 3] Current Turn = 1 ΓåÆ Process 1 should execute
Enter the process to execute (0 for P0, 1 for P1): 1
Process P1 is allowed to execute.
Process 1 is ENTERING critical section...
Process 1 is INSIDE critical section
Process 1 is LEAVING critical section...
---------------------------------------------
Turn changed ΓåÆ Now it's Process P0's turn.
[Round 4] Current Turn = 0 ΓåÆ Process 0 should execute
Enter the process to execute (0 for P0, 1 for P1): 0
Process P0 is allowed to execute.
Process 0 is ENTERING critical section...
Process 0 is INSIDE critical section
Process 0 is LEAVING critical section...
---------------------------------------------
Turn changed ΓåÆ Now it's Process P1's turn.

*/