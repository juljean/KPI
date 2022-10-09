#include <stdio.h>
#include <math.h>
#include <windows.h>
#define str1 " Laboratory 1"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "INPUT-OUTPUT OPERATIONS"
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

void task1(){
    printf("\nYou choose first task\n");
    float first = float_val("Enter the first number:");
    float second= float_val("Enter the second number:");
    float av_ar = (first + second)/2;
    float av_geom = pow((first * second), 0.5);
    printf( "Arithmetical mean of numbers = %.3f\n", av_ar);
    printf( "Geometrical mean of numbers = %.3f\n", av_geom);
}

void task2(){
    printf("You choose second task\n");
    float side1 = float_val("Enter the first side:");
    float side2 = float_val("Enter the second side:");
    float side3 = float_val("Enter the third side:");
    float volume = side1 * side2 * side3;
    printf("The volume of rectangular parallelepiped = %.3f\n", volume);
}

void menu(){
    int var = int_val("Enter the number of task:");
    if (var == 1){
        task1();
    }
    else if (var == 2){
        task2();
    }
    else{
        printf("You entered wrong number\n");
        menu();
    }
    int ans;
    printf("\nDo you want to continue?(Yes = 1; No = ``else key``):");
    scanf("%d", &ans);
    if (ans==1){
        system("cls");
        menu();
    }
}
int main() {
    frame();
    printf("           Menu\n");
    printf("1.Find arithmetical mean and geometrical mean\n");
    printf("2.Find the volume of rectangular parallelepiped\n");
    menu();
    return 0;
}
