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

typedef struct {
    char name[5];
    int st;  // start time
    int ct;  // completion time
} EProcess;  // executed process

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

void print_gantt_chart(EProcess d_p[], int n) {
    printf("\n| ----- Gantt Chart ----- |\n\n");
    for (int i = 0; i < n; i++) printf("+-----%s", (i == n - 1) ? "+\n" : "");
    for (int i = 0; i <= n; i++) (i == n) ? printf("|\n") : printf("%s%-5s", "|", d_p[i].name);
    for (int i = 0; i < n; i++) printf("+-----%s", (i == n - 1) ? "+\n" : "");
    for (int i = 0; i <= n; i++) (i == n) ? printf("%-6d\n", d_p[n - 1].ct) : printf("%-6d", d_p[i].st);
}

// fcfs calculations

void sort_processes(Process processes[], int n) {
    // sorts n processes based on the Process.at
    for (int i = 0; i < n - i; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j + 1].at < processes[j].at) {
                Process temp = processes[j + 1];
                processes[j + 1] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

int perform_fcfs(Process ps[], EProcess e_ps[], int n) {
    // return the total number of individual execution performed
    int idle = 0;
    int curr_eps = 0, clk = 0, curr_ps = 0;
    for (curr_eps = 0, clk = 0, curr_ps = 0; curr_ps < n;) {
        if (ps[curr_ps].at <= clk && ps[curr_ps].status == 0) {
            // check if the processor was idling before the current process
            // starts execution
            if (idle == 1) {
                e_ps[curr_eps++].ct = clk;
                idle = 0;
            }
            strncpy(e_ps[curr_eps].name, ps[curr_ps].name, 5);
            e_ps[curr_eps].st = clk;                   // start time = i
            e_ps[curr_eps].ct = clk + ps[curr_ps].bt;  // completion time = start time + burst time (fcfs)

            ps[curr_ps].wt = clk - ps[curr_ps].at;                // wait time = start time - arrival time
            ps[curr_ps].tt = e_ps[curr_eps].ct - ps[curr_ps].at;  // turn around time = completion time - arrival time
            ps[curr_ps].ct = e_ps[curr_eps].ct;

            clk = e_ps[curr_eps++].ct;
            ps[curr_ps++].status = 1;  // process has completely executed
            continue;
        }

        // no process to execute, check for idle
        // if not starts idling
        if (idle == 0) {
            strncpy(e_ps[curr_eps].name, "Idle", 5);
            e_ps[curr_eps].st = clk;
            clk++;
            idle = 1;
            continue;
        }
        clk++;
    }
    return curr_eps;
}

int main() {
    Process processes[20];
    EProcess e_processes[20];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    read_n_process(processes, n);
    // print_n_processes(processes, n);
    sort_processes(processes, n);

    int num = perform_fcfs(processes, e_processes, n);
    print_n_processes(processes, n);
    print_gantt_chart(e_processes, num);
    return 0;
}

/* OUTPUT

Enter the number of processes: 5
Enter the details of the processes


Enter the details of processes 1
Name: p1
Arrival Time: 3
Burst Time: 4

Enter the details of processes 2
Name: p2
Arrival Time: 5
Burst Time: 3

Enter the details of processes 3
Name: p3
Arrival Time: 0
Burst Time: 2

Enter the details of processes 4
Name: p4
Arrival Time: 5
Burst Time: 1

Enter the details of processes 5
Name: p5
Arrival Time: 4
Burst Time: 3

| ----- Table ----- |

Name            Arrival Time    Burst Time      Completion Time Waiting Time    Turn around Time
p3              0               2               2               0               2
p1              3               4               7               0               4
p5              4               3               10              3               6
p2              5               3               13              5               8
p4              5               1               14              8               9
------------------------------------------------------------------------------------------------
                                                     Average    3.20            5.80

| ----- Gantt Chart ----- |

+-----+-----+-----+-----+-----+-----+
|p3   |Idle |p1   |p5   |p2   |p4   |
+-----+-----+-----+-----+-----+-----+
0     2     3     7     10    13    14

*/
