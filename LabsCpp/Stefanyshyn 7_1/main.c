#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <windows.h>
#include <math.h>
#define str1 " Laboratory 7"
#define str2 " Task 2"
#define str3 "Variant 18"
#define str4 "TOPIC: SINGLY-LINKED LIST"
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

int int_val(const char* prompt) {
    int integint;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &integint)) {
            if (getchar() == '\n')
            {
                if (integint>=0) return integint;
                else return int_val("Numbers in this range are not available.\n Enter new number:");
            }
            else
            {
                while (getchar() != '\n');
                printf("You entered wrong value, try again.\n");
            }
        }
        else {
            while (getchar() != '\n');
            printf("You entered wrong value, try again.\n");
        }
    }
}

typedef struct PRICE{
    char item[50];
    char shop[50];
    int it_price;
    struct PRICE* next;
}PRICE;

int word_len(PRICE *head, char spot[5]){
    unsigned int count = 0;
    unsigned int maxs = 0;
    PRICE* pnt = head;
    if (strcmp(spot,"item") == 0){
        while (pnt!=NULL){
            if (strlen(pnt->item) > maxs) {
                count = strlen(pnt->item);
                if(count > maxs)
                    maxs = count;
            }
            pnt = pnt->next;
        }
    }
    else{
        while (pnt!=NULL){
            if (strlen(pnt->shop) > maxs) {
                count = strlen(pnt->shop);
                if(count>maxs) maxs = count;
            }
            pnt = pnt->next;
        }
    }
    return  maxs;
}

int price_len(PRICE *head){
    int count = 0;
    int maxv = 0;
    PRICE *cur = head;
    while(cur){
        int num = cur->it_price;
        while(num)
        {
            num=num/10;
            count++;
        }
        cur = cur->next;
        if (count > maxv) maxv = count;
    }
    return maxv;
}

void top(int max1, int max2, int max3, int line){
    for (int i = 0; i <= line; i++) {
        if (i == 0)
            printf("\332");
        else if(i == line)
            printf("\277");
        else if ((i == max1+2)||(i == max1 + max2 + 4))  printf("\302");
        else printf("\304");}
    printf("\n");

    printf("\263Item");
    for(int k = 0;k < max1 + 1 - strlen("Item");k++)
        printf(" ");

    printf("\263Shop");
    for(int k=0;k < max2 + 1 - strlen("Shop");k++)
        printf(" ");

    printf("\263Price");
    for(int k = 0;k < max3 + 1 - strlen("Price");k++)
        printf(" ");
    printf("\263");
}

void separator(int max1, int max2, int line){
    printf("\n");
    for (int k = 0; k <= line; k++) {
        if (k == 0)
            printf("\303");
        else if (k==line)
            printf("\264");
        else if ((k == max1 + 2)||(k == max1 + max2 + 4))  printf("\305");
        else printf("\304");
    }
    printf("\n");
}

void bottom(int max1, int max2, int line){
    printf("\n");
    for (int i = 0; i <= line; i++) {
        if (i == 0)
            printf("\300"
                   "");
        else if (i==line)
            printf("\331");
        else if ((i == max1 + 2)||(i == max1 + max2 + 4))  printf("\301");
        else
            printf("\304");}
    printf("\n");
}

void fill(int max1, int max2, int max3, int line, PRICE* head){
    PRICE* pnt;
    pnt = head;
    while(pnt != NULL)
    {
        printf("\263%s", pnt->item);
        for(int k=0;k<max1+1-strlen(pnt->item);k++)
            printf(" ");

        printf("\263%s", pnt->shop);
        for(int k=0; k < max2 + 1 - strlen(pnt->shop);k++)
            printf(" ");

        printf("\263%d", pnt->it_price);
        for(int k = 0;k < max3 - floor(log10(abs( pnt->it_price))); k++)
            printf(" ");

        printf("\263");
        pnt = pnt->next;
        if (pnt!=NULL) separator(max1, max2, line);
    }
}

void output(const char *prompt, PRICE* head) {
    int max1 = max(word_len(head, "item"), strlen("item"));
    int max2 = max(word_len(head, "shop"), strlen("shop"));
    int max3 = max(price_len(head), strlen("price"));
    int line = max1 + max2 + max3 + 6;
    printf("%s", prompt);
    top(max1, max2, max3, line);
    separator(max1, max2, line);
    fill(max1, max2,max3, line, head);
    bottom(max1, max2, line);
}
PRICE* create(){
    PRICE *pnt, *prev;
    PRICE* head = prev = pnt = (PRICE*) malloc(sizeof(PRICE));
    printf("Enter the item:");
    gets(pnt->item);
    printf("Enter the shop:");
    gets(pnt->shop);
    pnt->it_price = int_val("Enter the price:");
    prev->next = pnt;
    while(1)
    {
        int answ = int_val("Do you want to continue?(no-0; yes-another digit)");
        if(answ==0){
            break;
        }
        pnt = (PRICE*) malloc(sizeof(PRICE));
        printf("Enter the item:");
        gets(pnt->item);
        printf("Enter the shop:");
        gets(pnt->shop);
        pnt->it_price = int_val("Enter the price:");
        prev->next = pnt;
        prev = pnt;
    }
    pnt->next=NULL;
    return head;
}

