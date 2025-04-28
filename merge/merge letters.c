#include <stdio.h>
#include <stdlib.h>

typedef struct tData {
    struct tData *next;
    int data;  // Заменим char на int, чтобы хранить числовые значения
} tData;


char* aplh[34] = {
    "", //for empty index 
    "a",  // А
    "b",  // Б
    "v",  // В
    "g",  // Г
    "d",  // Д
    "e",  // Е
    "yo", // Ё
    "zh", // Ж
    "z",  // З
    "i",  // И
    "y",  // Й
    "k",  // К
    "l",  // Л
    "m",  // М
    "n",  // Н
    "o",  // О
    "p",  // П
    "r",  // Р
    "s",  // С
    "t",  // Т
    "u",  // У
    "f",  // Ф
    "h",  // Х
    "c",  // Ц
    "ch", // Ч
    "sh", // Ш
    "shch", // Щ
    "tz",   // Ъ (твёрдый знак, обычно пропускается)
    "y",  // Ы
    "mz",   // Ь (мягкий знак, обычно пропускается)
    "e",  // Э
    "yu", // Ю
    "ya"  // Я
};


void AddToStack(tData** head, int data) {
    tData* p = (tData*)malloc(sizeof(tData));
    p->data = data;
    p->next = *head;
    *head = p;
}

void print_list(tData *head) {
    tData *p = head;
    while (p != NULL) {
        printf("%s ", aplh[p->data]);  // Выводим числа
        p = p->next;
    }
    printf("\n");
}

void clear(tData *head) {
    tData *p = head;
    while (p != NULL) {
        tData *temp_p = p;
        p = p->next;
        free(temp_p);
    }
}

typedef struct {
    tData *head;
    tData *tail;
} tQueue;

void InitializeQueue(tQueue *q) {
    q->head = q->tail = NULL;
}

void MergeSeries(tData **a, int q, tData **b, int r, tQueue *c) {
    printf("Merge: \n");
    while (q > 0 && r > 0 && *a != NULL && *b != NULL) {
        printf("%s compares with %s \n",aplh[(*a)->data],aplh[(*b)->data]);
        if ((*a)->data <= (*b)->data) {
            if (c->head == NULL) {
                c->head = c->tail = *a;
            } else {
                c->tail->next = *a;
                c->tail = *a;
            }
            *a = (*a)->next;
            q--;
        } else {
            if (c->head == NULL) {
                c->head = c->tail = *b;
            } else {
                c->tail->next = *b;
                c->tail = *b;
            }
            *b = (*b)->next;
            r--;
        }
    }

    while (q > 0 && *a != NULL) {
        if (c->head == NULL) {
            c->head = c->tail = *a;
        } else {
            c->tail->next = *a;
            c->tail = *a;
        }
        *a = (*a)->next;
        q--;
    }

    while (r > 0 && *b != NULL) {
        if (c->head == NULL) {
            c->head = c->tail = *b;
        } else {
            c->tail->next = *b;
            c->tail = *b;
        }
        *b = (*b)->next;
        r--;
    }

    if (c->tail != NULL) {
        c->tail->next = NULL;
    }
    printf("Merge result: ");
    print_list(c->head);
}

void SplitLists(tData *head, tData **a, tData **b, int *n) {
    *a = head;
    *b = head->next;

    tData *k = *a, *p = *b;
    *n = 1;

    while (p != NULL) {
        (*n)++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
}

void MergeSort(tData **S) {
    if (*S == NULL || (*S)->next == NULL) {
        return;
    }

    tQueue c[2];
    tData *a, *b;
    int n;
    SplitLists(*S, &a, &b, &n);

    printf("\nInitial split:\n");
    printf("A: ");
    print_list(a);
    printf("B: ");
    print_list(b);
    printf("----------------\n");

    for (int p = 1; p < n; p *= 2) {
        InitializeQueue(&c[0]);
        InitializeQueue(&c[1]);
        int i = 0, m = n;

        printf("series size: %d\n", p);

        while (m > 0) {
            int q = (m >= p) ? p : m;
            m -= q;
            int r = (m >= p) ? p : m;
            m -= r;

            MergeSeries(&a, q, &b, r, &c[i]);

            i = 1 - i;
        }

        a = c[0].head;
        b = c[1].head;

        printf("after merge:\n");
        printf("A: ");
        print_list(a);
        printf("B: ");
        print_list(b);
        printf("----------------\n");
    }

    if (c[0].tail != NULL) {
        c[0].tail->next = NULL;
    }
    *S = c[0].head;
}

int main() {
    // 26 -> ш, 20 -> т, 6 -> е, 15 -> р, 18 -> н, 10 -> и, 19 -> с, 12 -> к
    int numbers[] = {26, 1, 13, 1, 14, 16, 3, 15, 10, 12, 10, 20}; // Positions in alphabet
    int len = sizeof(numbers) / sizeof(numbers[0]);
    tData *stack = NULL;

    // Заполняем стек числовыми значениями
    for (int i = len-1; i >= 0; i--) {
        AddToStack(&stack, numbers[i]);
    }

    printf("initial sequence: ");
    print_list(stack);

    MergeSort(&stack);

    printf("\nsorted sequence: ");
    print_list(stack);

    clear(stack);
    return 0;
}
