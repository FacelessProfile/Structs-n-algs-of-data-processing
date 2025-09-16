#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#define PAGE_SIZE 20
#define QUEUE_SIZE 4000

typedef struct record
{
    char FIO[32];
    char street[18];
    short int House;
    short int Apartment;
    char Date[10];
} record;

typedef struct queue_node
{
    int index;
    struct queue_node *next;
} queue_node;

record DB[4000];

int compare_records(const record *a, const record *b)
{
    int cmp = strcmp(a->FIO, b->FIO);
    if (cmp==0)
        return strcmp(a->street, b->street);
    return cmp;
}

void HeapBuild(int A[], int L, int R)
{
    int x = A[L];
    int i = L;
    while (1)
    {
        int j = 2*i +1;
        if (j > R)
            break;
        if (j < R && compare_records(&DB[A[j+1]], &DB[A[j]])>0)
        {
            j++;
        }

        if (compare_records(&DB[x], &DB[A[j]])>=0)
            break;

        A[i] = A[j];
        i = j;
    }
    
    A[i] = x;
}

void HeapSort(int A[], int n)
{
    int temp;
    for (int L=n/2-1; L>=0; L--)
    {
        HeapBuild(A, L, n-1);
    }

    for (int R=n-1; R>0; R--)
    {
        temp = A[0];
        A[0] = A[R];
        A[R] = temp;

        HeapBuild(A, 0, R-1);
    }
}

int find_lower(int n, int A[], char *FIO_first_three) {
    int L=0, R=n-1;
    while (L < R) {
        int m = (L + R) / 2;
        if (strncmp(DB[A[m]].FIO, FIO_first_three, 3)<0) {
            L=m+1;
        } else {
            R=m;
        }
    }
    if (strncmp(DB[A[L]].FIO, FIO_first_three, 3)==0) {
        return L;
    } else {
        return -1;
    }
}

