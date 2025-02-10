#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n=10;



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
	for (int i=0;i<n;i++){
		printf("%d ",A[i]);
	}
	printf("\n");
}



void SelectSort(int n,int A[]) {
    int i,j,min,temp;
    int comparisons=0;
    int swaps=0;

    for (int i=0;i<n-1;i++) {
        min=i;
        for (int j =i+1;j<n;j++) {
            comparisons++;
            if (A[j]<A[min]){
                min=j;
            }
        }
            temp=A[i];
            A[i]=A[min];
            A[min]=temp;
            swaps++;
        }
    printf("\nComparisons:%d",comparisons);
    printf("\nswaps:%d\n",swaps);
}






int main(){
	srand(time(NULL));
	int *A=malloc(n * sizeof(int));
	printf("FillInc:\n");
	FillInc(n,A);
	print(n,A);
	printf("CS of A is:%d \n",CheckSum(n,A));
	printf("Series:%d \n",RunNumber(n,A));
	printf("FillDec:\n");
	FillDec(n,A);
	print(n,A);
	printf("CS of A is:%d \n",CheckSum(n,A));
	printf("Series:%d \n",RunNumber(n,A));
	printf("FillRand:\n");
	FillRand(n,A);
	print(n,A);
	printf("CS of A is:%d \n",CheckSum(n,A));
	printf("Series:%d \n",RunNumber(n,A));
	printf("Selection sort:");
	SelectSort(n,A);
	print(n,A);
	printf("CS of A is:%d \n",CheckSum(n,A));
	printf("Series:%d \n",RunNumber(n,A));
	free(A);
}
