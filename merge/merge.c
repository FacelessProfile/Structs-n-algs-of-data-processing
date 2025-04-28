#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM 10

typedef struct Noda{
    struct Noda* next;
    int data;
} st;

// --- Stack functions ---
st* add_stack(st* head,int data){
    st* new = malloc(sizeof(st));
    new->next = head;
    new->data = data;
    return new;
}

st* delFROMstack(st* head){
    if (head == NULL) return NULL;
    st* p = head;
    head = p->next;
    free(p);
    return head;
}

void freeMEM(st* head){
    while (head) {
        st* temp = head;
        head = head->next;
        free(temp);
    }
}

void printStack(st* head){
    for (st* current = head; current; current = current->next) {
        if (current->next == NULL) printf("%d", current->data);
        else printf("%d, ", current->data);
    }
    printf("\n");
}

// --- Queue functions ---
st* add_QUEUE(st* tail, int data) {
    st* new = malloc(sizeof(st));
    new->data = data;
    new->next = NULL;
    tail->next = new;
    return new;
}

void print_queue(st* head) {
    st* current = head->next;
    while (current) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("this is the end(NIL)\n");
}

// --- List functions ---
void printList(st* head) {
    st* current = head;
    while (current) {
        printf("%d, ", current->data);
        current = current->next;
    }
    printf("end\n");
}

int checksum(st* head) {
    int sum = 0;
    for (st* cur = head; cur; cur = cur->next) sum += cur->data;
    return sum;
}

int count_series(st* head) {
    if (!head) return 0;
    int series = 1;
    for (st* cur = head; cur->next; cur = cur->next)
        if (cur->data > cur->next->data) series++;
    return series;
}

void free_list(st* head) {
    freeMEM(head);
}

void print_straight(st* head) {
    if (!head) return;
    if (head->next) printf("%d, ", head->data); else printf("%d", head->data);
    print_straight(head->next);
}

void print_reverse(st* head) {
    if (!head) return;
    if (head->next) print_reverse(head->next);
    if (head->next == NULL) printf("%d", head->data);
    else printf(", %d", head->data);
}

// --- Stack creation ---
st* fill_stack_inc(int n) {
    st* head = NULL;
    for (int i = n - 1; i >= 0; i--) head = add_stack(head, i);
    return head;
}

st* fill_stack_dec(int n) {
    st* head = NULL;
    for (int i = 0; i < n; i++) head = add_stack(head, i);
    return head;
}

st* fill_stack_rand(int n) {
    st* head = NULL;
    for (int i = 0; i < n; i++) head = add_stack(head, rand() % NUM);
    return head;
}

// --- Queue creation ---
st* fill_queue_inc(int n) {
    st* head = malloc(sizeof(st));
    head->next = NULL;
    st* tail = head;
    for (int i = 0; i < n; i++) tail = add_QUEUE(tail, i);
    return head;
}

st* fill_queue_dec(int n) {
    st* head = malloc(sizeof(st));
    head->next = NULL;
    st* tail = head;
    for (int i = n - 1; i >= 0; i--) tail = add_QUEUE(tail, i);
    return head;
}

st* fill_queue_rand(int n) {
    st* head = malloc(sizeof(st));
    head->next = NULL;
    st* tail = head;
    for (int i = 0; i < n; i++) tail = add_QUEUE(tail, rand() % NUM);
    return head;
}

// --- Merge-sort utilities ---

typedef struct {
    st* head;
    st* tail;
} Queue;

void InitializeQueue(Queue* q) {
    q->head = q->tail = NULL;
}

void MergeSeries(st** a, int q, st** b, int r, Queue* c, int* cmp, int* move) {
    while (q > 0 && r > 0 && *a && *b) {
        (*cmp)++;
        if ((*a)->data <= (*b)->data) {
            if (c->head == NULL) c->head = c->tail = *a;
            else { c->tail->next = *a; c->tail = *a; }
            *a = (*a)->next; q--;
        } else {
            if (c->head == NULL) c->head = c->tail = *b;
            else { c->tail->next = *b; c->tail = *b; }
            *b = (*b)->next; r--;
        }
        (*move)++;
    }
    while (q > 0 && *a) {
        if (c->head == NULL) c->head = c->tail = *a;
        else { c->tail->next = *a; c->tail = *a; }
        *a = (*a)->next; q--; (*move)++;
    }
    while (r > 0 && *b) {
        if (c->head == NULL) c->head = c->tail = *b;
        else { c->tail->next = *b; c->tail = *b; }
        *b = (*b)->next; r--; (*move)++;
    }
    if (c->tail) c->tail->next = NULL;
}

void SplitLists(st* head, st** a, st** b, int* n, int* move) {
    *a = head;
    *b = head->next;
    st* k = *a;
    st* p = *b;
    *n = 1;
    while (p) {
        (*move)++;
        k->next = p->next;
        k = p;
        p = p->next;
        (*n)++;
    }
}

