
#include <stdio.h>

struct Process {
    int pid;
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int response_time;
    int finished;
};

void sjf(struct Process p[], int n) {
    int clock = 0;
    int done = 0;
    int sequence[100];
    int start[100];
    int end[100];

    float total_wait = 0;
    float total_turn = 0;
    float total_response = 0;

    while (done < n) {
        int chosen = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].finished == 0 &&
                p[i].arrival_time <= clock) {

                if (chosen == -1 ||
                    p[i].burst_time < p[chosen].burst_time ||
                    (p[i].burst_time == p[chosen].burst_time &&
                     p[i].arrival_time < p[chosen].arrival_time)) {
                    chosen = i;
                }
            }
        }

        if (chosen == -1) {
            int next = -1;

            for (int i = 0; i < n; i++) {
                if (p[i].finished == 0) {
                    if (next == -1 ||
                        p[i].arrival_time < next) {
                        next = p[i].arrival_time;
                    }
                }
            }

            clock = next;
            continue;
        }

        sequence[done] = chosen;
        start[done] = clock;

        p[chosen].waiting_time =
            clock - p[chosen].arrival_time;

        p[chosen].response_time =
            p[chosen].waiting_time;

        clock += p[chosen].burst_time;
        end[done] = clock;

        p[chosen].turnaround_time =
            clock - p[chosen].arrival_time;

        total_wait += p[chosen].waiting_time;
        total_turn += p[chosen].turnaround_time;
        total_response += p[chosen].response_time;

        p[chosen].finished = 1;
        done++;
    }

    printf("\n=== Shortest Job First (SJF) ===\n");
    printf("Gantt Chart: ");

    int previous = 0;

    for (int i = 0; i < n; i++) {
        if (previous < start[i]) {
            printf("| Idle (%d-%d) ", previous, start[i]);
        }

        printf("| P%d (%d-%d) ",
               p[sequence[i]].pid, start[i], end[i]);

        previous = end[i];
    }

    printf("|\n");
    printf("PID\tAT\tBT\tWT\tTAT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].arrival_time,
               p[i].burst_time, p[i].waiting_time,
               p[i].turnaround_time, p[i].response_time);
    }

    printf("Average Waiting Time: %.2f\n", total_wait / n);
    printf("Average Turnaround Time: %.2f\n", total_turn / n);
    printf("Average Response Time: %.2f\n", total_response / n);
}

int main() {
    struct Process p[100];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    if (n < 1 || n > 100) {
        printf("Invalid number of processes\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        p[i].finished = 0;

        printf("Enter the arrival time and burst time for process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival_time, &p[i].burst_time);

        if (p[i].arrival_time < 0 || p[i].burst_time <= 0) {
            printf("Invalid process times\n");
            return 1;
        }
    }

    sjf(p, n);

    return 0;
}

