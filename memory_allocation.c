#include <stdio.h>

// Function to allocate memory using Worst Fit, Best Fit, and First Fit
void allocateMemory(int algo, int blocks[], int m, int processes[], int n)
{
    int alloc[n]; // Stores block assigned to each process
    for (int i = 0; i < n; i++) alloc[i] = -1;

    for (int i = 0; i < n; i++)
    {
        int bestIdx = -1;
        for (int j = 0; j < m; j++)
        {
            if (blocks[j] >= processes[i])
            {
                if (algo == 0 && (bestIdx == -1 || blocks[j] > blocks[bestIdx])) // Worst Fit
                    bestIdx = j;
                else if (algo == 1 && (bestIdx == -1 || blocks[j] < blocks[bestIdx])) // Best Fit
                    bestIdx = j;
                else if (algo == 2 && bestIdx == -1) // First Fit
                    bestIdx = j;
            }
        }
        if (bestIdx != -1)
        {
            alloc[i] = bestIdx;
            blocks[bestIdx] -= processes[i];
        }
    }

    // Print results
    printf("%s Fit:\n", (algo == 0) ? "Worst" : (algo == 1) ? "Best" : "First");
    for (int i = 0; i < n; i++)
    {
        printf("P%d -> ", i + 1);
        if (alloc[i] != -1) printf("B%d\n", alloc[i] + 1);
        else printf("Not Allocated\n");
    }
    printf("\n");
}

int main()
{
    int m, n;
    printf("Number of blocks and processes: ");
    scanf("%d %d", &m, &n);

    int blocks[m], orig_blocks[m], processes[n];

    printf("Enter block sizes: ");
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &blocks[i]);
        orig_blocks[i] = blocks[i];
    }

    printf("Enter process sizes: ");
    for (int i = 0; i < n; i++) scanf("%d", &processes[i]);

    for (int algo = 0; algo < 3; algo++)
    {
        for (int i = 0; i < m; i++) blocks[i] = orig_blocks[i]; // Reset block sizes
        allocateMemory(algo, blocks, m, processes, n);
    }

    return 0;
}

/*
Sample Input:
Number of blocks and processes: 4 2
Block sizes: 100 50 300 20
Process sizes: 75 125

Expected Output:
Worst Fit:
P1 -> B3
P2 -> B3

Best Fit:
P1 -> B1
P2 -> B3

First Fit:
P1 -> B1
P2 -> B3
*/

