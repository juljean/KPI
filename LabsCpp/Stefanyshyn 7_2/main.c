#include <stdio.h>
#include <malloc.h>
#include <windows.h>
#define str1 " Laboratory 7"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "TOPIC: SINGLY LINKED LIST"
#define str5 "KM-91"
#define str6 "Nazar Stefanyshyn"
#define str7 "Kyiv 2020"

void spot(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void bound(int x1, int y1, int x2, int y2) {
    spot(x1, y1);
    for (int i = x1; i <= x2; i++) {
        if (i == x1)
            printf("\332");
        else if (i == x2)
            printf("\277");
        else {
            if ((i + 1) % 60 == 0)
                printf("");
            else printf("\304");
        }
    }

    for (int i = (y1 + 1); i <= (y2 - 1); i++) {
        spot(x1, i);
        printf("\263");
        spot(x2, i);
        printf("\263");
    }

    spot(x1, y2);
    for (int i = x1; i <= x2; i++) {
        if (i == x1) printf("\300");
        else if (i == x2)
            printf("\331");
        else {
            if ((i + 1) % 60 == 0)
                printf("");
            else printf("\304");
        }
    }
}

void frame() {
    bound(0, 0, 59, 10);
    spot(21, 1);
    puts(str1);
    spot(24, 2);
    puts(str2);
    spot(23, 3);
    puts(str3);
    spot(14, 4);
    puts(str4);
    spot(25, 5);
    puts(str5);
    spot(20, 6);
    puts(str6);
    spot(23, 9);
    puts(str7);
    printf("\n");
}

int int_val(const char *prompt){
    int inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &inp)) {
            if (getchar() == '\n') {
                if (inp >= 0) return inp;
                else {
                    printf("WRONG VALUE\n");
                    return int_val(prompt);
                }
            }
            else
            {
                while (getchar() != '\n');
                printf("WRONG VALUE\n");
            }
        }
        else {
            while (getchar() != '\n');
            printf("WRONG VALUE\n");
        }
    }
}

typedef struct list{
    int num;
    struct list* next;
}list;

list* create(){
    list* pnt, *prev;
    list* head = prev = pnt = (list*) malloc(sizeof(list));
    pnt->num = int_val("Enter the number:");
    prev->next=pnt;
    while(1)
    {
        int answ = int_val("Do you want to continue?(no-0; yes-another digit)");
        if(answ==0){
            break;
        }
        pnt = (list*) malloc(sizeof(list));
        pnt->num = int_val("Enter the number:");
        prev->next = pnt;
        prev = pnt;
    }
    pnt->next = NULL;
    return head;
}

void show(list* head, const char* prompt)
{
    list* pnt = head;
    printf("%s", prompt);
    while (pnt) {
        printf("\nNumber: %d", pnt->num);
        pnt = pnt->next;
    }
}

list* final(list* head){
    list *pnt = head;
    while(pnt){
        if((pnt->next->next) == NULL){
            list* new_h = pnt->next;
            new_h->next = head;
            pnt->next = NULL;
            return new_h;
        }
        else pnt = pnt->next;
    }
}

list * merge(list* head1, list* head2){
    list *pnt = head1;
    while(pnt){
        if((pnt->next)==NULL){
            pnt->next= head2;
            return final(head1);
        }
        else pnt = pnt->next;
    }
}

void task(){
    printf("Enter elements for the first list\n");
    list* head1=create();
    printf("\nEnter elements for the second list\n");
    list* head2=create();
    show(head1, "\nFirst list:");
    show(head2, "\n\nSecond list:");
    list *merge_h=merge(head1, head2);
    show(merge_h, "\n\nFinal list:");
    int ans = int_val("\nDo you want to continue?(1-yes/0-no):");
    if (ans == 1) {
        system("cls");
        return task();
    }
    else{
        free(head1);
        free(head2);
        free(merge_h);
    }
}
int main() {
    frame();
    task();
    return 0;
}

