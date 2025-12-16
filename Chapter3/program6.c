/*
Experiment - 6 : Process Synchronization using Test-and-Set Lock 
(TSL).
Algorithm :-
1. Initialize a lock variable to 0 (unlocked).
2. Before entering the critical section, each process executes the test_and_set() function.
3. If the lock is 0, set it to 1 and enter the critical section.
4. If the lock is 1, keep waiting (busy-waiting).
5. After leaving the critical section, reset the lock to 0.
6. Repeat the process for all processes.

*/

//Program :
#include <stdio.h>
#include <stdbool.h>
int lock = 0; // 0 = unlocked, 1 = locked
// Test and Set function
int test_and_set(int *target) {
 int rv = *target;
 *target = 1;
 return rv;
}
void critical_section(int process_id) {
 printf("Process %d is entering critical section...\n", process_id);
 printf("Process %d is inside critical section\n", process_id);
 printf("Process %d is leaving critical section...\n", process_id);
}
void process(int process_id) {
 while (test_and_set(&lock))
 ; // Busy waiting
 // Critical Section
 critical_section(process_id);
 // Release Lock
 lock = 0;
}
int main() {
   printf("Process Synchronization using Test-and-Set Lock\n\n");
   for (int i = 1; i <= 3; i++) {
   process(i);
 }
 return 0;
}

/*
Output: 
Process Synchronization using Test-and-Set Lock
Process 1 is entering critical section...
Process 1 is inside critical section 
Process 1 is leaving critical section... 
Process 2 is entering critical section...
Process 2 is inside critical section 
Process 2 is leaving critical section... 
Process 3 is entering critical section...
Process 3 is inside critical section 
Process 3 is leaving critical section...

*/