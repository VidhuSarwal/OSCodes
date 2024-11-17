#include <stdio.h>
#include <stdbool.h>

#define P 3 // Number of processes
#define R 4 // Number of resources

// Function to check if the current state is safe
bool isSafeState(int available[], int max[P][R], int allocation[P][R], int need[P][R]) {
    int work[R]; // Work array represents available resources
    bool finish[P] = {false}; // Tracks if a process is finished
    int safeSequence[P]; // Stores the safe sequence
    int count = 0; // Number of processes in the safe sequence

    // Initialize work as available
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    // Find processes that can finish
    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) { // If process is not finished
                bool canFinish = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) { // If resources needed are not available
                        canFinish = false;
                        break;
                    }
                }

                if (canFinish) { // If process can finish
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[i][k]; // Release resources
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) { // If no process can proceed
            printf("\nSystem is not in a safe state.\n");
            return false;
        }
    }

    // If all processes can finish, print the safe sequence
    printf("\nSystem is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    // Example data for demonstration
    int allocation[P][R] = {
        {1, 0, 0, 1}, // Resources allocated to P0
        {0, 1, 0, 0}, // Resources allocated to P1
        {1, 2, 2, 0}  // Resources allocated to P2
    };

    int max[P][R] = {
        {2, 1, 3, 2}, // Maximum resources P0 may need
        {1, 3, 2, 2}, // Maximum resources P1 may need
        {1, 3, 5, 0}  // Maximum resources P2 may need
    };

    int available[R] = {2, 2, 2, 1}; // Available resources in the system

    // Calculate the Need matrix
    int need[P][R];
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Print allocation, max, need, and available resources
    printf("Allocation Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", allocation[i][j]);
        }
        printf("\n");
    }

    printf("\nMax Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", max[i][j]);
        }
        printf("\n");
    }

    printf("\nNeed Matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    printf("\nAvailable Resources:\n");
    for (int i = 0; i < R; i++) {
        printf("%d ", available[i]);
    }
    printf("\n");

    // Check safe state for initial configuration
    isSafeState(available, max, allocation, need);

    // Simulate a resource request that leads to unsafe state
    int request[R] = {1, 0, 1, 0}; // Request for resources by process P0
    int process = 0; // Process making the request

    printf("\nSimulating resource request by P%d: ", process);
    for (int i = 0; i < R; i++) {
        printf("%d ", request[i]);
    }
    printf("\n");

    // Check if request can be granted
    bool canGrant = true;
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i] || request[i] > available[i]) {
            canGrant = false;
            break;
        }
    }

    if (canGrant) {
        // Grant request temporarily
        for (int i = 0; i < R; i++) {
            available[i] -= request[i];
            allocation[process][i] += request[i];
            need[process][i] -= request[i];
        }

        // Check if the new state is safe
        if (!isSafeState(available, max, allocation, need)) {
            printf("Request cannot be granted as it leads to an unsafe state.\n");
        } else {
            printf("Request granted.\n");
        }
    } else {
        printf("Request exceeds need or available resources. Cannot be granted.\n");
    }

    return 0;
}
