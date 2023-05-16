/**
 * @file main.c
 * 
 * @brief Functions for reading line string input from streams in C
 * @date 2020-05-06
 * @author F3lda
 */
// input types
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 



/* Get line from stream using fgetc() function
*  -----
*  char *line_buffer - char array to save input string
*  size_t line_buffer_size - input string max length including terminating char '\0'
*  FILE *stream - input stream
*  return - 0 -> newline char not read/reached (stream is not empty)
*         - '\n' -> newline char read/reached
*         - EOF -> end of file reached
*         - 1 -> unknown errror
*         - <0 -> arguments errors
*/
int fgetlc(char *line_buffer, size_t line_buffer_size, FILE *stream) // stream_buffer_size = 1;
{
    if (line_buffer == NULL) {
        return -2;
    }

    if (line_buffer_size < 2) { // one char + terminating char
        return -3;
    }

    if (stream == NULL) {
        return -4;
    }

    int c;
    size_t length = 0;
    do {
        c = fgetc(stream);
        if (c != EOF && c != '\n') {
            line_buffer[length] = (char)((unsigned char)c);
            length++;
            line_buffer[length] = '\0';
        }
    } while(c != EOF && c != '\n' && length+1 < line_buffer_size);

    if (c == EOF) {
        if(feof(stream)) {
            return EOF; // End Of File
        }
        return 1; // unknown errror
    }
    if (c == '\n') {
        return '\n'; // newline char read/reached
    }

    return 0; // stream is not empty
}


// Get line from stream using fgets() function
int fgetls(char *line_buffer, int line_buffer_size, FILE *stream) // stream_buffer_size = line_buffer_size
{
    if (line_buffer == NULL) return -2;
    if (line_buffer_size < 2) return -3;
    if (stream == NULL) return -4;
    if (fgets(line_buffer, line_buffer_size, stream) == NULL) {
        if (feof(stream)) {
            return EOF; // End Of File
        }
        return 1; // unknown error
    }
    size_t len = strlen(line_buffer);
    if(line_buffer[len-1] == '\n') {
        line_buffer[len-1] = '\0';
        return '\n'; // Newline char read/reached
    }
    return 0; // stream is not empty
}


// Get line from stream using fscanf() function
int fgetlf(char *line_buffer, int line_buffer_size, FILE *stream) // stream_buffer_size = line_buffer_size
{
    if (line_buffer == NULL) {
        return -2;
    }

    if (line_buffer_size < 2) { // one char + terminating char
        return -3;
    }

    if (stream == NULL) {
        return -4;
    }

    char format[32]; // this should be enough also for unsigned long int
    if (snprintf(format, sizeof(format), "%%%d[^\n]", line_buffer_size-1) < 0) { // create scanf format with max chars array_size-1
        return -5; // string variable FORMAT is too short
    }
    
    // clear string - not necessary
    //memset(line_buffer, '\0', sizeof(char)*line_buffer_size);

    if (fscanf(stream, format, line_buffer) != 1) { // scan string
        // empty line - EOF or newline
        if(feof(stream)) {
            return EOF;
        }
        return 1; // unknown error
    }

    int c = 0;
    if (line_buffer[line_buffer_size-2] == '\0') { // if buffer is not full -> EOF or newline char
        c = fgetc(stream); // clear newline char from stream
    }

    return c; // '\n' or EOF
}


// Read user input using malloc -> read until line_buffer_size or RAM is over/full
// if line_buffer_size is set to 0 -> reads chars from stream until realloc is NULL
int fgetlm(char **line_buffer, int line_buffer_size, FILE *stream, int stream_buffer_size) // malloc + realloc
{
    if ((*line_buffer) != NULL) {
        return -2;
    }

    if (line_buffer_size < 0) {
        return -3;
    }

    if (stream == NULL) {
        return -4;
    }

    if (stream_buffer_size < 2) {
        return -6;
    }


    if (stream_buffer_size > line_buffer_size && line_buffer_size != 0) {
        stream_buffer_size = line_buffer_size;
    }

    int length = 0, result = 0;
    char *temp_line_buffer = NULL;

    do {
        if ((temp_line_buffer = realloc((*line_buffer), sizeof(char) * (length+stream_buffer_size))) != NULL) {
            result = fgetlc(&temp_line_buffer[length], stream_buffer_size, stream);
            (*line_buffer) = temp_line_buffer;
            length += stream_buffer_size-1; // minus terminating char

            if (result < 0) {
                return result;
            }

            if (length+stream_buffer_size > line_buffer_size && line_buffer_size != 0) {
                stream_buffer_size = stream_buffer_size-((length+stream_buffer_size)-line_buffer_size);
            }
        }
        //printf("<%u, %d>\n",temp_line_buffer, result);
    } while(temp_line_buffer != NULL && stream_buffer_size > 1 && result == 0 && !feof(stream)); // EOF or NEWLINE or FULL BUFFER

    // realloc to string length
    if (*line_buffer != NULL) {
        if ((temp_line_buffer = realloc((*line_buffer), sizeof(char) * (strlen(*line_buffer)+1))) != NULL) {
            (*line_buffer) = temp_line_buffer;
        }
    }

    return result; // newline or EOF
}


// Clear stream buffer until newline char or EOF is reached
// NOTICE: You have to be sure that in the buffer is at least one char, otherwise it will wait for user input!
int fclearl(FILE *stream)
{
    if (stream == NULL) {
        return 0;
    }

    int c;
    do {
        c = fgetc(stream);
    } while(c != EOF && c != '\n');

    return c; // newline or EOF
}



int main()
{
    // when you write more than max chars, stdin stream is cleared
    char line2[10];
    printf("Type chars (more than 10): ");
    int result = fgetlc(line2,10,stdin);
    printf("Result: %d (0 == STDIN is not empty)\nLine: <%s>\n",result,line2);
    if (result != '\n') {
        fclearl(stdin);
    }

    printf("Type chars (less than 10): ");
    result = fgetlc(line2,10,stdin);
    printf("Result: %d (10 == Newline char read)\nLine: <%s>\n",result,line2);
    if (result != '\n') {
        fclearl(stdin);
    }

    printf("Type chars (max 10): ");    
    if (fgetlc(line2,10,stdin) != '\n') {
        fclearl(stdin);
    }
    printf("Line: %s\n",line2);



    // read stream with dynamic memory allocation
    char *str = NULL;
    printf("Type chars (malloc - less than 10): ");
    printf("Result: %d (10 == Newline char read)\n", fgetlm(&str, 10, stdin, 3));
    printf("Line: <%s>\n", str);
    free(str);


    // usage of ungetc
    printf("Type one char (ungetc): ");
    int ch = getc(stdin);
    printf("STDIN: %c\n",ch);
    
    ungetc('x', stdin);
    printf("STDIN: %c\n",getc(stdin));
    ungetc('y', stdin);
    printf("STDIN: %c\n",getc(stdin));

    if (ch != '\n') { // clear only when more chars than only enter were pressed
        fclearl(stdin);
    }


    // file read
    printf("Press any key to read file...");
    getc(stdin);

    FILE *f = fopen("main.c","r");
    if(f != NULL){
        char line[100];
        while(!feof(f)) {
            line[0] = '\0';
            if(fgetlc(line, 10, f) == '\n') {
                printf("<%s>\n",line);
            } else {
                printf("<%s>",line);
            }
        }
        fclose(f);
    }
    printf("\n");

    return 0;
}
