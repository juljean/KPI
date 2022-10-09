#include <stdio.h>
#include <windows.h>
#define str1 " Laboratory 6"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "TOPIC: DYNAMIC ARRAYS"
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

void random(float **arr, int row, int col){
    for (int i = 0; i<row; i++)
    {
        for (int k = 0; k<col; k++)
        {
            arr[i][k]= rand() %60-10;
        }
    }
}

void fill(float **arr, int row, int col){
    for(int i=0;i<row;i++){
        for (int k=0;k<col;k++){
            arr[i][k]=float_val("Enter the value: ");
        }
    }
}

void print_ar(float **arr, int row, int column,const char* prompt){
    printf("%s\n",prompt);
    for (int i = 0; i<row; i++)
    {
        for (int k = 0; k<column; k++)
        {
            printf("%.3f ", arr[i][k]);
        }
        printf("\n");
    }
    printf("\n");
}

void menu(float **arr, int row, int column){
    int choice;
    printf("Fill array manually - 1\nFill array automatically - ``else key``:");
    scanf("%d",&choice);
    if (choice==1){
        fill(arr, row, column);
    }
    else{
        random(arr, row, column);
    }
}
void changed(float **arr, int row, int column){
    float min=arr[0][0];
    int min_i = 0;
    int min_k = 0;
    for (int i = 0; i<row; i++)
    {
        for (int k = 0; k<column; k++)
        {
            if (arr[i][k]<min){
                min=arr[i][k];
                min_i = i;
                min_k = k;
            }
        }
    }
    printf("The minimal element is %.3f\n", min);
    free(arr[min_i]);
    row--;
    while(min_i<row)
    {
        //move data up
        arr[min_i] = arr[min_i+1];
        min_i++;
    }

    for (int k = 0; k < row; k++){
        int buf = min_k;
        while(buf < column - 1)
        {
            //move data up
            arr[k][buf] = arr[k][buf + 1];
            buf++;
        }
    }
    column--;
    print_ar(arr, row, column, "\nCHANGED MATRIX\n");
}

void task(){
    int row=int_val("Enter the number of rows:");
    int column=int_val("Enter the number of columns:");

    float **arr = (float**)malloc(row * sizeof(float));

    if(arr == NULL)
    {
        puts("CREATION FAILED\n");
        return task();
    }

    for(int i = 0;i < row; i++ ){
        arr[i]=(float*)malloc(column * sizeof(float));
    }
    menu(arr,row, column);
    print_ar(arr, row, column, "YOUR MATRIX");
    changed(arr,row, column);

    for(int i=0;i < row - 1;i++){
        free(arr[i]);
    }
    free(arr);

    int ans = int_val("Do you want to continue?(1-yes/0-no):");
    if (ans == 1) {
        system("cls");
        return task();
    }
    else
        exit(0);
}
int main() {
    frame();
    task();
    return 0;
}
