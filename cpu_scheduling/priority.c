// non pre-emptive Priority

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
    int pr;      // priority, lower the value higher the priority
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

        printf("Priority: ");
        scanf("%d", &processes[i].pr);

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
    // returns -> the index of the next process (next smallest Process.pr)
    //          -1 if a process could not be found

    int min = 0, found = 0;
    for (int i = 0; i < n; i++) {
        if (ps[i].at <= clk && ps[i].status == 0) {
            if (found == 0) {
                min = i;
                found = 1;
            }

            if (found == 1 && ps[i].pr < ps[min].pr) {
                min = i;
            }
        }
    }

    return (found == 1) ? min : -1;
}

int perform_sjf(Process ps[], int n) {
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

            ps[idx].status = 1;  // (NPP, executes a process completely)
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
    int num = perform_sjf(processes, n);

    print_n_processes(processes, n);
    return 0;
}

/* OUTPUT

Enter the number of processes: 5
Enter the details of the processes


Enter the details of processes 1
Name: p1
Arrival Time: 0
Burst Time: 8
Priority: 1

Enter the details of processes 2
Name: p2
Arrival Time: 2
Burst Time: 9
Priority: 2

Enter the details of processes 3
Name: p3
Arrival Time: 4
Burst Time: 1
Priority: 3

Enter the details of processes 4
Name: p4
Arrival Time: 6
Burst Time: 6
Priority: 4

Enter the details of processes 5
Name: p5
Arrival Time: 8
Burst Time: 3
Priority: 5

| ----- Table ----- |

Name            Arrival Time    Burst Time      Completion Time Waiting Time    Turn around Time
p1              0               8               8               0               8
p2              2               9               17              6               15
p3              4               1               18              13              14
p4              6               6               24              12              18
p5              8               3               27              16              19
------------------------------------------------------------------------------------------------
                                                     Average    9.40           14.80
*/
