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

void print_page_frame(int page, int frame[], int f_size) {
    printf("%d | ", page);
    for (int i = 0; i < f_size; i++) {
        if (frame[i] == -1) {
            printf("\n");
            return;
        }
        printf("%d ", frame[i]);
    }
    printf("\n");
}

int find_lru(int time[], int f_size) {
    int min = time[0];
    int pos = 0;

    for (int i = 0; i < f_size; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int do_lru(int pages[], int p_size, int f_size) {
    int frame[f_size];
    int time[f_size];
    int hit_count = 0;

    init_frame(frame, f_size);

    int counter = 0, l_idx = 0, lj, fj;

    for (int i = 0; i < p_size; i++) {
        fj = in_arr(frame, f_size, pages[i]);
        if (fj != -1) {
            printf("%d | Hit\n", pages[i]);
            hit_count++;
            time[fj] = counter;
            counter++;
            continue;
        }

        // check for free space
        fj = in_arr(frame, f_size, -1);
        if (fj != -1) {
            frame[fj] = pages[i];
            time[fj] = counter;
            counter++;
            print_page_frame(pages[i], frame, f_size);
            continue;
        }

        // frame is full
        int pos = find_lru(time, f_size);
        frame[pos] = pages[i];
        time[pos] = counter;
        print_page_frame(pages[i], frame, f_size);
        counter++;
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
    int h_count = do_lru(pages, n_pages, frame_size);
    printf("Total Fault Count = %d\n", n_pages - h_count);
}