PRICE* sort(PRICE *head)
{
    PRICE *a = NULL;
    PRICE *b = NULL;
    PRICE *c = NULL;
    PRICE *e = NULL;
    PRICE *tmp = NULL;

    while(e != head->next)
    {
        c = a = head;
        b = a->next;
        while(a != e)
        {
            if(strcmp(a->shop, b->shop) > 0)
            {
                if(a == head)
                {
                    tmp = b -> next;
                    b->next = a;
                    a->next = tmp;
                    head = b;
                    c = b;
                }
                else
                {
                    tmp = b->next;
                    b->next = a;
                    a->next = tmp;
                    c->next = b;
                    c = b;
                }
            }
            else
            {
                c = a;
                a = a->next;
            }
            b = a->next;
            if(b == e)
                e = a;
        }
    }
    output("Sorted by shop structure\n", head);
    return head;
}

PRICE* add_head(PRICE *head){
    PRICE *pnt = head;
    PRICE *tmp = (PRICE*)malloc(sizeof(PRICE));

    printf("Enter the item:");
    gets(tmp->item);
    printf("Enter the shop:");
    gets(tmp->shop);
    tmp->it_price = int_val("Enter the price:");

    tmp->next = head;
    return tmp;
}

PRICE* add_tail(PRICE *head){
    PRICE *pnt = head;
    PRICE *tmp = (PRICE*)malloc(sizeof(PRICE));

    printf("Enter the item:");
    gets(tmp->item);
    printf("Enter the shop:");
    gets(tmp->shop);
    tmp->it_price = int_val("Enter the price:");

    tmp->next = NULL;
    while (pnt){
        if(pnt->next == NULL){
            pnt->next = tmp;
            return head;
        }
        else
            pnt = pnt->next;
    }
}

PRICE* add_number(PRICE *head){
    int count=0;
    PRICE *pnt=head;
    PRICE *tmp=(PRICE*)malloc(sizeof(PRICE));

    printf("Enter the item:");
    gets(tmp->item);
    printf("Enter the shop:");
    gets(tmp->shop);
    tmp->it_price = int_val("Enter the price:");

    PRICE *newh =pnt;
    int el=int_val("Enter the number of element after which you want to add a node:");
    while (pnt){
        count+=1;
        if (count==el){
            PRICE* buf=pnt->next;
            pnt->next=tmp;
            tmp->next=buf;
            return newh;
        }
        else
            pnt = pnt->next;
    }
    printf("Your entered too big value\n");
    return add_number(head);

}
PRICE* add_key(PRICE *head){
    PRICE *pnt=head;
    PRICE *tmp=(PRICE*)malloc(sizeof(PRICE));

    printf("Enter the item:");
    gets(tmp->item);
    printf("Enter the shop:");
    gets(tmp->shop);
    tmp->it_price = int_val("Enter the price:");

    PRICE *newh = pnt;
    char key[30] = "";
    int ans = int_val("What will be a key(item - 1; shop - 2; price - 3): ");
    switch (ans){
        case 1:{
            printf("Enter the key: ");
            gets(key);
            while (pnt != NULL){
                if (strcmp(pnt->item, key)==0){
                    PRICE* buf=pnt->next;
                    pnt->next=tmp;
                    tmp->next=buf;
                    return newh;
                } else
                    pnt = pnt->next;
            }
            printf("Your entered nonexistent key \n");
            return add_key(head);
        }
        case 2:{
            printf("Enter the key: ");
            gets(key);
            while ((pnt)!=NULL){
                if (strcmp(pnt->shop, key) == 0){
                    PRICE* buf=pnt->next;
                    pnt->next=tmp;
                    tmp->next=buf;
                    return newh;
                }
                else
                    pnt = pnt->next;
            }
            printf("Your entered nonexistent key \n");
            return add_key(head);
        }
        case 3:{
            int key_n=check_int("Enter the key: ");
            while ((pnt)!=NULL){
                if (pnt->it_price == key_n){
                    PRICE* buf=pnt->next;
                    pnt->next=tmp;
                    tmp->next=buf;
                    return newh;
                }
                else
                    pnt = pnt->next;
            }
            printf("Your entered nonexistent key \n");
            return add_key(head);
        }
        default:
            printf("Choose something from menu:");
            return add_key(head);
    }
}

