/*

Expertiment 11: Memory Management with Variable Size Partitioning.(First Fit, Best Fit, Worst Fit)

Description:
* In variable-size partitioning, memory blocks of different sizes are allocated to processes based on their
* memory requirements. This method helps to reduce internal fragmentation.
* The experiment demonstrates three allocation strategies: First Fit, Best Fit, and Worst Fit.
* Each strategy allocates memory blocks to processes differently, affecting memory utilization and fragmentation.

Algorithm:
1. Start the program.
2. Input the number of memory blocks and their sizes.
3. Input the number of processes and their memory requirements.
4. Implement three allocation strategies:
   a. First Fit: Allocate the first block that is large enough.
   b. Best Fit: Allocate the smallest block that is large enough.
   c. Worst Fit: Allocate the largest block available.
5. Display the allocation results for each strategy.
6. Stop the program.
*/
#include <stdio.h>

void firstFit(int bSize[], int m, int pSize[], int n) {
    int allocation[20];
    int temp[20];

    // Copy block sizes 
    for (int i = 0; i < m; i++)
        temp[i] = bSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (temp[j] >= pSize[i]) {
                allocation[i] = j;
                temp[j] -= pSize[i];
                break;
            }
        }
    }

    printf("\n--- FIRST FIT ---\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tB%d\n", i + 1, pSize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, pSize[i]);
    }
}

void bestFit(int bSize[], int m, int pSize[], int n) {
    int allocation[20];
    int temp[20];

    for (int i = 0; i < m; i++)
        temp[i] = bSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (temp[j] >= pSize[i]) {
                if (bestIdx == -1 || temp[j] < temp[bestIdx])
                    bestIdx = j;
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            temp[bestIdx] -= pSize[i];
        }
    }

    printf("\n--- BEST FIT ---\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tB%d\n", i + 1, pSize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, pSize[i]);
    }
}

void worstFit(int bSize[], int m, int pSize[], int n) {
    int allocation[20];
    int temp[20];

    for (int i = 0; i < m; i++)
        temp[i] = bSize[i];

    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (temp[j] >= pSize[i]) {
                if (worstIdx == -1 || temp[j] > temp[worstIdx])
                    worstIdx = j;
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            temp[worstIdx] -= pSize[i];
        }
    }

    printf("\n--- WORST FIT ---\n");
    printf("Process\tSize\tBlock\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t%d\tB%d\n", i + 1, pSize[i], allocation[i] + 1);
        else
            printf("P%d\t%d\tNot Allocated\n", i + 1, pSize[i]);
    }
}

int main() {
    int bSize[20], pSize[20];
    int nb, np;

    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);

    printf("Enter size of each block:\n");
    for (int i = 0; i < nb; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &bSize[i]);
    }

    printf("\nEnter number of processes: ");
    scanf("%d", &np);

    printf("Enter size of each process:\n");
    for (int i = 0; i < np; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &pSize[i]);
    }

    firstFit(bSize, nb, pSize, np);
    bestFit(bSize, nb, pSize, np);
    worstFit(bSize, nb, pSize, np);

    return 0;
}

/*
Output: 

Enter number of memory blocks: 2
Enter size of each block:
Block 1: 150
Block 2: 350

Enter number of processes: 3
Enter size of each process:
Process 1: 30
Process 2: 87
Process 3: 67

--- FIRST FIT ---
Process Size    Block
P1      30      B1
P2      87      B1
P3      67      B2

--- BEST FIT ---
Process Size    Block
P1      30      B1
P2      87      B1
P3      67      B2

--- WORST FIT ---
Process Size    Block
P1      30      B2
P2      87      B2
P3      67      B2

*/