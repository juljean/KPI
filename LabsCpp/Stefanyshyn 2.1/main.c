#include <stdio.h>
#include <windows.h>
#define str1 " Laboratory 2"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "1-D ARRAYS"
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
void random(float arr[80], int len) {
    getchar();
    for (int i = 0; i < len; i++) {
        arr[i] = rand() % 200 - 100;
    }
}

void fill(float arr[80], int len) {
    for (int i=0; i<len; i++){
        arr[i]=float_val("Enter the element:");}
}

void print_ar(float arr[80], int len, const char *prompt){
    printf("%s\n", prompt);
    for (int i=0; i<len; i++){
        printf("%.3f ", arr[i]);
    }
}

void input(float arr[80], int len){
    int choice;
    printf("Fill array manually - 1\nFill array automatically - ``else key``:");
    scanf("%d",&choice);
    if (choice==1){
        fill(arr, len);
        print_ar(arr,len,"You array is:");
    }
    else{
        random(arr, len);
        print_ar(arr,len,"You array is:");
    }
}

void bubble_sort(float arr[100], int size){
    for(int i = 0; i < size; i++ ){
        for (int j = (size - 1); j > i; j--){
            if (arr[j -1] > arr[j]){
                float temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

void menu(){
    int ans;
    int task_num;
    float first_ar[80], sec_ar[80];
    task_num=int_val("Choose the task:");
    while (task_num!=1 && task_num!=2){
        printf("WRONG VALUE(ENTER 1 OR 2)\n");
        task_num=int_val("Choose the task:");
    }
    int size=int_val("Enter the size of array:");
    input(first_ar, size);
    switch (task_num) {
        case 1:
            for (int i=0;i<size;i++){
                sec_ar[i]=first_ar[i];
            }
            bubble_sort(sec_ar ,size);
            float maxel=sec_ar[size-1];
            float minel=sec_ar[0];
            printf("\nArray B is:\n");
            for (int i=0; i<size; i++){
                printf("%.3f ", first_ar[i]);
                if(first_ar[i]==maxel && i < size -1){
                    i++;
                    while (first_ar[i]!=minel){
                        if (first_ar[i] == 0) i++;
                        else{
                            printf("%.3f ", first_ar[i]);
                            i++;
                        }
                    }
                    printf("%.3f ", first_ar[i]);
                }
                else if(first_ar[i]==minel && i < size -1){
                    i++;
                    while (first_ar[i]!=maxel){
                        if (first_ar[i] == 0) i++;
                        else{
                            printf("%.3f ", first_ar[i]);
                            i++;
                        }
                    }
                    printf("%.3f ", first_ar[i]);
                }
            }
            break;
        case 2:
            bubble_sort(first_ar, size);
            print_ar(first_ar, size, "\nSorted array a is:");
            break;
    }
    printf("\nDo you want to continue?(If yes - enter '1'):");
    scanf("%d", &ans);
    if (ans==1){
        system("cls");
        menu();
    }
    else
        exit(0);
}

int main() {
    frame();
    printf("          MENU\n");
    printf("TASK 1: MODIFYING ARRAY A\n");
    printf("TASK 2: SORTING ARRAY A\n");
    menu();
    return 0;
}
