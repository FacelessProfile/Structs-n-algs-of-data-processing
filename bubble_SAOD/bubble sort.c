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
	for (int i=0;i<n;i++){
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


double Timer(int (*sortFunc)(int, int[],int), int A[], int n) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    sortFunc(n, A,1);
    gettimeofday(&end, NULL);
    print(n,A);
    return (end.tv_sec - start.tv_sec) * 1000.0 + (end.tv_usec - start.tv_usec) / 1000.0;
}


int countFact(int n) {
    int A[n];

    FillDec(n, A);
    int DEC = bubbleSort(n, A, 0);
    FillRand(n, A);
    int RAND = bubbleSort(n, A, 0);
    FillInc(n, A);
    int INC = bubbleSort(n, A, 0);

    printf("%-8d %-8d %-8d\n", DEC, RAND, INC);  // Выравнивание значений по колонкам
    return 0;
}

int main(){
int *A=malloc(4*n);
printf("FillInc:\n");
FillInc(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));
int Inc=bubbleSort(n,A,1);

printf("FillDec:\n");

FillDec(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

int Dec=bubbleSort(n,A,1);

print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

printf("FillRand:\n");
FillRand(n,A);
print(n,A);
printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));

int Rand=bubbleSort(n,A,1);

printf("CS of A is:%d \n",CheckSum(n,A));
printf("Series:%d \n",RunNumber(n,A));



printf(" N     M+C theor       M+C fact\n");
    printf("                     D        R        I\n");

    printf("%-6d %-12d", 100, countTheory(100));
    countFact(100);

    printf("%-6d %-12d", 200, countTheory(200));
    countFact(200);

    printf("%-6d %-12d", 300, countTheory(300));
    countFact(300);

    printf("%-6d %-12d", 400, countTheory(400));
    countFact(400);

    printf("%-6d %-12d", 500, countTheory(500));
    countFact(500);

    return 0;

}