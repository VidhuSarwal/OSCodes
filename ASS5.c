#include <stdio.h>

int main()
{
    // Variable declarations
    int p[10], at[10], bt[10], ct[10], tat[10], wt[10], i, j, temp = 0, n;
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

    // Input: Arrival times for each process
    printf("Enter %d arrival times: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &at[i]);
    }

    // Input: Burst times for each process
    printf("Enter %d burst times: ", n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &bt[i]);
    }

    // Sorting processes by arrival time (at) using Bubble Sort
    // Ensures FCFS order
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < (n - i - 1); j++)
        {
            if (at[j] > at[j + 1])
            {
                // Swap process IDs
                temp = p[j + 1];
                p[j + 1] = p[j];
                p[j] = temp;

                // Swap arrival times
                temp = at[j + 1];
                at[j + 1] = at[j];
                at[j] = temp;

                // Swap burst times
                temp = bt[j + 1];
                bt[j + 1] = bt[j];
                bt[j] = temp;
            }
        }
    }

    // Calculating completion time (CT) for each process
    ct[0] = at[0] + bt[0]; // First process starts immediately upon arrival
    for (i = 1; i < n; i++)
    {
        temp = 0;
        if (ct[i - 1] < at[i])
        {
            // If the CPU is idle, adjust for the idle time
            temp = at[i] - ct[i - 1];
        }
        ct[i] = ct[i - 1] + bt[i] + temp; // Compute completion time for current process
    }

    // Display the results table headers
    printf("\np\tAT\tBT\tCT\tTAT\tWT");

    // Calculating Turnaround Time (TAT) and Waiting Time (WT)
    for (i = 0; i < n; i++)
    {
        tat[i] = ct[i] - at[i];  // Turnaround time: Completion time - Arrival time
        wt[i] = tat[i] - bt[i]; // Waiting time: Turnaround time - Burst time
        atat += tat[i];         // Accumulate turnaround time for average calculation
        awt += wt[i];           // Accumulate waiting time for average calculation
    }

    // Calculate averages
    atat /= n;
    awt /= n;

    // Displaying the results for each process
    for (i = 0; i < n; i++)
    {
        printf("\nP%d\t %d\t %d\t %d\t %d\t %d", p[i], at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    // Display average turnaround time and waiting time
    printf("\nAverage turnaround time: %f", atat);
    printf("\nAverage waiting time: %f", awt);

    return 0;
}
