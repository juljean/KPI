#include <stdio.h>
#include <windows.h>
#define str1 " Laboratory 1"
#define str2 " Task 2"
#define str3 "Variant 18"
#define str4 "BIT OPERATIONS"
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
    spot(21, 4);
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

float float_val(const char *prompt){
    float inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &inp)) {
            if (getchar() == '\n'){
                if (inp >=0) return inp;
                else {
                    printf("WRONG VALUE\n");
                    return float_val(prompt);
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
int hex_val(const char *prompt){
    int inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%x", &inp)) {
            if (getchar() == '\n')
                return inp;
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

int valid_range(int bot_val, int up_val, const char *prompt){
    int val = int_val(prompt);
    if (val >= bot_val && val <= up_val)
        return val;
    else{
        printf("WRONG VALUE\n");
        valid_range(bot_val, up_val, prompt);
    }
}

void packing(){
    unsigned char x; //horizontal coord
    unsigned char y; //vertical coord
    unsigned char c; // color
    unsigned int point;

    x=valid_range(0,63,"Enter horizontal coordinate (0 - 63): ");
    y=valid_range(0, 63, "Enter vertical coordinate (0 - 63): ");
    c=valid_range(0, 15,"Enter a color (0 - 15): ");

    point = ((unsigned int)x & 0x3f) << 10;
    point |= ((unsigned int)y & 0x3f) << 4;
    point |= ((unsigned int)c & 0x0f);

    printf("\nThe point format = %04x\n", point);
}

void unpacking(){
    unsigned char x; //horizontal coord
    unsigned char y; //vertical coord
    unsigned char c; // color
    unsigned int point;

    point= hex_val("The point format:\n");

    x = (point >> 10) & 0x3f;
    y = (point >> 4) & 0x3f;
    c = (point >> 0) & 0x0f;

    printf("Horizontal coordinate  = %d\n", x);
    printf("Vertical coordinate = %d\n", y);
    printf("Color =  %d\n", c);
}

void menu(){
    int task_num= int_val("Enter the number of task:");
    while (task_num!=1 && task_num!=2){
        printf("WRONG VALUE(ENTER 1 OR 2)\n");
        task_num= int_val("Enter the number of task:");
    }
    switch (task_num) {
        case 1:
            packing();
            break;
        case 2:
            unpacking();
            break;
    }
    int ans;
    printf("\nDo you want to continue?(If yes - enter '1', no - ``else key``):");
    scanf("%d", &ans);
    if (ans==1){
        system("cls");
        menu();
    }
}
int main() {
    frame();
    printf("          MENU\n");
    printf("TASK 1: PACKING\n");
    printf("TASK 2: UNPACKING\n");
    menu();
    return 0;
}
