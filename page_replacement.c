#include <stdio.h>

int main()
{
    int frames, n;
    printf("Number of frames and pages: ");
    scanf("%d %d", &frames, &n);

    int pages[n], frame[frames], faults = 0, pos = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;

    printf("Enter page sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    // FIFO Page Replacement
    faults = 0;
    pos = 0;
    for (int i = 0; i < n; i++)
    {
        int hit = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }
        if (!hit)
        {
            frame[pos] = pages[i];
            pos = (pos + 1) % frames;
            faults++;
        }
    }
    printf("FIFO: Page Faults = %d\n", faults);

    // LRU Page Replacement
    faults = 0;
    int time[frames], least_recent;
    for (int i = 0; i < frames; i++) frame[i] = -1, time[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int hit = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                hit = 1;
                time[j] = i;
                break;
            }
        }
        if (!hit)
        {
            least_recent = 0;
            for (int j = 1; j < frames; j++)
                if (time[j] < time[least_recent]) least_recent = j;
            frame[least_recent] = pages[i];
            time[least_recent] = i;
            faults++;
        }
    }
    printf("LRU: Page Faults = %d\n", faults);

    // Optimal Page Replacement
    faults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    for (int i = 0; i < n; i++)
    {
        int hit = 0;
        for (int j = 0; j < frames; j++)
        {
            if (frame[j] == pages[i])
            {
                hit = 1;
                break;
            }
        }
        if (!hit)
        {
            int farthest = -1, replace = -1;
            for (int j = 0; j < frames; j++)
            {
                int next_use = n;
                for (int k = i + 1; k < n; k++)
                    if (pages[k] == frame[j])
                    {
                        next_use = k;
                        break;
                    }
                if (next_use > farthest)
                {
                    farthest = next_use;
                    replace = j;
                }
            }
            frame[replace] = pages[i];
            faults++;
        }
    }
    printf("Optimal: Page Faults = %d\n", faults);

    return 0;
}

/*
Sample Input:
Number of frames and pages: 3 7
Page sequence: 1 2 3 4 1 2 5

Expected Output:
FIFO: Page Faults = 7
LRU: Page Faults = 7
Optimal: Page Faults = 5
*/

