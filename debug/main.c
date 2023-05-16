#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

/*
Global Variable errno

errno value    Error
1              Operation not permitted 
2              No such file or directory 
3              No such process 
4              Interrupted system call 
5              I/O error 
6              No such device or address 
7              Argument list too long 
8              Exec format error 
9              Bad file number 
10             No child processes 
11             Try again 
12             Out of memory 
13             Permission denied 
*/

/*
Run program with errors logging to file

./debug.exe >out.txt 2>error_log.txt

'out.txt' file will contain only STDOUT.
'error_log.txt' file will contain only STDERR
*/

#define DEBUG
#define ERRORs



#ifdef DEBUG
    #define D
#else
    #define D if(0)
#endif

#ifdef ERRORs
    #define error(format, ...) fprintf(stderr, format, ##__VA_ARGS__)//; exit(EXIT_FAILURE)
#else
    #define error(format, ...) NULL
#endif

#define msg(format, ...) fprintf(stdout, "%s:%d:%s(): "format"\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)



int main()
{
    D printf("---------------\n");
    error("Contact list is EMPTY!%s","\n------\n");
    msg("TEST");
    
    printf("TEST\n\n");

    printf("Value of errno: %d\n ", errno);
    printf("The error message is : %s\n", strerror(errno));
    perror("Message from perror");

    return EXIT_SUCCESS;
}
