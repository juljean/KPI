#include <stdio.h>
#include <windows.h>
#define str1 " Laboratory 2"
#define str2 " Task 2"
#define str3 "Variant 18"
#define str4 "2-D ARRAYS"
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
    spot(23, 4);
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
void random(float arr[80][80], int len) {
    getchar();
    for (int i=0; i<len; i++) {
        for (int k = 0; k < len; k++) {
            arr[i][k] = rand() % 200 - 100;
        }
    }
}
void fill(float arr[80][80], int len) {
    for (int i=0; i<len; i++){
        for(int k=0; k<len;k++){
            arr[i][k]=float_val("Enter the element:");
        }
    }
}
void print_ar(float arr[80][80], int len, const char *prompt){
    printf("%s\n", prompt);
    for (int i=0; i<len; i++){
        for(int k=0; k<len;k++){
            printf("%.3f ", arr[i][k]);
            if (k==len - 1){
                printf("\n");
            }
        }
    }
}

void input(float arr[80][80], int len){
    int choice;
    printf("Do you want to enter values manually?('1'-yes):");
    scanf("%d",&choice);
    if (choice==1){
        fill(arr, len);
        print_ar(arr, len, "You matrix is:");
    }
    else{
        random(arr, len);
        print_ar(arr, len, "You matrix is:");
    }
}
void task(){
    int ans;
    float arr[80][80];
    int size=int_val("Enter the size of square matrix(EVEN NUMBER):");
    if(size%2 != 0){
        printf("The size is not even\n");
        task();
    }
    input(arr, size);
    int marker = size/2;
    for (int i = 0; i < marker; i++){
        for (int j = 0; j < marker; j++){
            float buf = arr[i][j];
            arr[i][j] = arr[i + marker][j];
            arr[i + marker][j] = arr[i + marker][j + marker];
            arr[i + marker][j + marker] = arr[i][j + marker];
            arr[i][j + marker] = buf;
        }

    }
    print_ar(arr, size, "New matrix is");
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
