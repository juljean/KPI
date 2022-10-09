#include <stdio.h>
#include <Windows.h>
#include <math.h>
#define str1 " Laboratory 4"
#define str2 " Task 2"
#define str3 "Variant 18"
#define str4 "TOPIC: POINTERS, FUNCTION, RECURSION"
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
    spot(x1, y1);//upper line
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
        printf("\263"); //right side
        spot(x2, i);
        printf("\263");//left side
    }

    spot(x1, y2); //bottom line
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
    spot(12, 4);
    puts(str4);
    spot(25, 5);
    puts(str5);
    spot(20, 6);
    puts(str6);
    spot(23, 9);
    puts(str7);
    printf("\n");
}
//int int_val(const char *prompt){
//    int inp = 0;
//    while (1) {
//        printf("%s", prompt);
//        if (scanf("%d", &inp)) {
//            if (getchar() == '\n') {
//                if (inp >= 0) return inp;
//                else {
//                    printf("WRONG VALUE\n");
//                    return int_val(prompt);
//                }
//            }
//            else
//            {
//                while (getchar() != '\n');
//                printf("WRONG VALUE\n");
//            }
//        }
//        else {
//            while (getchar() != '\n');
//            printf("WRONG VALUE\n");
//        }
//    }
//}

float float_val(const char *prompt){
    float inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &inp)) {
            if (getchar() == '\n'){
                return inp;
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

double eps = 0.0001;

float func(float x){
    return (cos(2/x) - 2*sin(1/x) + 1/x);
}

double recur (double x0, double x1){
    double x = (x0 + x1)/2;
    double f = func(x);
    if (fabs(x1 - x0) < eps || f == 0) return x;
    else{
        if (f > 0) return recur(x0, x);
        else return recur(x, x1);
    }
}
void task() {
    int ans;
    int x0 = 1;
    int x1 = -1;
    while (x0 >= -5) {
        x0 = float_val("Enter the bottom bound of approximation(<-5):");
    }
    while (x1 <= 5) {
        x1 = float_val("Enter the upper bound of approximation(>5):");
    }
    printf("Your answer is %f", recur(x0, x1));
    printf("\nDo you want to continue?(If yes - enter '1'):");
    scanf("%d", &ans);
    if (ans==1){
        system("cls");
        task();
    }
    else
        exit(0);
}
int main() {
    frame();
    task();
    return 0;
}
