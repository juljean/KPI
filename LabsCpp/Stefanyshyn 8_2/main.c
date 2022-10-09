#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define str1 " Laboratory 8"
#define str2 " Task 2"
#define str3 "Variant 18"
#define str4 "TOPIC:BINARY FILE"
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
    spot(19, 4);
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

typedef struct{
    char name[100];
    int auto_numb;
    int phone;
    int pas_numb;
    int status;
} auto_owner;

void new_file(char* file_name){
    FILE *fp;
    int ans;
    auto_owner current;
    fp = fopen(file_name, "wb");
    if(fp == NULL){
        printf("Error in opening file!\n");
        return;
    }
    getchar();
    printf("Enter data\n");
    do{
        printf("Name: ");
        gets(current.name);
        current.auto_numb = int_val("Enter the number of auto:");
        current.phone = int_val("Enter the phone number:");
        current.pas_numb = int_val("Enter the number of auto passport:");
        current.status = 0;
        fwrite(&current, sizeof(current), 1, fp);
        ans = int_val("Do you want to end? 0/1");
    }
    while(ans != 0);
    fclose(fp);
}

void open(char* file_name){
    FILE *fp;
    int i = 1;
    auto_owner current;
    fp = fopen(file_name, "rb");
    fread(&current, sizeof(current), 1, fp);
    int mode = 3;
    while (mode != 0 && mode != 1){
        mode = int_val("\"Do you want to see only active files or only passive(1/0)\"");
    }

    while(!feof(fp))
    {
        if (current.status != mode){
            printf("%3dName %s  Number of auto:%d Phone number:%d Number of auto passport:%d Status:%d\n",
               i, current.name, current.phone, current.auto_numb, current.pas_numb, current.status);
            fread(&current, sizeof(auto_owner), 1, fp);
            i++;
        }
    }
}

void view(char* file_name){
    FILE *fp;
    int i = 1;
    auto_owner current;
    fp = fopen(file_name, "rb");
    int mode = 3;
    while (mode != 0 && mode != 1){
        mode = int_val("\"Do you want to see only active files or only passive(0/1)\"");
    }
    while(!feof(fp))
    {
        fread(&current, sizeof(auto_owner), 1, fp);
        if (current.status == mode){
            printf("%d.Name %s  Number of auto:%d Phone number:%d Number of auto passport:%d Status:%d\n",
                   i, current.name, current.auto_numb, current.phone, current.pas_numb, current.status);
            i++;
        }
    }
    fclose(fp);
}

void add(char *file_name){
    FILE *fp;
    int ans;
    auto_owner current;
    fp = fopen(file_name, "ab");
    printf("Enter data:\n");
    do{
        printf("Name: ");
        gets(current.name);
        current.auto_numb = int_val("Enter the number of auto:");
        current.phone = int_val("Enter the phone number:");
        current.pas_numb = int_val("Enter the number of auto passport:");
        current.status = 0;
        fwrite(&current, sizeof(current), 1, fp);
        ans = int_val("Do you want to end? 0/1");
    }
    while(ans != 0);
    fclose(fp);
}

void correct(char *file_name){
    FILE *fp1, *fp2;
    auto_owner current;
    int count = 1;
    char temp[] = "temp.txt";
    int line = int_val("Enter the number of active owner to change his data:");
    fp1 = fopen(file_name, "rb");
    if (!fp1)
    {
        printf("Unable to open the input file!!\n");
        return;
    }
    fp2 = fopen(temp, "wb");
    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp1);
        return;
    }

    int exist = 0;

    while(!feof(fp1))
    {
        if (current.status == 0){
            fread(&current, sizeof(current), 1, fp1);
            if(line == count)
            {
                exist = 1;
                printf("New data\n");
                printf("Enter new name: ");
                gets(current.name);
                current.auto_numb = int_val("Enter the number of auto:");
                current.phone = int_val("Enter the phone number:");
                current.pas_numb = int_val("Enter the number of auto passport:");
                current.status = 0;

                printf("%s", current.name);
                printf(" Number of auto:%d Phone number:%d Number of auto passport:%d Status:%d\n", current.auto_numb, current.phone, current.pas_numb, current.status);
                printf("\n");
                fwrite(&current, sizeof(auto_owner), 1, fp2);
                count++;
                continue;
            }
            fwrite(&current, sizeof(auto_owner), 1, fp2);
            count++;
        }
    }
    if(!exist){
        printf("There is no such structure\n");
    }
    else {
        fclose(fp1);
        fclose(fp2);
        remove(file_name);
        rename(temp, file_name);
        printf(" Replacement did successfully..!! \n");
    }
}

void delete(char *file_name){
    FILE *fp1, *fp2;
    auto_owner current;
    int change_line = -1;
    char temp[] = "temp";
    int count = 1;
    fp1 = fopen(file_name, "rb");
    if(fp1){
        fp2 = fopen(temp, "wb");
        if (!fp2){
            printf("Unable to open a temporary file to write!!\n");
            fclose(fp1);
            return;
        }
        while (change_line <= 0) change_line = int_val("Enter the number of owner which data you want to delete:\n");
        while(!feof(fp1)){
            fread(&current, sizeof(current), 1, fp1);
            if (current.status == 0){
                if(count != change_line){
                    fwrite(&current, sizeof(auto_owner), 1, fp2);
                }
                else{
                    current.status = 1;
                    fwrite(&current, sizeof(auto_owner), 1, fp2);
                }
                count++;
            }
            else{
                fwrite(&current, sizeof(auto_owner), 1, fp2);
            }
        }

    } else{
        printf("File not found\n");
        return;
    }
    fclose(fp1);
    fclose(fp2);
    remove(file_name);
    rename(temp, file_name);
    printf("Deleted\n");
}

