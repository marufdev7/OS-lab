#include <stdio.h>

struct Process{
     int pid, at, bt, ct, tat, wt;  
};
int main()
{
     int n;
     printf("Enter the number of processes: ");
     scanf("%d", &n);

     struct Process p[n];
     for (int i = 0; i < n; i++)
     {
          p[i].pid = i + 1;
          printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
          scanf("%d %d", &p[i].at, &p[i].bt);
     }

     for (int i = 0; i < n - 1; i++)
     {
          for (int j = 0; j < n - i - 1; j++)
          {
               if (p[j].at > p[j + 1].at)
               {
                    struct Process temp = p[j];
                    p[j] = p[j + 1];
                    p[j + 1] = temp;
               }
          }
     }

     int time = 0; 
     float total_tat = 0, total_wt = 0;

     for (int i = 0; i < n; i++)
     {
          if (time < p[i].at)
          {
               time = p[i].at;
          }

          p[i].ct = time + p[i].bt;
          p[i].tat = p[i].ct - p[i].at;
          p[i].wt = p[i].tat - p[i].bt;

          total_tat += p[i].tat;
          total_wt += p[i].wt;

          time = p[i].ct;
     }

     printf("\nProcess Table:\n");
     printf("ID\tAT\tBT\tCT\tTAT\tWT\n");
     for (int i = 0; i < n; i++)
     {
          printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
     }

     printf("\nAverage Turnaround Time: %.2f", total_tat / n);
     printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

     return 0;
}

/*
Sample Input:
Enter number of processes: 4
P1 Arrival & Burst Time: 1 3
P2 Arrival & Burst Time: 2 4
P3 Arrival & Burst Time: 3 5
P4 Arrival & Burst Time: 4 6

Expected Output:
ID    AT    BT    CT    TAT    WT
P1    1     3     4     3      0
P2    2     4     8     6      2
P3    3     5     13    10     5
P4    4     6     19    15     9

Avg TAT: 8.50
Avg WT: 4.00
*/
