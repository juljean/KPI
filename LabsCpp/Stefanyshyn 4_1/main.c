#include <stdio.h>
#include <Windows.h>
#define str1 " Laboratory 4"
#define str2 " Task 1"
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

int int_val(const char *prompt){
    int inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &inp)) {
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

float float_val(const char *prompt, float *arr, int size,int i,int j){
    float inp = 0;
    while (1) {
        printf("%s", prompt);
        if (scanf("%f", &*(arr +i*size+ j))) {
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
void fill(float *arr,int size){
    for(int i=0; i<size; i++){
        for (int j=0; j<size;j++){
            float_val("Enter the element: ", arr, size, i, j);
        }
    }
}
void random(float *arr,int size) {
    getchar();
    for (int i=0; i<size; i++) {
        for (int j = 0; j < size; j++) {
            *(arr+i*size+j) = rand() % 200 - 100;
        }
    }
}
void print_ar(float *arr,int size, const char *prompt){
    printf("%s\n", prompt);
    for(int i=0; i<size; i++){
        for (int j=0; j<size;j++){
            printf("%.3f ",*(arr+i*size+j));
        }
        printf("\n");
    }
}

void input(float *arr,int size){
    int choice;
    printf("Do you want to enter values manually?('1'-yes):");
    scanf("%d",&choice);
    if (choice==1){
        fill(arr,size);
        print_ar(arr,size, "Your matrix is:");
    }
    else{
        random(arr,size);
        print_ar(arr,size, "Your matrix is:");
    }
}

void task(){
    setbuf(stdout, 0);
    int ans;
    float arr[100][100], *arr_p;
    arr_p=&arr[0][0];
    int size = -1;
    while (size < 0){
        size=int_val("Enter the size of square matrix(non-negative):");
    }
    input(arr_p, size);
    printf("Your new matrix is:\n");
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i == 0) printf("%.3f ", *(arr_p + (size - 1 - j) * size));
            else if(j == 0) printf("%.3f ", *(arr_p + (size - 1) * size + i));
            else if(i == size - 1) printf("%.3f ", *(arr_p + (size - 1 - j)* size + size - 1));
            else if(j == size - 1) printf("%.3f ", *(arr_p + i));
            else printf("%.3f ",*(arr_p+i*size+j));
        }
        printf("\n");
    }

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