int find_upper(int n, int A[], char *FIO_first_three) {
    int L=0, R=n-1;
    while (L<R) {
        int m = (L+R)/2;
        if (strncmp(DB[A[m]].FIO, FIO_first_three, 3)<=0) {
            L = m + 1;
        } else {
            R = m;
        }
    }
    if (strncmp(DB[A[L]].FIO, FIO_first_three, 3)==0) return L+1;
    return L;
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

char display_loop(void *data, int is_list, int num_records, char *label, char *prompt) {
    int page = 0;
    char command;
    while (1) {
        clear_screen();
        int start = page * PAGE_SIZE;
        int end = start + PAGE_SIZE;
        if (end > num_records) end = num_records;
#ifdef _WIN32
        system("chcp 65001 >nul");
#endif
        printf("%-35s %-22s %-8s %-22s %-15s\n", 
               "Фио", "Улица", "Дом", "Квартира", "Дата");
        printf("-------------------------------------------------------------------------------\n");
#ifdef _WIN32
        system("chcp 866 >nul");
#endif
        if (is_list) {
            queue_node *current = (queue_node *)data;
            for (int j = 0; j < start && current; ++j) {
                current = current->next;
            }
            for (int i = start; i < end && current; ++i) {
                record r = DB[current->index];
                printf("%-32s %-18s %-6hd %-10hd %-10s\n", 
                       r.FIO, 
                       r.street, 
                       r.House, 
                       r.Apartment, 
                       r.Date);
                current = current->next;
            }
        } else {
            int *indexes = (int *)data;
            for (int i = start; i < end; ++i)
            {
                record r = DB[indexes[i]];
                printf("%-32s %-18s %-6hd %-10hd %-10s\n", 
                       r.FIO, 
                       r.street, 
                       r.House, 
                       r.Apartment, 
                       r.Date);
            }
        }
#ifdef _WIN32
        system("chcp 65001 >nul");
#endif
        printf("\nЗаписи %d–%d из %s %d\n", start+1, end, label, num_records);
        printf("%s", prompt);
        fflush(stdout);

        int c = getchar();
        if (c == EOF) c='q';
        command = (char)c;
        while (getchar() != '\n' && !feof(stdin));

#ifdef _WIN32
        system("chcp 866 > nul");
#endif
        if (command=='f') {
            if ((page + 1) * PAGE_SIZE<num_records)
                page++;
            continue;
        }
        else if (command=='b') {
            if (page > 0)
                page--;
            continue;
        } else {




            return command;
        }
    }
}

int main()
{
#ifdef _WIN32
    system("chcp 866 > nul");
#else
    setlocale(LC_ALL, "");
#endif

    FILE *fp;
    fp = fopen("testBase4.dat", "rb");

    if (fp == NULL) {
        printf("NO BD PROVIDED PLEASE GIMME testBase4.dat!\n");
        return 1;
    }

    int total_records = fread(DB, sizeof(record), QUEUE_SIZE, fp);
    fclose(fp);

    if (total_records <= 0) {
        printf("Файл пуст или ошибка чтения.\n");
        return 1;
    }

    int indexes[4000];
    int orig_indexes[4000];
    for (int i = 0; i < total_records; i++) {
        indexes[i] = i;
        orig_indexes[i] = i;
    }

    HeapSort(indexes, total_records);

    queue_node *queue_head;
    queue_node *queue_tail;
    int queue_size;

    char main_prompt_normal[] = " f - следующие, b - предыдущие, s - поиск, l - отсортированная, q - выйти: ";
    char main_prompt_sorted[] = " f - следующие, b - предыдущие, s - поиск, q - назад: ";
    char search_prompt[] = " f - следующие, b - предыдущие, q - выйти: ";
    char command;
    int mode = 0;
    int running = 1;

    while (running) {
        if (mode == 0) {
            command = display_loop(orig_indexes, 0, total_records, "всего", main_prompt_normal);
            if (command=='l') {

                mode = 1;

                continue;
            } else if (command=='s') {
#ifdef _WIN32
                system("chcp 65001 >nul");
#endif
                char FIO_first_three[4] = {0};
                printf("Введите 3 первые буквы фамилии: ");
#ifdef _WIN32
                system("chcp 866>nul");
#endif
                if (scanf("%3s", FIO_first_three)!= 1) {
                    while (getchar() !='\n' && !feof(stdin));
                    continue;
                }
#ifdef _WIN32
                system("chcp 65001 >nul");
#endif
                while (getchar()!='\n' && !feof(stdin));

                queue_head = NULL;
                queue_tail = NULL;
                queue_size = 0;
                for (int i=0; i<total_records; ++i) {
                    if (strncmp(DB[orig_indexes[i]].FIO, FIO_first_three, 3)==0) {
                        queue_node *p = (queue_node *)malloc(sizeof(queue_node));
                        p->index = orig_indexes[i];
                        p->next = NULL;
                        if (queue_tail) {
                            queue_tail->next = p;
                        } else {
                            queue_head = p;
                        }
                        queue_tail = p;
                        queue_size++;
                    }
                }
                if (queue_size== 0) {
                    printf("Не найдено.\n");
                    printf("Нажмите Enter...");
                    while (getchar() != '\n' && !feof(stdin));
                    continue;
                }
                display_loop(queue_head, 1, queue_size, "найденных", search_prompt);
                queue_node *curr = queue_head;
                while (curr) {
                    queue_node *next = curr->next;
                    free(curr);
                    curr = next;
                }
            } else if (command =='q') {
                running=0;
                break;
            } else {





                continue;
            }
        } else {

            command = display_loop(indexes, 0, total_records, "всего", main_prompt_sorted);
            if (command=='q') {
                mode = 0;
                continue;
            } else if (command=='s') {
#ifdef _WIN32
                system("chcp 65001 > nul");
#endif
                char FIO_first_three[4] = {0};
                printf("Введите 3 первые буквы фамилии: ");
#ifdef _WIN32
                system("chcp 866 > nul");
#endif
                if (scanf("%3s", FIO_first_three) != 1) {
                    while (getchar() != '\n' && !feof(stdin));
                    continue;
                }
#ifdef _WIN32
                system("chcp 65001 > nul");
#endif
                while (getchar() != '\n' && !feof(stdin));

                int lower = find_lower(total_records, indexes, FIO_first_three);
                if (lower == -1) {
                    printf("Не найдено.\n");
                    printf("Нажмите Enter...");
                    while (getchar() != '\n' && !feof(stdin));
                    continue;
                }

                int upper = find_upper(total_records, indexes, FIO_first_three);
                queue_head = NULL;
                queue_tail = NULL;
                queue_size = 0;
                for (int i = lower; i < upper; i++) {
                    queue_node *p = (queue_node *)malloc(sizeof(queue_node));
                    p->index = indexes[i];
                    p->next = NULL;
                    if (queue_tail) {
                        queue_tail->next = p;
                    } else {
                        queue_head = p;
                    }
                    queue_tail = p;
                    queue_size++;
                }
                display_loop(queue_head, 1, queue_size, "найденных", search_prompt);
                queue_node *curr = queue_head;
                while (curr) {
                    queue_node *next = curr->next;
                    free(curr);
                    curr = next;
                }
            } else {








                continue;
            }
        }
    }

    return 0;
}
