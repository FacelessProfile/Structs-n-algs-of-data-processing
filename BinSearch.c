#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void FillInc(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

int binarySearchMK1(int n, int a[n], int target, int *pointer) {
    int L = 0, R = n - 1, mid;
    int comparisons = 0;
    while (L <= R) {
        comparisons++;
        mid = L + (R - L) / 2;
        if (a[mid] == target) {
            *pointer = comparisons;
            return mid;
        }
        comparisons++;
        if (a[mid] < target) {
            L = mid + 1;
        } else {
            R = mid - 1;
        }
    }
    *pointer = comparisons;
    return -1;
}

int binarySearchMK2(int n, int a[n], int target, int *pointer) {
    int L = 0, R = n - 1, mid;
    int comparisons = 0;
    while (L < R) {
        mid = L + (R - L) / 2;
        comparisons++;
        if (a[mid] < target) {
            L = mid + 1;
        } else {
            R = mid;
        }
    }
    comparisons++;
    if (a[R] == target) {
        *pointer = comparisons;
        return R;
    } else {
        *pointer = comparisons;
        return -1;
    }
}

int main(){
    printf("%-10s %-20s %-20s\n", "N", "CompFactMkI", "CompFactMkII");
    
    for (int n = 100; n <= 1000; n += 100) {
        int *A = malloc(n * sizeof(int));
        
        FillInc(n, A);
        int comp1 = 0, comp2 = 0;
        srand(time(NULL));
        int target = rand() % n;
        binarySearchMK1(n, A, target, &comp1);
        binarySearchMK2(n, A, target, &comp2);
        printf("%-10d %-20d %-20d\n", n, comp1, comp2);
        free(A);
    }
    return 0;
}
