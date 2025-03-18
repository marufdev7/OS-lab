#include <stdio.h>
#include <stdbool.h>

struct Process {
     int pid, at, bt, pri, ct, tat, wt;
     bool comp;
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
          printf("Enter Arrival Time, Burst Time, and Priority for P%d: ", p[i].pid);
          scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
          p[i].comp = false;
     }

     int time = 0, done = 0;
     float total_tat = 0, total_wt = 0;

     while (done < n)
     {
          int hp_idx = -1;
          int hp = 99999;

          for (int i = 0; i < n; i++)
          {
               if (!p[i].comp && p[i].at <= time && p[i].pri < hp)
               {
                    hp = p[i].pri;
                    hp_idx = i;
               }
          }

          if (hp_idx == -1)
          {
               time++;
               continue;
          }

          p[hp_idx].ct = time + p[hp_idx].bt;
          p[hp_idx].tat = p[hp_idx].ct - p[hp_idx].at;
          p[hp_idx].wt = p[hp_idx].tat - p[hp_idx].bt;
          p[hp_idx].comp = true;

          total_tat += p[hp_idx].tat;
          total_wt += p[hp_idx].wt;

          time = p[hp_idx].ct;
          done++;
     }

     printf("\nProcess Table:\n");
     printf("ID\tAT\tBT\tPRI\tCT\tTAT\tWT\n");
     for (int i = 0; i < n; i++)
     {
          printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
     }

     printf("\nAverage Turnaround Time: %.2f", total_tat / n);
     printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

     return 0;
}

/*
Sample Input:
Enter number of processes: 3
P1 Arrival Time, Burst Time, Priority: 2 5 3
P2 Arrival Time, Burst Time, Priority: 5 9 2
P3 Arrival Time, Burst Time, Priority: 1 7 1

Expected Output:
ID    AT    BT    PRI    CT    TAT    WT
P3    1     7     1      8     7      0
P1    2     5     3     22     20     15
P2    5     9     2     17     12     3

Avg TAT: 13.00
Avg WT: 6.00
*/
