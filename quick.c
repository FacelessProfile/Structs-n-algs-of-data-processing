#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

int n = 10;

int countTheory(int n) {
    int C = ((n * n) + 5 * n + 4) / 2;
    int M = 3 * (n - 1);
    return C + M;
}

void FillInc(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void FillDec(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        A[i] = n - i;
    }
}

void FillRand(int n, int A[n]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n;
    }
}

int CheckSum(int n, int A[n]) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += A[i];
    }
    return sum;
}

int RunNumber(int n, int A[n]) {
    int series = 1;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            series++;
        }
    }
    return series;
}

void print(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int comparisons = 0;
int moves = 0;

// Worst-case pivot selection: always choose the leftmost element
void quickSort(int A[], int L, int R) {
    if (L >= R) return;

    int i = L, j = R;
    int x = A[L]; // Worst-case: always pick leftmost element

    while (i <= j) {
        while (A[i] < x) {
            i++;
            comparisons++;
        }
	comparisons++;
        while (A[j] > x) {
            j--;
            comparisons++;
        }
	comparisons++;
        if (i <= j) {
            int temp = A[i]; A[i] = A[j]; A[j] = temp;
            i++; j--;
            moves += 3;
        }
    }

    if (L < j) quickSort(A, L, j);
    if (i < R) quickSort(A, i, R);
}

int QuickSortWrapper(int n, int A[n], int debug) {
    comparisons = 0;
    moves = 0;
    quickSort(A, 0, n - 1);
    if (debug == 1) {
        printf("FactMoves: %d\nFactComparisons: %d\n", moves, comparisons);
    }
    return moves + comparisons;
}

double Timer(int (*sortFunc)(int, int[], int), int A[], int n) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(n, A, 1);
    gettimeofday(&end, NULL);
    print(n, A);
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

int countFact(int (*sortFunc)(int, int[], int), int n) {
    int A[n];

    FillDec(n, A);
    int DEC = sortFunc(n, A, 0);
    FillRand(n, A);
    int RAND = sortFunc(n, A, 0);
    FillInc(n, A);
    int INC = sortFunc(n, A, 0);

    printf("%-8d %-8d %-8d", DEC, RAND, INC);
    return 0;
}

int countRand(int (*sortFunc)(int, int[], int), int n, int A[]) {
    int *copy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = A[i];
    }

    int RAND = sortFunc(n, copy, 0);
    printf("%-10d", RAND);

    free(copy);
    return RAND;
}

int main() {
    int *A = malloc(4 * n);

    printf("+++++++++++++++QuickSort+++++++++++++++:\n");

    printf("FillInc:\n");
    FillInc(n, A);
    print(n, A);
    printf("Checksum of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));
    double Inc = Timer(QuickSortWrapper, A, n);
    printf("TIME: %.3f ms\n", Inc);
    printf("Checksum of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    printf("\nFillDec:\n");
    FillDec(n, A);
    print(n, A);
    printf("Checksum of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));
    double Dec = Timer(QuickSortWrapper, A, n);
    printf("TIME: %.3f ms\n", Dec);
    printf("Checksum of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    printf("\nFillRand:\n");
    FillRand(n, A);
    int *copy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        copy[i] = A[i];
    }

    print(n, A);
    printf("Checksum of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));
    double Rand = Timer(QuickSortWrapper, A, n);
    printf("TIME: %.3f ms\n", Rand);
    printf("Checksum of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    printf("\n  N     M+C theory       M+C fact\n");
    printf("                      D        R        I\n");

    printf("%-6d %-14d", 100, countTheory(100));
    countFact(QuickSortWrapper, 100);

    printf("\n%-6d %-14d", 200, countTheory(200));
    countFact(QuickSortWrapper, 200);

    printf("\n%-6d %-14d", 300, countTheory(300));
    countFact(QuickSortWrapper, 300);

    printf("\n%-6d %-14d", 400, countTheory(400));
    countFact(QuickSortWrapper, 400);

    printf("\n%-6d %-14d", 500, countTheory(500));
    countFact(QuickSortWrapper, 500);

    free(A);
    return 0;
}