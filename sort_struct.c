#include <stdio.h>
#include <string.h>

#define SIZE 5

typedef struct {
    char lastName[20];
    char firstName[20];
    char phoneNumber[15];
    int age;
} Contact;

int Less(Contact abonX, Contact abonY) {
    if (strcmp(abonX.firstName, abonY.firstName) < 0) return 1;
    else if (strcmp(abonX.firstName, abonY.firstName) > 0) return 0;
    else {
        if (strcmp(abonX.phoneNumber, abonY.phoneNumber) < 0) return 1;
        else return 0;
    }
}

void insertSort(Contact phonebook[], int n, int increase) {
    for (int i = 1; i < n; i++) {
        Contact temp = phonebook[i];
        int j = i - 1;
        while (j >= 0 && (increase ? Less(temp, phonebook[j]) : Less(phonebook[j], temp))) {
            phonebook[j + 1] = phonebook[j];
            j--;
        }
        phonebook[j + 1] = temp;
    }
}

void printPhonebook(Contact phonebook[], int n) {
    printf("%-15s %-15s %-15s %-5s\n", "lastName", "firstName", "phone Num", "Age");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-15s %-15s %-15s %-5d\n", phonebook[i].lastName, phonebook[i].firstName, phonebook[i].phoneNumber, phonebook[i].age);
    }
}




int binarySearch(Contact phonebook[], int n, char *target) {
    int L = 0, R = n;
    while (L < R) {
        int mid = L+(R-L) / 2;
        if (strcmp(phonebook[mid].firstName, target) < 0) {
            L = mid + 1;
        } else {
            R = mid;
        }
    }
    if (R < n && strcmp(phonebook[R].firstName, target) == 0) return R;
    return -1;
}





int main() {
    Contact phonebook[SIZE] = {
        {"Ivanov", "Andrey", "+79951234567", 18},
        {"Petrov", "Timofei", "+79951234568", 19},
        {"Shalamov", "Nikita", "+79951234569", 20},
        {"Markov", "Viktor", "+79951234570", 21},
        {"Kachur", "Anna", "+79951234571", 22}
    };
    
    printf("\n\nSOURCE:\n\n");
    printPhonebook(phonebook, SIZE);
    
    int increase = 1;
    insertSort(phonebook, SIZE, increase);
    
    printf("\nSORTED:\n\n");
    printPhonebook(phonebook, SIZE);
    

    char target[20];
    printf("\nInput target firstname:");
    scanf("%s", target);


    int index = binarySearch(phonebook, SIZE, target);
    if (index != -1) {
        printf("\nContact founded:\n");
        printf("%-15s %-15s %-15s %-5d\n", phonebook[index].lastName, phonebook[index].firstName, phonebook[index].phoneNumber, phonebook[index].age);
    } else {
        printf("\nContact isnt in phonebook.\n");
    }

    return 0;
}
