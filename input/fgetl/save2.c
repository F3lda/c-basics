#define STRING_ARRAY_SIZE 102
int getl(char *buffer, int array_size, FILE *stream) // getline() using fgets() with one more char in buffer for NEWLINE_CHAR check
{
    buffer[0] = '\0'; // initialize or clear the OUTPUT array (not necessary - prevents user from accessing random data)
    buffer[STRING_ARRAY_SIZE-2] = '\0';
    if(fgets(buffer, array_size, stream) == NULL){return EOF;} // read ARRAY_SIZE chars from stream
    if(buffer[STRING_ARRAY_SIZE-2] != '\0'){
        char ctemp;
        while(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){} // clear the STREAM buffer by reading it char by char
        return 1; // OVERFLOW
    } else {
        buffer[strcspn(buffer,"\n")] = '\0'; // remove NEWLINE_CHAR
    }
    return 0; // OK
}

int getl_v1(char *buffer, int array_size, FILE *stream) // getline() using fscanf("%[^\n]")
{
    if(buffer == NULL){return -11;}
    if(array_size <= 1){return -12;}
    if(stream == NULL){return -13;}
    char format[64]; // this should be enough also for UNSIGNED LONG INT
    if(snprintf(format, sizeof(format), "%%%d[^\n]", array_size-1) < 0){return -14;} // create fscanf() format with chars maximum of MAX_ARRAY_SIZE-1
    char ctemp = '\0';
    buffer[0] = '\0'; // initialize or clear the OUTPUT array
    int result = fscanf(stream, format, buffer); // scan string
    // scan next char from the STREAM buffer separately because otherwise NEWLINE_CHAR will stay in the STREAM buffer if ERROR occurs in first fscanf()
    if((fscanf(stream, "%c", &ctemp) == EOF && result == 1) || ((result == 0 || result == 1) && ctemp == '\n')){ // if EOF was reached and something was read or only NEWLINE_CHAR was read (result == 0) or maximum of chars MAX_ARRAY_SIZE-1 wasn't exceeded (result == 1)
        return 0; // OK
    } else if(result != 1){if(result == EOF) return EOF; else if(result == 0) return 10; else return 11;} // exit if EOF or other ERROR occurs
    while(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){} // clear the STREAM buffer
    return 1; // OVERFLOW
}

int getl_v2(char *buffer, int array_size, FILE *stream) // getline() using fgets()
{
    if(buffer == NULL){return -11;}
    if(array_size <= 1){return -12;}
    if(stream == NULL){return -13;}
    buffer[0] = '\0'; // initialize or clear the OUTPUT array (not necessary - prevents user from accessing random data)
    if(fgets(buffer, array_size, stream) == NULL){return EOF;} // read ARRAY_SIZE chars from stream
    int lastCharIndex = strlen(buffer)-1; // this index should never be -1 because of NEWLINE_CHAR
    if(buffer[lastCharIndex] != '\n'){ // check if NEWLINE_CHAR was read
        char ctemp;
        if(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){ // check if only NEWLINE_CHAR stayed in the STREAM buffer
            while(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){} // clear the STREAM buffer by reading it char by char
            return 1; // OVERFLOW
        }
    } else {
        buffer[lastCharIndex] = '\0'; // remove NEWLINE_CHAR
    }
    return 0; // OK
}

int getl_v3(char *buffer, int array_size, FILE *stream) // getline() using fscanf("%c")
{
    if(buffer == NULL){return -11;}
    if(array_size <= 1){return -12;}
    if(stream == NULL){return -13;}
    char ctemp = '\0';
    int i = 0, result = 0;
    buffer[0] = '\0'; // initialize or clear the OUTPUT array
    while((result = fscanf(stream, "%c", &ctemp)) == 1 && ctemp != '\n' && i < array_size-1){buffer[i] = ctemp; buffer[++i] = '\0';} // read a char from the STREAM buffer until an ERROR or a NEWLINE_CHAR occurs or MAX_ARRAY_SIZE-1 is reached
    if((result == 1 && ctemp == '\n') || (result == EOF && i != 0)){ // check if only a NEWLINE_CHAR remained in the STREAM buffer or EOF was reached and something was read
        return 0; // OK
    } else if(result != 1){if(result == EOF) return EOF; else if(result == 0) return 10; else return 11;} // exit if EOF or other ERROR occurs
    while(fscanf(stream, "%c", &ctemp) == 1 && ctemp != '\n'){} // clear the STREAM buffer
    return 1; // OVERFLOW
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