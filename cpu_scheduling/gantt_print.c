#include <stdio.h>
#include <string.h>

typedef struct {
    char name[5];
    int st;  // start time
    int ct;  // completion time

} PDone;

void print_gantt_char(PDone d_p[], int n) {
    for (int i = 0; i < n; i++) printf("+-----%s", (i == n - 1) ? "+\n" : "");  // generates +--+--+--
    for (int i = 0; i <= n; i++) (i == n) ? printf("|\n") : printf("%s%-5s", "|", d_p[i].name);
    for (int i = 0; i < n; i++) printf("+-----%s", (i == n - 1) ? "+\n" : "");  // generates +--+--+--
    for (int i = 0; i <= n; i++) (i == n) ? printf("%-6d\n", d_p[n - 1].ct) : printf("%-6d", d_p[i].st);
}

int main() {
    PDone p_processes[20];
    int n = 5;

    strncpy(p_processes[0].name, "IDLE", 25);
    p_processes[0].st = 0;
    p_processes[0].ct = 3;

    strncpy(p_processes[1].name, "hello", 25);
    p_processes[1].st = 3;
    p_processes[1].ct = 11;

    strncpy(p_processes[2].name, "p", 25);
    p_processes[2].st = 11;
    p_processes[2].ct = 17;

    strncpy(p_processes[3].name, "p5", 25);
    p_processes[3].st = 17;
    p_processes[3].ct = 21;

    strncpy(p_processes[4].name, "p2", 25);
    p_processes[4].st = 21;
    p_processes[4].ct = 23;

    print_gantt_char(p_processes, n);

    return 0;
}
