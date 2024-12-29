#include <stdio.h>
#include <stdlib.h>

struct Process {
    int Bt;
    int tBt;
    int TAt;
    int wt;
    int arrivalTime;
    int RT;
};

// Function to get a valid non-negative integer input
int getNonNegativeInteger(const char* prompt) {
    int number;
    char input[100];

    while (1) {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: Invalid input. Please try again.\n");
            continue;
        }
        char* endptr;
        number = strtol(input, &endptr, 10);
        if (*endptr != '\n' && *endptr != '\0') {
            printf("Error: Invalid input. Please enter a valid number: ");
        }
        else if (number < 0) {
            printf("Error: Please enter a non-negative integer: ");
        }
        else {
            break;
        }
    }

    return number;
}

int main() {
    int i, n, qt;
    int x, y;  // x: current time, y: number of completed processes
    float totalWT = 0, totalTAT = 0, totalRT = 0;

    struct Process P[100];
    n = getNonNegativeInteger("Enter the Number of Processes: ");

    for (i = 0; i < n; i++) {
        printf("Enter burst time for P-%d: ", i + 1);
        P[i].Bt = getNonNegativeInteger("");
        printf("Enter arrival time for P-%d: ", i + 1);
        P[i].arrivalTime = getNonNegativeInteger("");

        P[i].tBt = P[i].Bt;
        P[i].RT = -1; // t5ly el time = -1 3lashan lsa m4t8la4
    }
    qt = getNonNegativeInteger("Enter the time quantum: ");
    x = 0;
    y = 0;
    i = 0;
    while (1) {
        if (P[i].Bt > 0 && x >= P[i].arrivalTime) {
            if (P[i].RT == -1) {
                P[i].RT = x - P[i].arrivalTime;
            }

            if (P[i].Bt > qt) {
                x += qt;
                P[i].Bt -= qt;
            }
            else {
                x += P[i].Bt;
                P[i].TAt = x - P[i].arrivalTime;
                P[i].wt = P[i].TAt - P[i].tBt;
                y++;
                P[i].Bt = 0;
            }
        }
        if (i == n - 1) {
            i = 0;
        }
        else {
            i++;
        }

        if (y == n) {
            break;
        }
    }
    for (i = 0; i < n; i++) {
        totalWT += P[i].wt;
        totalTAT += P[i].TAt;
        totalRT += P[i].RT;
    }

    // Display results
    printf(" PROCESS\tARRIVAL TIME\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\tRESPONSE TIME\n");
    printf("--------------------------------------------------------------------------------------------\n");
    for (i = 0; i < n; i++) {
        printf("P-%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            i + 1, P[i].arrivalTime, P[i].tBt, P[i].wt, P[i].TAt, P[i].RT);
    }

    // Display averages
    printf("\nAverage Waiting Time: %.2f\n", totalWT / n);
    printf("Average Turnaround Time: %.2f\n", totalTAT / n);
    printf("Average Response Time: %.2f\n", totalRT / n);

    return 0;
}