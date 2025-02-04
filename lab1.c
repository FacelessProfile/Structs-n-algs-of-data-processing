#include <stdio.h>
#include <stdlib.h>

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


int main(){
int *A=malloc(4*n);
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

}
