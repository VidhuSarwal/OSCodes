#include<stdio.h>

int main() 

{
    // Variable declarations
    int p[10], bt[10], at[10], pri[10], wt[10], tat[10], n, i, j, temp;
    int st[10], ft[10]; // Start time and finish time for each process
    float awt = 0, atat = 0; // Average waiting time and turnaround time

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: Process IDs
    printf("Enter %d processes: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &p[i]);
    }

    // Input: Burst times for each process
    printf("Enter %d burst times: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    // Input: Arrival times for each process
    printf("Enter %d arrival times: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
    }

    // Input: Priority values for each process
    printf("Enter %d priority values: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &pri[i]);
    }

    // Sorting processes by priority (ascending order) using Bubble Sort
    // Lower priority value indicates higher priority
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (pri[j] > pri[j + 1]) // Compare priorities
            {
                // Swap arrival times
                temp = at[j + 1];
                at[j + 1] = at[j];
                at[j] = temp;

                // Swap priorities
                temp = pri[j + 1];
                pri[j + 1] = pri[j];
                pri[j] = temp;

                // Swap burst times
                temp = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = temp;

                // Swap process IDs
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculating start time, waiting time, finish time, and turnaround time
    for (i = 0; i < n; i++)
    {
        if (i == 0 || ft[i - 1] < at[i])
            st[i] = at[i]; // If CPU is idle, start at arrival time
        else
            st[i] = ft[i - 1]; // Otherwise, start after the last process finishes

        wt[i] = st[i] - at[i]; // Waiting time: Start time - Arrival time
        ft[i] = st[i] + bt[i]; // Finish time: Start time + Burst time
        tat[i] = ft[i] - at[i]; // Turnaround time: Finish time - Arrival time

        awt += wt[i]; // Accumulate waiting time for average calculation
        atat += tat[i]; // Accumulate turnaround time for average calculation
    }

    // Calculate averages
    awt /= n;
    atat /= n;

    // Display process details in tabular format
    printf("\nP\tAT\tBT\tWT\tTAT");
    for (i = 0; i < n; i++)
    {
        printf("\nP%d\t %d\t %d\t %d\t %d", p[i], at[i], bt[i], wt[i], tat[i]);
    }

    // Display average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %f", awt);
    printf("\nAverage Turn-Around Time: %f", atat);

    return 0;
}