void MergeSort(st** S, int* comparisons, int* moves) {
    if (*S == NULL || (*S)->next == NULL) return;
    Queue c[2];
    st* a;
    st* b;
    int n;
    SplitLists(*S, &a, &b, &n, moves);
    for (int p = 1; p < n; p *= 2) {
        InitializeQueue(&c[0]);
        InitializeQueue(&c[1]);
        int i = 0, m = n;
        while (m > 0) {
            int q = (m >= p) ? p : m; m -= q;
            int r = (m >= p) ? p : m; m -= r;
            MergeSeries(&a, q, &b, r, &c[i], comparisons, moves);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
    }
    if (c[0].tail) c[0].tail->next = NULL;
    *S = c[0].head;
}

int main() {
    srand((unsigned)time(NULL));
    int n = 10, m = 0;
    st *head = NULL, *a = NULL, *b = NULL;
    printf("Creating random list (size %d):\n", n);
    head = fill_stack_rand(n);
    printf("Original list:\n"); printList(head);
    printf("Checksum: %d, series: %d\n\n", checksum(head), count_series(head));

    printf("Splitting list into two sublists:\n");
    int moves = 0;
    SplitLists(head, &a, &b, &m, &moves);
    printf("List A:\n"); printList(a);
    printf("Checksum A: %d, series: %d\n", checksum(a), count_series(a));
    printf("List B:\n"); printList(b);
    printf("Checksum B: %d, series: %d\n\n", checksum(b), count_series(b));

    printf("Merging sublists:\n");
    Queue qarr[2]; InitializeQueue(&qarr[0]); InitializeQueue(&qarr[1]);
    int Cfact = 0, Mfact = 0, Ctheor = 0, Mtheor = 0;
    m = 0; // recompute length
    for (st* cur = a; cur; cur = cur->next) m++;
    for (st* cur = b; cur; cur = cur->next) m++;
    int idx = 0;
    printf("Before merging, total nodes: %d\n", m);
    while (m > 0) {
        int left = (m >= 1 ? 1 : m); m -= left;
        int right = (m >= 1 ? 1 : m); m -= right;
        Ctheor += ((left < right ? left : right) + left + right - 1) / 2;
        Mtheor += left + right;
        MergeSeries(&a, left, &b, right, &qarr[idx], &Cfact, &Mfact);
        idx ^= 1;
    }
    printf("Merged queue 0:\n"); printList(qarr[0].head);
    printf("Checksum: %d, series: %d\n", checksum(qarr[0].head), count_series(qarr[0].head));
    printf("Merge complexity (theoretical: C=%d, M=%d; actual: C=%d, M=%d)\n\n",
           Ctheor, Mtheor, Cfact, Mfact);

    // Merge sort demonstration
    freeMEM(head);
    head = NULL;
    printf("Merge sort on random list (size %d):\n", n);
    head = fill_stack_rand(n);
    printf("Unsorted list:\n"); printList(head);
    printf("Checksum: %d, series: %d\n\n", checksum(head), count_series(head));
    Cfact = Mfact = 0;
    MergeSort(&head, &Cfact, &Mfact);
    printf("Sorted list:\n"); printList(head);
    printf("Checksum: %d, series: %d\n", checksum(head), count_series(head));
    int theor = (int)(log2(n) * n);
    printf("Sort complexity (theoretical: C=M=%d; actual: C=%d, M=%d)\n\n",
           theor, Cfact, Mfact);

    // Complexity table
    printf("Complexity measurements for N = 100 to 500:\n");
    printf("|   N   | Theoretical M+C | Decr | Rand | Incr |\n");
    for (int j = 100; j <= 500; j += 100) {
        int Ttheor = (int)(2 * log2(j) * j);
        freeMEM(head); head = NULL; Cfact = Mfact = 0;
        head = fill_stack_rand(j); MergeSort(&head, &Cfact, &Mfact);
        int Trand = Cfact + Mfact;
        freeMEM(head); head = NULL; Cfact = Mfact = 0;
        // ascending
        for (int k = j-1; k >= 0; k--) head = add_stack(head, k);
        MergeSort(&head, &Cfact, &Mfact);
        int Tinc = Cfact + Mfact;
        freeMEM(head); head = NULL; Cfact = Mfact = 0;
        // descending
        for (int k = 0; k < j; k++) head = add_stack(head, k);
        MergeSort(&head, &Cfact, &Mfact);
        int Tdec = Cfact + Mfact;
        printf("| %5d | %15d | %5d | %4d | %4d |\n", j, Ttheor, Tdec, Trand, Tinc);
    }
    freeMEM(head);
    return 0;
}
