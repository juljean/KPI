#include <stdio.h>
#include <windows.h>
#define str1 " Laboratory 3"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "TOPIC: SYMBOL DATA PROCESSING"
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
    spot(17, 4);
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
void task1(){
    setbuf(stdout, 0);
    int ans;
    char last[100] = " ";
    char * pch;
    char str[1000];
    printf("Enter the text:");
    gets(str);
    printf("Your text is: %s\n", str);
    pch = strtok (str," ");
    while (pch != NULL)
    {
        for(int i = 0; i < strlen(pch); i++){
            if(pch[i] == '.'){
                char buf[] = " ";
                int end = i;
                memcpy(buf, &pch[0], end);
                buf[end] = '\0';
                strcat(last, buf);
                strcat(last, " ");
            }
        }
        pch = strtok (NULL, " ");
    }
    printf("Last words are: %s\n",last);

    printf("\nDo you want to continue?(If yes - enter '1'):");
    scanf("%d", &ans);
    if (ans==1){
        system("cls");
        fflush(stdin);
        task1();
    }
    else
        exit(0);
}
int main ()
{
    frame();
    task1();
    return 0;
}
