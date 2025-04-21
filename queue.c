//queueueueueueueueueueu uwu
//stack -  lifo
//queueueueueueue - fifo
//list - 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
    if (head->next) printf("%d, ", head->data);else printf("%d", head->data);
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

int main() {
    srand(time(NULL));

    // Тест функций создания стека
    printf("Stack inc:\n");
    st* headSTACK = fill_stack_inc(NUM);
    printStack(headSTACK);
    freeMEM(headSTACK);

    printf("Stack dec:\n");
    headSTACK = fill_stack_dec(NUM);
    printStack(headSTACK);
    freeMEM(headSTACK);

    printf("Stack rand:\n");
    headSTACK = fill_stack_rand(NUM);
    printStack(headSTACK);
    freeMEM(headSTACK);

    // Тест функций создания очереди
    printf("Queue inc:\n");
    st* headQueue = fill_queue_inc(NUM);
    print_queue(headQueue);
    free_list(headQueue);

    printf("Queue dec:\n");
    headQueue = fill_queue_dec(NUM);
    print_queue(headQueue);
    free_list(headQueue);

    printf("Queue rand:\n");
    headQueue = fill_queue_rand(NUM);
    print_queue(headQueue);
    free_list(headQueue);

    printf("List operations on inc list(stack):\n");
    st* list = fill_stack_inc(NUM);

    printf("printList: ");
    printList(list);

    printf("checksum: %d\n", checksum(list));
    printf("series: %d\n", count_series(list));

    printf("print_straight: ");
    print_straight(list);
    printf("\n");

    printf("print_reverse: ");
    print_reverse(list);
    printf("\n");

    free_list(list);

    printf("\n\nList operations on dec list(stack):\n");
    list = fill_stack_dec(NUM);

    printf("printList: ");
    printList(list);

    printf("checksum: %d\n", checksum(list));
    printf("series: %d\n", count_series(list));

    printf("print_straight: ");
    print_straight(list);
    printf("\n");

    printf("print_reverse: ");
    print_reverse(list);
    printf("\n");

    free_list(list);

    printf("\n\nList operations on rand list(stack):\n");
    list = fill_stack_rand(NUM);

    printf("printList: ");
    printList(list);

    printf("checksum: %d\n", checksum(list));
    printf("series: %d\n", count_series(list));

    printf("print_straight: ");
    print_straight(list);
    printf("\n");

    printf("print_reverse: ");
    print_reverse(list);
    printf("\n");

    free_list(list);

     printf("\n\nList operations on rand list(queue):\n");
    list = fill_queue_rand(NUM)->next;

    printf("printList: ");
    printList(list);

    printf("checksum: %d\n", checksum(list));
    printf("series: %d\n", count_series(list));

    printf("print_straight: ");
    print_straight(list);
    printf("\n");

    printf("print_reverse: ");
    print_reverse(list);
    printf("\n");

    free_list(list);

    return 0;
}


//meow