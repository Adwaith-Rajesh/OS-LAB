// non pre-emptive SJF
// explanation for calculating the wait times and other properties are in `fcfs.c`

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[5];
    int at;      // arrival time
    int bt;      // burst time
    int wt;      // waiting time
    int tt;      // turn around time
    int ct;      // completion time
    int status;  // status (checks execution completion)
} Process;

void read_n_process(Process processes[], int n) {
    printf("Enter the details of the processes\n\n");
    for (int i = 0; i < n; i++) {
        printf("\nEnter the details of processes %d\n", i + 1);
        printf("Name: ");
        scanf("%5s", processes[i].name);

        printf("Arrival Time: ");
        scanf("%d", &processes[i].at);

        printf("Burst Time: ");
        scanf("%d", &processes[i].bt);

        processes[i].status = 0;
    }
}

void print_n_processes(Process ps[], int n) {
    printf("\n| ----- Table ----- |\n\n");
    printf("%-16s%-16s%-16s%-16s%-16s%-16s\n",
           "Name", "Arrival Time", "Burst Time", "Completion Time", "Waiting Time", "Turn around Time");
    for (int i = 0; i < n; i++) {
        printf("%-16s%-16d%-16d%-16d%-16d%-16d\n",
               ps[i].name, ps[i].at, ps[i].bt, ps[i].ct, ps[i].wt, ps[i].tt);
    }
    for (int i = 0; i < 96; i++) printf("-");

    // calculate avg wt, tt
    float avg_tt = 0.0, avg_wt = 0.0;
    for (int i = 0; i < n; i++) {
        avg_tt += ps[i].tt;
        avg_wt += ps[i].wt;
    }
    avg_tt /= (float)n;
    avg_wt /= (float)n;

    printf("\n%60s%8.2f%16.2f\n", "Average", avg_wt, avg_tt);
}

// sjf calculations

int get_next_process_idx(Process ps[], int clk, int n) {
    // clk -> current clock value
    // n -> the number of processes
    // returns -> the index of the next process (next smallest Process.bt)
    //          -1 if a process could not be found

    int min = 0, found = 0;
    for (int i = 0; i < n; i++) {
        if (ps[i].at <= clk && ps[i].status == 0) {
            if (found == 0) {
                min = i;
                found = 1;
            }

            if (found == 1 && ps[i].bt < ps[min].bt) {
                min = i;
            }
        }
    }

    return (found == 1) ? min : -1;
}

int perform_sjf_np(Process ps[], int n) {
    int idle = 0, clk, curr_eps, curr_ps;
    for (clk = 0, curr_ps = 0, curr_eps = 0; curr_ps < n;) {
        int idx = get_next_process_idx(ps, clk, n);

        // check for idling
        if (idx == -1 && idle == 0) {
            idle = 1;  // start idling
            clk++;
            continue;
        }

        // a process exists
        if (idx != -1) {
            // stop idling, if we were doing so
            if (idle == 1) {
                idle = 0;
            }

            ps[idx].status = 1;  // (SJF-NP, executes a process completely)
            ps[idx].ct = clk + ps[idx].bt;

            ps[idx].tt = ps[idx].ct - ps[idx].at;
            ps[idx].wt = clk - ps[idx].at;

            clk = ps[idx].ct;
            curr_ps++;
            continue;
        }
        clk++;
    }
    return curr_eps;
}

int main() {
    Process processes[20];
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    read_n_process(processes, n);
    int num = perform_sjf_np(processes, n);

    print_n_processes(processes, n);
    return 0;
}

/* OUTPUT

Enter the number of processes: 5
Enter the details of the processes


Enter the details of processes 1
Name: p1
Arrival Time: 1
Burst Time: 7

Enter the details of processes 2
Name: p2
Arrival Time: 3
Burst Time: 3

Enter the details of processes 3
Name: p3
Arrival Time: 6
Burst Time: 2

Enter the details of processes 4
Name: p4
Arrival Time: 7
Burst Time: 10

Enter the details of processes 5
Name: p5
Arrival Time: 9
Burst Time: 8

| ----- Table ----- |

Name            Arrival Time    Burst Time      Completion Time Waiting Time    Turn around Time
p1              1               7               8               0               7
p2              3               3               13              7               10
p3              6               2               10              2               4
p4              7               10              31              14              24
p5              9               8               21              4               12
------------------------------------------------------------------------------------------------
                                                     Average    5.40           11.40

| ----- Gantt Chart ----- |

+-----+-----+-----+-----+-----+-----+
|Idle |p1   |p3   |p2   |p5   |p4   |
+-----+-----+-----+-----+-----+-----+
0     1     8     10    13    21    31

*/