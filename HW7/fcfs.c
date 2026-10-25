
#include <stdio.h>

int main() {
    int n;
    int arrival[100], burst[100];
    int waiting[100], turnaround[100], response[100];
    int pid[100];
    int start[100], finish[100];

    int current = 0;
    float total_wait = 0, total_turn = 0, total_response = 0;

    printf("Number of processes: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of processes\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        pid[i] = i + 1;

        printf("Arrival and burst time for P%d: ", pid[i]);
        scanf("%d %d", &arrival[i], &burst[i]);

        if (arrival[i] < 0 || burst[i] <= 0) {
            printf("Invalid process times\n");
            return 1;
        }
    }

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arrival[i] > arrival[j]) {
                int temp;

                temp = arrival[i];
                arrival[i] = arrival[j];
                arrival[j] = temp;

                temp = burst[i];
                burst[i] = burst[j];
                burst[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (current < arrival[i]) {
            current = arrival[i];
        }

        start[i] = current;
        finish[i] = start[i] + burst[i];

        waiting[i] = start[i] - arrival[i];
        turnaround[i] = finish[i] - arrival[i];
        response[i] = waiting[i];

        current = finish[i];

        total_wait += waiting[i];
        total_turn += turnaround[i];
        total_response += response[i];
    }

    printf("\nFCFS Scheduling\n");
    printf("\nGantt Chart:\n");

    current = 0;

    for (int i = 0; i < n; i++) {
        if (current < start[i]) {
            printf("| Idle (%d-%d) ", current, start[i]);
        }

        printf("| P%d (%d-%d) ", pid[i], start[i], finish[i]);
        current = finish[i];
    }

    printf("|\n");

    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               pid[i], arrival[i], burst[i],
               waiting[i], turnaround[i], response[i]);
    }

    printf("\nAverage Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turn / n);
    printf("Average Response Time: %.2f\n", total_response / n);

    return 0;
}

