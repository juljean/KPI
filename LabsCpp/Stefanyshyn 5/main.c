#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <math.h>
#define str1 " Laboratory 5"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "TOPIC: USER-DEFINED DATA TYPES"
#define str5 "KM-91"
#define str6 "Nazar Stefanyshyn"
#define str7 "Kyiv 2020"

int amount =  5;
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

typedef struct{
    char item[50];
    char shop[50];
    int it_price;
} PRICE[5] ;

PRICE curr;

int word_len(char spot[5]){
    int count = 0;
    int maxs = 0;
    if (strcmp(spot, "item") == 0){
        for(int i = 0; i < amount; i++) {
            if (strlen(curr[i].item) > maxs) {
                count = strlen(curr[i].item);
                if(count > maxs) maxs = count;
            }
        }
    }
    else{
        for(int i = 0; i < amount; i++) {
            if (strlen(curr[i].shop) > maxs) {
                count = strlen(curr[i].shop);
                if(count>maxs) maxs=count;
            }
        }
    }
    return  maxs;
}

int price_len(){
    int count = 0;
    for(int i = 0; i < amount; i++) {
        int price = curr[i].it_price;
        while(price)
        {
            price = price/10;
            count++;
        }
    }
    return count;
}

void sort(){
    for (int i = 0; i < amount; i++) {
        for (int j = i + 1; j < amount; j++) {
            if (strcmp(curr[i].shop, curr[j].shop) > 0) {
                PRICE tmp;
                tmp[0] = curr[i];
                curr[i] = curr[j];
                curr[j] = tmp[0];
            }
        }
    }
}

void top(int max1, int max2,int max3, int line){
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

void fill(int max1, int max2, int max3, int line){
    for(int i = 0 ; i<amount; i++) {
        printf("\263%s", curr[i].item);
        for(int k = 0;k < max1 - strlen(curr[i].item) + 1;k++)
            printf(" ");
        printf("\263%s", curr[i].shop);
        for(int k = 0;k < max2 - strlen(curr[i].shop) + 1;k++)
            printf(" ");

        printf("\263%d", curr[i].it_price);
        for(int k = 0;k < max3 - floor(log10(abs( curr[i].it_price))); k++)
            printf(" ");

        printf("\263");

        if(i!= amount - 1) {
            separator(max1, max2, line);
        }
    }
}

void output(const char *prompt) {
    int max1 = max(word_len("item"), strlen("item"));
    int max2 = max(word_len("shop"), strlen("shop"));
    int max3 = max(price_len(), strlen("price"));
    int line = max1 + max2 + max3 + 6;
    printf("%s", prompt);
    top(max1, max2, max3, line);
    separator(max1, max2, line);
    fill(max1, max2, max3, line);
    bottom(max1, max2, line);
}

void task(){
    char want[50];
    int exist = 0;

    for(int i=0; i<amount; i++)
    {
        printf("Enter the item:");
        scanf("%s",curr[i].item);
        printf("Enter the shop:");
        scanf("%s",curr[i].shop);
        curr[i].it_price = int_val("Enter the price:");
    }
    output("Start data:\n");
    sort();
    output("Sorted by the shop data:\n");
    printf("Enter the item you're interested in:");
    gets(want);
    for (int k=0; k < amount; k++){
        if (strcmp(curr[k].item, want) == 0 ){
            exist += 1;
            printf("Item:%s \t Shop: %s \t Price: %d \n", curr[k].item, curr[k].shop,curr[k].it_price);}
    }
    if (!exist)
        printf("There is not such item\n");

    int ans = int_val("Do you want to continue?(1-yes/0-no):");
    if (ans == 1) {
        system("cls");
        return task();
    }
    else
        exit(0);
}

int main() {
    setbuf(stdout, 0);
    frame();
    task();
    return 0;
}