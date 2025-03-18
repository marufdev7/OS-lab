#include <stdio.h>
#include <stdbool.h>

struct Process {
 int pid, at, bt, rt, ct, tat, wt; 
};

int main() {
    int n, q;
    
    printf("Enter the number of processes and time quantum: ");
    scanf("%d %d", &n, &q);
    
    struct Process p[n];
    
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ", p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
    }
    
    int time = 0, completed = 0;
    float total_tat = 0, total_wt = 0;
    bool executed;
    
    while (completed < n) {
        executed = false;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                executed = true;
                int exec_time = (p[i].rt > q) ? q : p[i].rt;
                time += exec_time;
                p[i].rt -= exec_time;
                
                if (p[i].rt == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct - p[i].at;
                    p[i].wt = p[i].tat - p[i].bt;
                    total_tat += p[i].tat;
                    total_wt += p[i].wt;
                    completed++;
                }
            }
        }
        if (!executed) {
            time++;
        }
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
Enter number of processes and time quantum: 3 2
P1 Arrival & Burst Time: 0 4
P2 Arrival & Burst Time: 1 3
P3 Arrival & Burst Time: 2 2

Expected Output:
ID    AT    BT    CT    TAT    WT
P1    0     4     8     8      4
P2    1     3     9     8      5
P3    2     2     6     4      2

Avg TAT: 6.67
Avg WT: 3.67
*/
