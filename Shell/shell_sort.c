#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>

int n = 10;

int countTheory(int n) {
    int C = ((n * n) - n) / 2;
    return 2 * C + 2 * n - 2;
}

void FillInc(int n, int A[n]) {
    for (int i = 0; i < n; i++) {
        A[i] = i;
    }
}

void FillDec(int n, int A[n]) {
    int k = 0;
    for (int i = n - 1; i >= 0; i--) {
        A[k] = i;
        k++;
    }
}

void FillRand(int n, int A[n]) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        A[i] = rand() % n;
    }
}

int CheckSum(int n, int A[n]) {
    int Cs = 0;
    for (int i = 0; i < n; i++) {
        Cs += A[i];
    }
    return Cs;
}

int RunNumber(int n, int A[n]) {
    int series = 1;
    for (int i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            series += 1;
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

int insertSort(int n, int A[n], int debug) {
    int comparisons = 0;
    int moves = 0;
    int temp = 0;

    for (int i = 1; i < n; i++) {
        temp = A[i];
        int j = i - 1;
        while (j >= 0 && temp < A[j]) {
            comparisons++;
            A[j + 1] = A[j];
            moves++;
            j--;
        }
        if (j >= 0) {
            comparisons++;
        }
        A[j + 1] = temp;
        moves += 2;
    }
    if (debug == 1) {
        printf("Factmoves:%d\nFactcomparisons:%d\n", moves, comparisons);
    }
    return moves + comparisons;
}

int shellSort(int n, int A[n], int debug) {
    int comparisons = 0;
    int moves = 0;

    int h = 1;
    while (h < n / 3) {
        h = 2 * h + 1;
    }

    while (h >= 1) {
        for (int i = h; i < n; i++) {
            int temp = A[i];
            int j = i - h;
            while (j >= 0 && temp < A[j]) {
                comparisons++;
                A[j + h] = A[j];
                moves++;
                j -= h;
            }
            if (j >= 0) {
                comparisons++;
            }
            A[j + h] = temp;
            moves++;
        }
        h /= 2;
    }

    if (debug) {
        printf("Fact moves: %d\nFact comparisons: %d\n", moves, comparisons);
    }
    return moves + comparisons;
}

int shellSortBetter(int n, int A[n], int debug) {
    int comparisons = 0;
    int moves = 0;

    int ciura_sequence[] = {701, 301, 132, 57, 23, 10, 4, 1};
    int steps[20];
    int num_steps = 0;

    for (int i = 0; i < sizeof(ciura_sequence)/sizeof(ciura_sequence[0]); i++) {
        if (ciura_sequence[i] <= n) {
            steps[num_steps++] = ciura_sequence[i];
        }
    }

    for (int s = 0; s < num_steps; s++) {
        int h = steps[s];
        for (int i = h; i < n; i++) {
            int temp = A[i];
            int j = i - h;
            while (j >= 0 && temp < A[j]) {
                comparisons++;
                A[j + h] = A[j];
                moves++;
                j -= h;
            }
            if (j >= 0) {
                comparisons++;
            }
            A[j + h] = temp;
            moves++;
        }
    }

    if (debug) {
        printf("Fact moves: %d\nFact comparisons: %d\n", moves, comparisons);
    }
    return moves + comparisons;
}

void generateShellSequenceAsString(int n, char *buffer) {
    int h = 1;
    int sequence[20];
    int count = 0;

    while (h < n) {
        sequence[count++] = h;
        h = 2 * h + 1;
    }

    int len = 0;
    for (int i = count - 1; i >= 0; i--) {
        len += sprintf(buffer + len, "%d ", sequence[i]);
    }
    
    while (len < 22) {
        buffer[len++] = ' ';
    }
    buffer[len] = '\0';
}

void generateCiuraSequenceAsString(int n, char *buffer) {
    int ciura_sequence[] = {701, 301, 132, 57, 23, 10, 4, 1};
    int steps[20];
    int num_steps = 0;

    for (int i = 0; i < sizeof(ciura_sequence)/sizeof(ciura_sequence[0]); i++) {
        if (ciura_sequence[i] <= n) {
            steps[num_steps++] = ciura_sequence[i];
        }
    }

    int len = 0;
    for (int i = 0; i < num_steps; i++) {
        len += snprintf(buffer + len, 30 - len, "%d ", steps[i]);
    }

    if (len > 0 && buffer[len-1] == ' ') {
        buffer[len-1] = '\0';
        len--;
    }

    while (len < 22) {
        buffer[len++] = ' ';
    }
    buffer[len] = '\0';
}

void printTable() {
    printf("-----------------------------------------------------------------------------------\n");
    printf("%-8s %-22s %-12s %-22s %-12s\n", "N", "h1 … hm (Knuth)", "Shell M+C", "h1 … hm (Better)", "Shell M+C");
    printf("-----------------------------------------------------------------------------------\n");

    int testSizes[] = {100, 200, 300, 400, 500};
    for (int i = 0; i < 5; i++) {
        int size = testSizes[i];

        char knuth_sequence[30] = {0};
        generateShellSequenceAsString(size, knuth_sequence);

        int *A_knuth = malloc(size * sizeof(int));
        FillDec(size, A_knuth);
        int knuth_mc = shellSort(size, A_knuth, 0);
        free(A_knuth);

        char better_sequence[30] = {0};
        generateCiuraSequenceAsString(size, better_sequence);

        int *A_better = malloc(size * sizeof(int));
        FillDec(size, A_better);
        int better_mc = shellSortBetter(size, A_better, 0);
        free(A_better);

        printf("%-8d %-25s %-12d %-25s %-12d\n", size, knuth_sequence, knuth_mc, better_sequence, better_mc);
    }
    printf("-----------------------------------------------------------------------------------\n");
}

double Timer(int (*sortFunc)(int, int[], int), int A[], int n) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(n, A, 1);
    gettimeofday(&end, NULL);
    print(n, A);
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}

int main(){
    int *A = malloc(4 * n);

    printf("+++++++++++++++++Insert+++++++++++++++++:\n");

    printf("FillInc:\n");
    FillInc(n, A);
    print(n, A);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));
    double Inc = Timer(insertSort, A, n);
    printf("TIME: %.3f ms\n", Inc);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));

    printf("\n");

    printf("FillDec:\n");
    FillDec(n, A);
    print(n, A);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));
    double Dec = Timer(insertSort, A, n);
    printf("TIME: %.3f ms\n", Dec);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));

    printf("\n");

    printf("FillRand:\n");
    FillRand(n, A);
    int *copy = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++){
        copy[i] = A[i];
    }
    print(n, A);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));
    double Rand = Timer(insertSort, A, n);
    printf("TIME: %.3f ms\n", Rand);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));

    printf("-----------------------------------SHELL-------------------------------------\n");
    printf("FillInc:\n");
    FillInc(n, A);
    print(n, A);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));
    Inc = Timer(shellSort, A, n);
    printf("TIME: %.3f ms\n", Inc);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));

    printf("\n");

    printf("FillDec:\n");
    FillDec(n, A);
    print(n, A);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));
    Dec = Timer(shellSort, A, n);
    printf("TIME: %.3f ms\n", Dec);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));

    printf("\n");

    printf("FillRand:\n");
    FillRand(n, A);
    print(n, A);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));
    Rand = Timer(shellSort, A, n);
    printf("TIME: %.3f ms\n", Rand);
    printf("CS of A is:%d \n", CheckSum(n, A));
    printf("Series:%d \n", RunNumber(n, A));

    printTable();
    free(A);
    return 0;
}
