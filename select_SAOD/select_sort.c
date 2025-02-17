#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n=10;

int countTheory(int n){
    int C = ((n*n)-n)/2;
    return C+(3*(n-1));
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

int SelectSort_UPGR(int n,int A[],int debug) {
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
        if (A[i]!=A[min]){
            temp=A[i];
            A[i]=A[min];
            A[min]=temp;
            swaps+=3;
        }
    }
    if (debug==1){
        printf("\nComparisons: %d", comparisons);
        printf("\nswaps: %d\n", swaps);
    }
    return comparisons + swaps;
}

int countFact(int (*Func)(int, int[], int), int n) {
    int A[n];

    FillDec(n, A);
    int DEC = Func(n, A, 0);
    FillRand(n, A);
    int RAND = Func(n, A, 0);
    FillInc(n, A);
    int INC = Func(n, A, 0);

    printf("%-6d %-6d %-6d", DEC, RAND, INC);
    return 0;
}

int main() {
    srand(time(NULL));
    int *A = malloc(n * sizeof(int));

    printf("FillInc:\n");
    FillInc(n, A);
    print(n, A);
    printf("CS of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    printf("FillDec:\n");
    FillDec(n, A);
    print(n, A);
    printf("CS of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    printf("FillRand:\n");
    FillRand(n, A);
    print(n, A);
    printf("CS of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    printf("Selection sort:\n");
    SelectSort(n, A, 1);
    print(n, A);
    printf("CS of A is: %d \n", CheckSum(n, A));
    printf("Series: %d \n", RunNumber(n, A));

    free(A);

    printf("\n N     M+C theor         M+C fact    	     M+C Fact (UPGR)\n");
    printf("                       D      R     I        D      R     I\n\n"); 
    printf(" 10        %d         ",countTheory(10));
    countFact(SelectSort,10);   
    printf("  "); 
    countFact(SelectSort_UPGR,10); 
    
    printf("\n\n");

    printf(" 100      %d      ",countTheory(100));
    countFact(SelectSort,100);   
    printf("  "); 
    countFact(SelectSort_UPGR,100);  
        
    return 0;
}
