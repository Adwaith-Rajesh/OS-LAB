#include <stdio.h>
#include <stdlib.h>

#define MAX_Q_SIZE 100

void sort(int arr[], int len) {
    for (int i = 0; i < len - 1; i++) {
        for (int j = 0; j < len - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void do_fcfs(int q[], int n_q, int curr_head) {
    int total_dist = 0, curr_pos;
    printf("\n\ntraversed order: ");

    for (int i = 0; i < n_q; i++) {
        curr_pos = q[i];
        printf("%d ", curr_pos);
        total_dist += (curr_head > curr_pos) ? curr_head - curr_pos : curr_pos - curr_head;
        curr_head = curr_pos;
    }
    printf("\nTotal distance traversed: %d\n", total_dist);
}

// SCAN - scans towards the right first
void do_scan(int q[], int n_q, int curr_head, int n_tracks) {
    int new_q[n_q + 3];
    for (int i = 0; i < n_q + 3; i++) new_q[i] = q[i];
    new_q[n_q] = 0;
    new_q[n_q + 1] = n_tracks;
    new_q[n_q + 2] = curr_head;

    sort(new_q, n_q + 3);

    // find the pos of curr_head
    int curr_pos = 0;
    for (int i = 0; i < n_q + 3; i++) {
        if (new_q[i] == curr_head) {
            curr_pos = i;
            break;
        }
    }

    printf("\n\nTraversed order: ");

    // scan right
    for (int i = curr_pos; i < n_q + 3; i++) {
        printf("%d ", new_q[i]);
    }

    // scan left
    for (int i = curr_pos - 1; i >= 1; i--) {
        printf("%d ", new_q[i]);
    }

    printf("\nTotal Seek Time: ");
    printf("%d\n", ((n_tracks - curr_head) + (n_tracks - new_q[1])));
}

void do_cscan(int q[], int n_q, int curr_head, int n_tracks) {
    int nq_s = n_q + 3;
    int new_q[nq_s];
    for (int i = 0; i < nq_s; i++) new_q[i] = q[i];
    new_q[n_q] = 0;
    new_q[n_q + 1] = n_tracks;
    new_q[n_q + 2] = curr_head;

    sort(new_q, nq_s);

    // find the pos of curr_head
    int curr_pos = 0;
    for (int i = 0; i < nq_s; i++) {
        if (new_q[i] == curr_head) {
            curr_pos = i;
            break;
        }
    }

    printf("\n\nTraversed order: ");
    for (int i = curr_pos;; i = (i + 1) % nq_s) {
        printf("%d ", new_q[i]);
        if (i == curr_pos - 1) break;
    }

    printf("\nTotal Seek Time: ");
    printf("%d\n", ((n_tracks - curr_head) + n_tracks + new_q[curr_pos - 1]));
}

int main() {
    int q_size, curr_head, n_tracks;
    printf("Enter the total number of tracks: ");
    scanf("%d", &n_tracks);

    printf("Enter the size of the queue: ");
    scanf("%d", &q_size);

    int q[q_size];

    printf("Enter the current head position: ");
    scanf("%d", &curr_head);

    printf("Enter the queue: ");
    for (int i = 0; i < q_size; i++) {
        scanf("%d", &q[i]);
    }

    int opt;
    printf("Enter the scheduling algorithm: \n1.FCFS 2.SCAN 3.C-SCAN 4. Exit: ");
    scanf("%d", &opt);

    switch (opt) {
        case 1:
            do_fcfs(q, q_size, curr_head);
            break;
        case 2:
            do_scan(q, q_size, curr_head, n_tracks);
            break;
        case 3:
            do_cscan(q, q_size, curr_head, n_tracks);
        case 4:
        default:
            exit(0);
    }

    return 0;
}