PRICE *delete_head(PRICE *head){
    PRICE *pnt = head;
    head=head->next;
    free(pnt);
    return head;
}

PRICE *delete_tail(PRICE *head){
    PRICE *pnt = head;
    PRICE * buf = NULL;
    while (pnt->next) {
        buf = pnt;
        pnt = pnt->next;
    }
    if (buf == NULL)
        return buf;
    else{
        free(pnt);
        buf->next = NULL;
        return head;
    }
}

PRICE * delete_number(PRICE *head){
    int count = 0;
    PRICE *pnt = head;
    int el = int_val("Enter the number of element after which you want to delete a node:");
    while (pnt->next){
        count += 1;
        if (count == el){
            PRICE* buf = pnt->next->next;
            free(pnt->next);
            pnt->next = buf;
            return head;
        }
        else
            pnt = pnt->next;
    }
    printf("Your entered too big value\n");
    return delete_number(head);
}

PRICE * delete_key(PRICE *head){
    PRICE *pnt=head;
    char key[30] = "";
    int ans = int_val("What will be a key(item - 1; shop - 2; price - 3): ");
    switch (ans) {
        case 1: {
            printf("Enter the key: ");
            gets(key);
            while (pnt->next) {
                if (strcmp(pnt->item, key) == 0) {
                    PRICE *buf = pnt->next->next;
                    free(pnt->next);
                    pnt->next = buf;
                    return head;
                } else
                    pnt = pnt->next;

            }
            printf("Your entered nonexistent key or there is no nodes after this element\n");
            return delete_key(head);
        }

        case 2: {
            printf("Enter the key: ");
            gets(key);
            while (pnt->next) {
                if (strcmp(pnt->shop, key) == 0) {
                    PRICE *buf = pnt->next->next;
                    free(pnt->next);
                    pnt->next = buf;
                    return head;
                } else
                    pnt = pnt->next;
            }
            printf("Your entered nonexistent key or there is no nodes after this element \n");
            return delete_key(head);
        }

        case 3: {
            int key_n = int_val("Enter the key: ");
            while (pnt->next) {
                if (pnt->it_price == key_n) {
                    PRICE *buf = pnt->next->next;
                    free(pnt->next);
                    pnt->next = buf;
                    return head;
                } else
                    pnt = pnt->next;
            }
            printf("Your entered nonexistent key or there is no nodes after this element\n");
            return delete_key(head);
        }

        default:
            printf("Choose something from menu\n");
            return delete_key(head);
    }
}

void show_menu(){
    printf("  Menu of modifying structure\n");
    printf("1. Add a head-node\n");
    printf("2. Add an end-node\n");
    printf("3. Add a node after an element number... \n");
    printf("4. Add a node after an element with key... \n");
    printf("5. Delete a head-node\n");
    printf("6. Delete an end-node\n");
    printf("7. Delete a node after an element number... \n");
    printf("8. Delete a node after an element with key... \n");
    printf("9. Sorting a list by the number of route\n");
    printf("10. Exit a program\n");
    printf("11. Show the menu\n");
}

void menu(PRICE *head){
    int choice = int_val("Enter your choice(11 to show the menu): ");
    switch (choice){
        case 1:{
            head = add_head(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 2:{
            head = add_tail(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 3:{
            head = add_number(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 4:{
            head = add_key(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 5:{
            if (head == NULL){
                printf("The list is empty, you can't delete anything\n");
                menu(head);
            }
            head = delete_head(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 6:{
            if (head == NULL){
                printf("The list is empty, you can't delete anything\n");
                menu(head);
            }
            head = delete_tail(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 7:{
            if (head == NULL){
                printf("The list is empty, you can't delete anything\n");
                menu(head);
            }
            head = delete_number(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 8:{
            if (head == NULL){
                printf("The list is empty, you can't delete anything\n");
                menu(head);
            }
            head = delete_key(head);
            output("Modified structure\n", head);
            menu(head);
        }

        case 9:{
            head = sort(head);
            menu(head);
        }

        case 10:{
            free(head);
            exit(0);
        }

        case 11:{
            show_menu();
            menu(head);
        }

        default:
            printf("Choose something from menu\n");
            show_menu();
            menu(head);
    }
}

void task(){
    setbuf(stdout,0);
    PRICE* head = create();
    output("Your structure\n",head);
    show_menu();
    menu(head);
    free(head);
}

int main() {
    frame();
    task();
    return 0;
}