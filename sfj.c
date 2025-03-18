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
        int s_idx = -1;
        int s_bt = 99999;
        
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= time && p[i].bt < s_bt) {
                s_bt = p[i].bt;
                s_idx = i;
            }
        }
        
        if (s_idx == -1) {
            time++;
            continue;
        }
        
        p[s_idx].ct = time + p[s_idx].bt;
        p[s_idx].tat = p[s_idx].ct - p[s_idx].at;
        p[s_idx].wt = p[s_idx].tat - p[s_idx].bt;
        p[s_idx].completed = true;
        
        total_tat += p[s_idx].tat;
        total_wt += p[s_idx].wt;
        
        time = p[s_idx].ct;
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
P2    2     5     10    8      3
P3    3     6     16    13     7
P4    4     7     23    19     12

Avg TAT: 11.00
Avg WT: 5.50
*/
