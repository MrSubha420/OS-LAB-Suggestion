/*Experiment 10: Memory Management with Fixed Size Partitioning

Description:
* In fixed-size partitioning, the main memory is divided into equal-sized partitions.
* Each process is loaded into a single free partition that is large enough to accommodate it.
* If no partition is large enough, the process must wait.
* This method leads to internal fragmentation.
* The experiment demonstrates allocation and display of memory partitions for given processes.

Algorithm:
1. Start the program.
2. Input the number of partitions and their fixed size.
3. Input the number of processes and their memory requirements.
4. For each process, check if it fits into a free partition.

   * If yes, allocate it and mark that partition as occupied.
   * If not, display that it cannot be allocated.
5. Display the final allocation table.
6. Stop the program.
*/

//Source Code:
#include <stdio.h>

int main() {
    int partitionSize, numPartitions, numProcesses;
    int processSize[20];

    printf("Enter number of partitions: ");
    scanf("%d", &numPartitions);

    printf("Enter size of each partition: ");
    scanf("%d", &partitionSize);

    printf("Enter number of processes: ");
    scanf("%d", &numProcesses);

    for (int i = 0; i < numProcesses; i++) {
        printf("Enter size of process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    int allocatedPartition[20]; // stores partition number for each process
    for (int i = 0; i < numProcesses; i++) {
        allocatedPartition[i] = -1; // initially unallocated
    }

    printf("\n--- Memory Allocation ---\n");

    int partition = 0; // track which partition is free
    for (int i = 0; i < numProcesses; i++) {
        if (processSize[i] <= partitionSize && partition < numPartitions) {
            allocatedPartition[i] = partition + 1;
            printf("Process %d of size %d allocated to Partition %d\n",
                   i + 1, processSize[i], partition + 1);
            partition++;
        } else {
            printf("Process %d of size %d cannot be allocated (Not enough space)\n",
                   i + 1, processSize[i]);
        }
    }

    printf("\n--- Final Memory Status ---\n");
    for (int i = 0; i < numPartitions; i++) {
        int found = 0;
        for (int j = 0; j < numProcesses; j++) {
            if (allocatedPartition[j] == i + 1) {
                printf("Partition %d: Occupied by Process %d (Size: %d)\n",
                       i + 1, j + 1, processSize[j]);
                found = 1;
                break;
            }
        }
        if (!found)
            printf("Partition %d: Empty\n", i + 1);
    }

    return 0;
}

/* Output: -
Enter number of partitions: 5
Enter size of each partition: 100  
Enter number of processes: 3
Enter size of process 1: 100
Enter size of process 2: 300
Enter size of process 3: 20

--- Memory Allocation ---
Process 1 of size 100 allocated to Partition 1
Process 2 of size 300 cannot be allocated (Not enough space)
Process 3 of size 20 allocated to Partition 2

--- Final Memory Status ---
Partition 1: Occupied by Process 1 (Size: 100)
Partition 2: Occupied by Process 3 (Size: 20)
Partition 3: Empty
Partition 4: Empty
Partition 5: Empty
*/
