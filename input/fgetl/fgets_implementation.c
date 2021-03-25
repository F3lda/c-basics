#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fgets2(char *str, int array_size, FILE *stream) // char *
{
    int i;
    for(i = 0; i < array_size-1; i++){
        if(fscanf(stream, "%c", &str[i]) != 1){ /* You can use any of them to get one Char from STDIN: scanf("%c"); fscanf(stdin, "%c"); getc(stdin); getchar(); fgetc(stdin); fgetchar(); */
            return 0; // return NULL;
        }
        if(str[i] == '\n'){
            str[++i] = '\0';
            return i; // return str;
        }
    }
    str[i] = '\0';
    return i; // return str;
}

int main()
{
    printf("Function 'fgets()' implementation:\n");
    
    char strtmp[10];
    printf("Type string: ");
    printf("<%d>", fgets2(strtmp, sizeof(strtmp), stdin));
    printf("<%d>\n<%s>\n", strlen(strtmp), strtmp);

    printf("Type string: ");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>\n", strtmp);

    printf("Type string: ");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>\n", strtmp);
    
    return 0;
}