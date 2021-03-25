#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getl_v2(char *buffer, int array_size, FILE *stream) // getline() using fgets()
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
    buffer[0] = '\0'; // initialize or clear array (not necessary - prevents printing random chars)
    if(fgets(buffer, array_size, stream) == NULL){ // read ARRAY_SIZE chars from stream
        return -4;
    }
    int lastCharIndex = strlen(buffer)-1; // this index should never go -1 because of newline char
    if(lastCharIndex >= 0){
        if(buffer[lastCharIndex] != '\n'){ // check if newline char was read
            char ctemp;
            if(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){ // check if only newline char stayed in STDIN buffer
                while(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){} // clear STDIN buffer by reading char by char
                //char stemp[array_size]; stemp[0] = '\0';
                //while(fgets(stemp, array_size, stream) != NULL && strchr(stemp, '\n') == NULL){} // clear STDIN buffer by reading with array buffer
                return 1; // overflow
            } else {
                return 0; // OK
            }
        } else {
            buffer[lastCharIndex] = '\0'; // delete newline char
            return 0; // OK
        }
    } else {
        return -5; // index error
    }
    return 0;
}


int main()
{
    char strtmp[10];
    printf("Type string: ");
    int res = getl_v2(strtmp, sizeof(strtmp), stdin);
    printf("<res:%d><%s><%d>\n", res, strtmp, strlen(strtmp));

    // check if STDIN buffer is empty
    char strTemp[255];
    printf("Type string:");
    fgets(strTemp, sizeof(strTemp), stdin);
    printf("<%s>", strTemp);
    
    // in loop
    char output[10];
    int result;
    while((result = getl_v2(output, sizeof(output), stdin)) >= 0){
        if(strcmp(output, "") == 0){ // finish on empty line
            break;
        } else {
            if(result == 0){
                printf("OK - ");
            } else {
                printf("OVERFLOW - ");
            }
            printf("<%s>\n", output);
        }
    }
    printf("Done! <res:%d>\n", result);
}