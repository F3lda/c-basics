#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getl_v3(char *buffer, int array_size, FILE *stream) // getline() using fscanf("%c")
{
    if(buffer == NULL){return -1;}
    if(array_size <= 1){return -2;}
    if(stream == NULL){return -3;}
    buffer[0] = '\0';
    char ctemp = '\0';
    int i = 0, result = 0;
    while((result = fscanf(stream, "%c", &ctemp)) == 1 && ctemp != '\n' && i < array_size-1){buffer[i] = ctemp; i++; buffer[i] = '\0';}
    if(result != 1){if(result == EOF) return -4; else if(result == 0) return -5; else return -6;}
    if(i == array_size-1 && ctemp != '\n'){i = array_size;}
    while(ctemp != '\n' && fscanf(stream, "%c", &ctemp) == 1){}
    return i == array_size;
}

int main()
{
    char output[10];
    int result;
    while((result = getl_v3(output, sizeof(output), stdin)) >= 0 && strcmp(output, "exit") != 0){
        printf("<%s>", output);
        if(result == 0){
            printf(" - OK");
        } else {
            printf(" - OVERFLOW");
        }
        printf("\n");
    }
    printf("Done! <res:%d>\n", result);
}