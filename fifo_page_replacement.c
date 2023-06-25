#include <stdio.h>
#include <stdlib.h>

int in_arr(int arr[], int len, int n) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == n) return i;
    }
    return -1;
}

void init_frame(int frame[], int frame_size) {
    for (int i = 0; i < frame_size; i++) frame[i] = -1;
}

int do_fcfs(int pages[], int p_size, int f_size) {
    int hit_count = 0;
    int f_idx = -1;
    int frame[f_size];
    init_frame(frame, f_size);

    for (int i = 0; i < p_size; i++) {
        printf("%d | ", pages[i]);

        if (in_arr(frame, f_size, pages[i]) != -1) {
            printf("Hit\n");
            hit_count++;
            continue;
        }
        int fj = in_arr(frame, f_size, -1);
        if (fj != -1) {
            frame[fj] = pages[i];
        } else {
            f_idx = (f_idx + 1) % f_size;
            frame[f_idx] = pages[i];
        }

        for (int k = 0; k < f_size; k++) {
            if (frame[k] == -1) break;
            printf("%d ", frame[k]);
        }
        printf("\n");
    }
    return hit_count;
}

int main() {
    int n_pages, frame_size;
    printf("Enter the number queue size: ");
    scanf("%d", &n_pages);

    int pages[n_pages];

    printf("Enter the page size: ");
    scanf("%d", &frame_size);

    printf("Enter the pages to allocate: ");
    for (int i = 0; i < n_pages; i++) {
        scanf("%d", &pages[i]);
    }
    int h_count = do_fcfs(pages, n_pages, frame_size);
    printf("Total Fault Count = %d\n", n_pages - h_count);
}
