#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
int n=10;



int countTheory(int n){
int C = ((n*n)-n)/2;
return 2*C+2*n-2;
}

void FillInc(int n,int A[n]){

	for (int i=0;i<n;i++){
		A[i]=i;
	}
}

void FillDec(int n,int A[n]){
	int k=0;
	for (int i=n-1;i>=0;i--){
		A[k]=i;
		k++;
	}
}

void FillRand(int n, int A[n]){
	srand(time(NULL));
	for (int i=0;i<n;i++){
		A[i]=rand()%n;
	}
}

int CheckSum(int n, int A[n]){
	int Cs=0;
	for (int i=0;i<n;i++){
		Cs+=A[i];
	}
	return Cs;
}

int RunNumber(int n, int A[n]){
	int series=1;
	for (int i=0;i<n-1;i++){
		if (A[i]>A[i+1]){
		series+=1;
		}
	}
	return series;
}

void print(int n,int A[n]){
	for (int i=0;i<=(n-1);i++){
		printf("%d ",A[i]);
	}
	printf("\n");
}

int bubbleSort(int n,int A[n],int debug){
	int moves=0;
	int comparisons=0;
	for(int i=0;i<n-1;i++){
		for(int j=(n-1);j>i;j--){
			comparisons++;
			if(A[j]<A[j-1]){
				moves+=3;
				int temp=A[j];
				A[j]=A[j-1];
				A[j-1]=temp;
			}
		}
	}
if (debug==1){
	printf("Factmoves:%d\n Factcomparisons:%d\n",moves,comparisons);
	}
return moves+comparisons;
}


int shakerSort(int n, int A[n], int debug) {
    int L = 0, R = n - 1, K = n - 1;
    int moves = 0, comparisons = 0;
    
    do {
        for (int j = R; j > L; j--) {
            comparisons++;
            if (A[j] < A[j - 1]) {
                moves += 3;
                int temp = A[j];
                A[j] = A[j - 1];
                A[j - 1] = temp;
                K = j;
            }
        }
        L = K;
        
        for (int j = L; j < R; j++) {
            comparisons++;
            if (A[j] > A[j + 1]) {
                moves += 3;
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
                K = j;
            }
        }
        R = K;
    } while (L < R);
    
    if (debug == 1) {
        printf("Factmoves:%d\nFactcomparisons:%d\n", moves, comparisons);
    }
    return moves + comparisons;
}


int insertSort(int n, int A[n],int debug) {
    int comparisons=0;
    int moves=0;
    int temp=0;

    for (int i=1; i<n;i++) {
        temp=A[i];
        int j =i-1;

        while (j>=0 &&temp<A[j]) {
            comparisons++;
            A[j+1]=A[j];
            moves++;
            j--;
        }

        if (j>=0) {
            comparisons++;
        }

        A[j+1]=temp;
        moves += 2;
    }
    if (debug == 1) {
        printf("Factmoves:%d\nFactcomparisons:%d\n", moves, comparisons);
    }
    return moves + comparisons;
}


int SelectSort(int n,int A[],int debug) {
    int i,j,min,temp;
    int comparisons=0;
    int swaps=0;

    for (i=0;i<n-1;i++) {
        min=i;
        for (j =i+1;j<n;j++) {
            comparisons++;
            if (A[j]<A[min]){
                min=j;
            }
        }
        temp=A[i];
        A[i]=A[min];
        A[min]=temp;
        swaps+=3;
    }
    if (debug==1){
        printf("\nComparisons: %d", comparisons);
        printf("\nswaps: %d\n", swaps);
    }
    return comparisons + swaps;
}








double Timer(int (*sortFunc)(int, int[],int), int A[], int n) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(n, A,1);
    gettimeofday(&end, NULL);
    print(n,A);
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}









int countFact(int (*sortFunc)(int, int[],int), int n) {
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

int main(){
int *A=malloc(4*n);

printf("+++++++++++++++++Insert+++++++++++++++++:\n");

printf("FillInc:\n");

FillInc(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));
double Inc=Timer(insertSort,A,n);
printf("TIME: %.3f ms\n",Inc);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

printf("\n");

printf("FillDec:\n");

FillDec(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

double Dec=Timer(insertSort,A,n);
printf("TIME: %.3f ms\n",Dec);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

printf("\n");

printf("FillRand:\n");

FillRand(n,A);
int *copy = malloc(n * sizeof(int));
for(int i=0;i<n;i++){
copy[i]=A[i];
}

print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

double Rand=Timer(insertSort,A,n);
printf("TIME: %.3f ms\n",Rand);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));


printf("\n");

printf(" N     M+C theor       M+C fact\n");
    printf("                     D        R        I\n");

    printf("%-6d %-12d", 100, countTheory(100));
    countFact(insertSort,100);

    printf("\n%-6d %-12d", 200, countTheory(200));
    countFact(insertSort,200);

    printf("\n%-6d %-12d", 300, countTheory(300));
    countFact(insertSort,300);

    printf("\n%-6d %-12d", 400, countTheory(400));
    countFact(insertSort,400);

    printf("\n%-6d %-12d", 500, countTheory(500));
    countFact(insertSort,500);
    
printf("\n");
printf("\n");

 int sizes[] = {100, 200, 300, 400, 500};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    printf("         		M+C\n");
    printf(" N     Select    Bubble    Shaker    Insert\n");

    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        int A[n];

        FillRand(n, A);

        printf("%-8d", n);
        countRand(SelectSort, n, A);
        countRand(bubbleSort, n, A);
        countRand(shakerSort, n, A);
        countRand(insertSort, n, A);
        printf("\n");
    }








return 0;

}
