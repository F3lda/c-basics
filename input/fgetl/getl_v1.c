#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getl_v1(char *buffer, int array_size, FILE *stream) // getline() using fscanf()
{
    if(buffer == NULL){
        return -1;
    }
    if(array_size <= 1){
        return -2;
    }
    if(stream == NULL){
        return -3;
    }
    char format[64]; // this should be enough also for unsigned long int
    if(snprintf(format, sizeof(format), "%%%d[^\n]", array_size-1) < 0){ // create scanf format with max chars array_size-1
        return -4;
    }
    char ctemp = '\0';
    buffer[0] = '\0'; // initialize or clear array (not necessary - prevents printing random chars)
    int result = fscanf(stream, format, buffer); // scan string
    fscanf(stream, "%c", &ctemp); // scanning separately because otherwise newline char will stay in STDIN buffer
    if((result == 0 && ctemp == '\n') || result == 1){ // if only newline char was read or OK
        result = 0; // OK
    } else {
        result = -5; // couldn't read string or EOF
    }
    if(ctemp != '\n'){
        if(scanf("%c", &ctemp) == EOF){
            return -6; // EOF
        }
        while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){} // clear STDIN buffer
        return 1; // overflow
    }
    return result;
}

int main()
{
    char strtmp[10];
    printf("Type string: ");
    int res = getl_v1(strtmp, sizeof(strtmp), stdin);
    printf("<res:%d><%s><%d>\n", res, strtmp, strlen(strtmp));

    // check if STDIN buffer is empty
    char strTemp[255];
    printf("Type string:");
    fgets(strTemp, sizeof(strTemp), stdin);
    printf("<%s>", strTemp);
}