#include <stdio.h>
#include <stdbool.h>


struct Process {
    int pid, at, bt, ct, tat, wt; 
    bool completed;
};

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = false;
    }

    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;

    while (completed < n) {
        int ljf_idx = -1;
        int max_bt = -1;

        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].bt > max_bt) {
                max_bt = p[i].bt;
                ljf_idx = i;
            }
        }

        if (ljf_idx == -1) {
            time++;
            continue;
        }

        p[ljf_idx].ct = time + p[ljf_idx].bt;
        p[ljf_idx].tat = p[ljf_idx].ct - p[ljf_idx].at;
        p[ljf_idx].wt = p[ljf_idx].tat - p[ljf_idx].bt;
        p[ljf_idx].completed = true;

        total_tat += p[ljf_idx].tat;
        total_wt += p[ljf_idx].wt;

        time = p[ljf_idx].ct;
        completed++;
    }

    printf("\nProcess Table:\n");
    printf("ID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time: %.2f", total_tat / n);
    printf("\nAverage Waiting Time: %.2f\n", total_wt / n);

    return 0;
}

/*
Sample Input:
Enter number of processes: 4
P1 Arrival & Burst Time: 1 4
P2 Arrival & Burst Time: 2 5
P3 Arrival & Burst Time: 3 6
P4 Arrival & Burst Time: 4 7

Expected Output:
ID    AT    BT    CT    TAT    WT
P1    1     4     5     4      0
P2    2     5     23    21     16
P3    3     6     18    15     9
P4    4     7     12    8      1

Avg TAT: 12.00
Avg WT: 6.50
*/
