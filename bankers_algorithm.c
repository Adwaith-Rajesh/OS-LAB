// this is a simpler version of the bankers algorithm, with no prevention
// against deadlocks, if a deadlock happens then the code will go into a infinite loop

#include <stdio.h>
#include <stdlib.h>

void read_matrix(int mat[][3], int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &mat[i][j]);
        }
    }
}

void print_matrix(int mat[][3], int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void print_array(int arr[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void calc_need_matrix(int need[][3], int alloc[][3],
                      int max[][3], int row) {
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < 3; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int compare_mat(int arr1[], int arr2[], int len) {
    for (int i = 0; i < len; i++) {
        if (arr1[i] > arr2[i]) return 0;
    }
    return 1;
}

void add_arr(int arr1[], int arr2[], int n) {
    for (int i = 0; i < n; i++) {
        arr2[i] += arr1[i];
    }
}

void calc_seq(int alloc[][3], int need[][3],
              int finish[], int work[3], int n) {
    int fin_count = 0;
    int i = 0;
    while (fin_count != n) {
        if ((compare_mat(need[i], work, 3) == 1) && (finish[i] == 0)) {
            add_arr(alloc[i], work, 3);
            fin_count++;
            finish[i] = 1;
            printf("%d ", i);
        }
        i = (i + 1) % n;
    }
}

int main() {
    int n_process;
    printf("Enter the number of processes: ");
    scanf("%d", &n_process);

    int alloc_mat[n_process][3];
    int max_mat[n_process][3];
    int need_mat[n_process][3];
    int finish[n_process];
    int avail[3];

    for (int i = 0; i < n_process; i++) finish[i] = 0;

    printf("Enter the allocation matrix\n");
    read_matrix(alloc_mat, n_process);

    printf("Enter the max matrix\n");
    read_matrix(max_mat, n_process);

    printf("Enter the available processes: ");
    scanf("%d%d%d", &avail[0], &avail[1], &avail[2]);

    calc_need_matrix(need_mat, alloc_mat, max_mat, n_process);

    printf("\nNeed matrix: \n");
    print_matrix(need_mat, n_process);

    printf("Sequence: ");
    calc_seq(alloc_mat, need_mat, finish, avail, n_process);
    printf("\n");

    return 0;
}

/* OUTPUT

Enter the number of processes: 5
Enter the allocation matrix
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter the max matrix
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3
Enter the available processes: 3 3 2

Need matrix:
7 4 3
1 2 2
6 0 0
0 1 1
4 3 1
Sequence: 1 3 4 0 2

*/