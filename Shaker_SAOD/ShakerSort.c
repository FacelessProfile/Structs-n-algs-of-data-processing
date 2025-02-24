#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
int n=10;



int countTheory(int n){
int C = ((n*n)-n)/2;
return C+(3*C);
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
	printf("FactMoves:%d\n FactComparisons:%d\n",moves,comparisons);
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
        printf("FactMoves:%d\nFactComparisons:%d\n", moves, comparisons);
    }
    return moves + comparisons;
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

    printf("%-8d %-8d %-8d", DEC, RAND, INC);  // Выравнивание значений по колонкам
    return 0;
}

int main(){
int *A=malloc(4*n);

printf("+++++++++++++++++BUBBLE+++++++++++++++++:\n");

printf("FillInc:\n");

FillInc(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));
double Inc=Timer(bubbleSort,A,n);
printf("TIME: %.3f ms\n",Inc);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

printf("\n");

printf("FillDec:\n");

FillDec(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

double Dec=Timer(bubbleSort,A,n);
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

double Rand=Timer(bubbleSort,A,n);
printf("TIME: %.3f ms\n",Rand);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));


printf("\n");





printf("+++++++++++++++++SHAKER+++++++++++++++++:\n");

printf("FillInc:\n");

FillInc(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));
Inc=Timer(shakerSort,A,n);
printf("TIME: %.3f ms\n",Inc);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

printf("\n");

printf("FillDec:\n");

FillDec(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

Dec=Timer(shakerSort,A,n);
printf("TIME: %.3f ms\n",Dec);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

printf("\n");

printf("FillRand:\n");

print(n,copy);
printf("CS of A is:%d \n",CheckSum(n,copy));
printf("Series:%d \n",RunNumber(n,copy));

Rand=Timer(shakerSort,copy,n);
printf("TIME: %.3f ms\n",Inc);
printf("CS of A is:%d \n",CheckSum(n,copy));
printf("Series:%d \n",RunNumber(n,copy));







printf(" N     	     Bubble M+C	       	        Shaker M+C\n");
    printf("   	 D        R        I       D        R        I\n");

    printf("%-6d %-12", 100);
    countFact(bubbleSort,100);
    countFact(shakerSort,100);
printf("\n");
    printf("%-6d %-12", 200);
    countFact(bubbleSort,200);
    countFact(shakerSort,200);
printf("\n");
    printf("%-6d %-12", 300);
    countFact(bubbleSort,300);
    countFact(shakerSort,300);
printf("\n");
    printf("%-6d %-12", 400);
    countFact(bubbleSort,400);
    countFact(shakerSort,400);
printf("\n");
    printf("%-6d %-12", 500);
    countFact(bubbleSort,500);
    countFact(shakerSort,500);
    return 0;

}