void normal_save(char *file_name, char *file_name2){
    auto_owner current;
    FILE *fp1 = fopen(file_name, "rb");
    FILE *fp2 = fopen("temp", "wb");
    if (!fp1)
    {
        printf("Unable to open the input file!!\n");
        return;
    }
    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp1);
        return;
    }
    if (!feof(fp1))
    {
        fread(&current, sizeof(auto_owner), 1, fp1);
        if(current.status == 0) fwrite(&current, sizeof(auto_owner), 1, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    remove(file_name);
    rename("temp", file_name2);
}

void save_plus(char *file_name, char *file_name2){
    auto_owner current;
    FILE *fp1 = fopen(file_name, "rb");
    FILE *fp2 = fopen("temp", "wb");
    if (!fp1)
    {
        printf("Unable to open the input file!!\n");
        return;
    }

    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp1);
        return;
    }
    while(!feof(fp1)){
        fread(&current, sizeof(auto_owner), 1, fp1);
        if(current.status == 0) fwrite(&current, sizeof(current), 1, fp2);
        if(current.status == 1){
            current.status = 0;
            fwrite(&current, sizeof(current), 1, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove(file_name);
    rename("temp", file_name2);
}

void save(char *file_name, char *file_name2){
    int choice;
    puts("1. Save file with compression\n");
    puts("2. Save file without compression\n");
    choice = int_val("Enter your choice:");
    switch (choice){
        case 1:
            normal_save(file_name, file_name2);
            break;
        case 2:
            save_plus(file_name, file_name2);
            break;

        default:
            puts("Incorrect!");
    }
}

void close(char *file_name){
    FILE *fp = fopen(file_name, "rb");
    if (!fp)
    {
        printf("Unable to open the input file!!\n");
        return;
    }
    fclose(fp);
}

void del_passp(char *file_name){
    FILE *fp1, *fp2;
    fp1 = fopen(file_name, "rb");
    auto_owner current;
    if (!fp1)
    {
        printf("Unable to open the input file!!\n");
        return;
    }

    fp2 = fopen("temp", "wb");
    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp2);
        return;
    }

    int pass_numb = int_val("Enter the number of passport:");

    while (!feof(fp1)) {
        fread(&current, sizeof(auto_owner), 1, fp1);
        if(current.pas_numb == pass_numb && current.status == 0){
            current.status = 1;
        }
        fwrite(&current, sizeof(current), 1, fp2);
    }
    fclose(fp1);
    fclose(fp2);
    remove(file_name);
    rename("temp", file_name);
}

void add_two(char *file_name){
    FILE *fp1 = fopen(file_name, "rb");
    auto_owner current;
    char name[256];
    if (!fp1)
    {
        printf("Unable to open the input file!!\n");
        return;
    }

    FILE *fp2 = fopen("temp", "wb");
    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp2);
        return;
    }
    printf("Enter the name:");
    gets(name);
    while (!feof(fp1))
    {
        fread(&current, sizeof(auto_owner), 1, fp1);
        if(strcmp(current.name, name) == 0){
            fwrite(&current, sizeof(current), 1, fp2);
            printf("Enter data\n");
            for (int i = 0; i < 2; i++){
                printf("Name: ");
                gets(current.name);
                current.auto_numb = int_val("Enter the number of auto:");
                current.phone = int_val("Enter the phone number:");
                current.pas_numb = int_val("Enter the number of auto passport:");
                current.status = 0;
                fwrite(&current, sizeof(current), 1, fp2);
            }
        }
        else{
            fwrite(&current, sizeof(current), 1, fp2);
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove(file_name);
    rename("temp", file_name);
}

void menu(){
    int choice;
    //default file
    char file_name[256] = "filebin";
    while(1)
    {
        puts("1 - New file");
        puts("2 - Open file");
        puts("3 - Add to the file");
        puts("4 - View the file");
        puts("5 - Correct a structure");
        puts("6 - Delete a structure");
        puts("7 - Save a file");
        puts("8 - Save a file as");
        puts("9 - Close a file");
        puts("10 - Delete an element with auto-passport...");
        puts("11 - Add 2 elements after structure with surname...");
        puts("0 - Exit");
        choice = int_val("Enter your choice:");

        switch(choice)
        {
            case 1: {
                printf("Input the filename you want to create: ");
                scanf("%s",file_name);
                new_file(file_name);
                break;
            }
            case 2:{
                printf("Input the filename to be opened: ");
                scanf("%s",file_name);
                open(file_name);
                break;
            }
            case 3: add(file_name); break;
            case 4: view(file_name); break;
            case 5: correct(file_name); break;
            case 6: delete(file_name); break;
            case 7: save(file_name, file_name); break;
            case 8: {
                char *file_name2 = "file";
                printf("Enter the name of new file:");
                scanf("%s", file_name2);
                save(file_name, file_name2); break;
            }
            case 9: close(file_name); break;
            case 10: del_passp(file_name); break;
            case 11: add_two(file_name); break;
            case 0: exit(0);
            default: puts("Incorrect!");
        }
    }
}
int main() {
    setbuf(stdout, 0);
    frame();
    menu();
    return 0;
}
