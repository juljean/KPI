#include <stdio.h>
#include <string.h>
#include <windows.h>
#define str1 " Laboratory 8"
#define str2 " Task 1"
#define str3 "Variant 18"
#define str4 "TOPIC: TEXT FILE"
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

void new_file(char* file_name){
    char text[1000];
    FILE *fp = fopen(file_name, "w");
    if(fp == NULL){
        printf("Error in opening file!\n");
        return;
    }
    getchar();
    printf("Input a text for the file\n");
    fgets(text, sizeof(text), stdin);
    fprintf(fp, "%s", text);
    fclose(fp);
    printf("File created\n");
}

void open(char* file_name){
    FILE *fp;
    char text[1000];
    int lno = 1;
    fp = fopen (file_name, "r");
    if (fp == NULL)
    {
        printf(" File does not exist or cannot be opened.\n");
        return;
    }
    printf("\nThe content of the file %s is  :\n",file_name);
    fgets(text, 128, fp);
    while (fgets(text, 128, fp))
    {
        printf ("%d.%s",lno, text);
        lno++;
    }
    fclose(fp);
    printf("\n");
}

void add(char* file_name){
    FILE * fp;
    char str[100];
    fp = fopen(file_name, "a");
    if (fp == NULL)
    {
        printf(" File does not exist or cannot be opened.\n");
        return;
    }
    printf("The line you want to add: \n");
    fgets(str, sizeof str, stdin);
    fputs(str, fp);
    fclose (fp);
    printf("Line added\n");
}

void view(char* file_name){
    FILE * fp;
    char text[1000];
    fp = fopen (file_name, "r");
    int lno = 1;
    if (fp == NULL)
    {
        printf(" File does not exist or cannot be opened.\n");
        return;
    }
    printf("\nThe content of the file %s is:\n",file_name);
    fgets(text, 128, fp);
    while (fgets(text, 128, fp))
    {
        printf ("%d.%s",lno, text);
        lno++;
    }
    fclose (fp);
}

void correct(char* file_name){
    FILE *fp1, *fp2;
    int lno, linectr = 0;
    char str[256];
    char newln[256], temp[] = "temp.txt";
    fp1 = fopen(file_name, "r");
    if (!fp1)
    {
        printf("Unable to open the input file!!\n");
        return;
    }
    fp2 = fopen(temp, "w");
    if (!fp2)
    {
        printf("Unable to open a temporary file to write!!\n");
        fclose(fp1);
        return;
    }
    printf("Input the content of the new line: ");
    fgets(newln, 256, stdin);

    lno = int_val("Input the number of line you want to replace : ");
    lno++;

    while (!feof(fp1))
    {
        strcpy(str, "\0");
        fgets(str, 256, fp1);
        if (!feof(fp1))
        {
            linectr++;
            if (linectr != lno)
            {
                fprintf(fp2, "%s", str);
            }
            else
            {
                fprintf(fp2, "%s", newln);
            }
        }
    }
    fclose(fp1);
    fclose(fp2);
    remove(file_name);
    rename(temp, file_name);
    printf(" Replacement did successfully..!! \n");
}

void delete(char *file_name){
    FILE *fp1, *fp2;
    int change_line = -1;
    char str[256], temp[] = "temp.txt";
    int ctr = 0;
    fp1 = fopen(file_name, "r");
    if(fp1){
        fp2 = fopen(temp, "w");
        if (!fp2){
            printf("Unable to open a temporary file to write!!\n");
            fclose(fp1);
            return;
        }
        while (change_line <= 0){
            change_line = int_val("Enter the number of string you want to delete:\n");
        }
        change_line++;
        while(!feof(fp1)){
            strcpy(str, "\0");
            fgets(str, 256, fp1);
            if(!feof(fp1)){
                ctr++;
                if(ctr != change_line) fprintf(fp2, "%s", str);
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
}

void save(char *file_name){
    FILE *fp = fopen(file_name, "r");
    fclose(fp);
    printf("File saved..!! \n");
}

void save_as(char *file_name){
    char new_name[256];
    printf("Enter the new name of the file:");
    scanf("%s", new_name);
    rename(file_name, new_name);
    printf("File saved..!! \n");
}

void nonrepeat(char *file_name){
    char new_name[256];
    int i = 0, j = 0, k, length;
    printf("Enter the new name of the file where to copy strings:");
    scanf("%s", new_name);
    FILE * fp1, * fp2;
    char string[1000];
    fp1 = fopen (file_name, "r");
    fp2 = fopen (new_name, "a+");

    while (fgets(string, 128, fp1)) {
        int flag = 0;
        char words[100][100];
        for(k=0; string[k]!='\0'; k++){
            if(string[k] != ' ' && string[k] != '\0'){
                words[i][j++] = tolower(string[k]);
            }
            else{
                words[i][j] = '\0';
                i++;
                j = 0;
            }
        }
        length = i+1;

        for(i = 0; i < length; i++){
            for(j = i+1; j < length; j++){
                if(strcmp(words[i], words[j]) == 0 && (strcmp(words[j],"0") != 0)){
                    flag = 1;
                }
            }
        }
        if (flag != 1) fprintf(fp2, "%s", string);
    }
    printf("Done \n");
    fclose(fp1);
    fclose(fp2);
}
void vowels(char *file_name){
    char sent1[1000];
    int c = 0, count = 0;
    char * pch;

    FILE *fp = fopen(file_name, "r");
    fgets(sent1, 128, fp);

    pch = strtok(sent1, ".");
    while (pch[c] != '\0') {
        if (pch[c] == 'a' || pch[c] == 'A' || pch[c] == 'e' || pch[c] == 'E' || pch[c] == 'i' || pch[c] == 'I' || pch[c] =='o' || pch[c]=='O' || pch[c] == 'u' || pch[c] == 'U')
            count++;
        c++;
    }

    printf("Number of vowels in the string: %d\n", count);
    fclose(fp);
}

void menu(){
    int choice;
    //default file
    char file_name[256] = "testfile";
    while(1)
    {
        puts("        Menu");
        puts("1 - New file");
        puts("2 - Open file");
        puts("3 - Add to the file");
        puts("4 - View the file");
        puts("5 - Correct a file");
        puts("6 - Delete a string");
        puts("7 - Save a file");
        puts("8 - Save a file as");
        puts("9 - Close a file");
        puts("10 - Copy to file 2 strings with non-repated words");
        puts("11 - Find an amount of vowel in first line");
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
            case 7: save(file_name); break;
            case 8: save_as(file_name); break;
            case 9: save(file_name); break;
            case 10: nonrepeat(file_name); break;
            case 11: vowels(file_name); break;
            case 0: exit(0);
            default: puts("Incorrect!");
        }
    }
}

int main() {
    frame();
    menu();
    return 0;
}
