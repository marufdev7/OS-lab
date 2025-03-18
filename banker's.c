#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, m;

    printf("Number of processes and resources: ");
    scanf("%d %d", &n, &m);

    int avail[m], max[n][m], alloc[n][m], need[n][m], safe[n];
    bool finish[n];

    printf("Enter available resources: ");
    for (int j = 0; j < m; j++)
    {
        scanf("%d", &avail[j]);
    }

    printf("Enter max demand matrix: ");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter allocation matrix: ");
    for (int i = 0; i < n; i++)
    {
        finish[i] = false;
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &alloc[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    int count = 0;
    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool can_allocate = true;
                for (int j = 0; j < m; j++)
                {
                    if (need[i][j] > avail[j])
                    {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate)
                {
                    for (int j = 0; j < m; j++)
                    {
                        avail[j] += alloc[i][j];
                    }
                    safe[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found)
        {
            printf("System is in an unsafe state!\n");
            return 0;
        }
    }

    printf("Safe sequence: ");
    for (int  i = 0; i < n; i++)
    {
        printf("P%d ", safe[i]);
    }
    printf("\n");

    return 0;
}

/*
Number of processes and resources: 5 3
Enter available resources: 3 3 2
Enter max demand matrix: 7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter allocation matrix: 0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Safe sequence: P1 P3 P4 P0 P2
*/

