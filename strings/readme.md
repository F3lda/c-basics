NOTE:   1. In C programming there isn't any data type `String` but we have just `an Array of chars`. 
        2. `STDIN` = (short for `standard input`) is a pointer to a `FILE`.

STDERR Source: https://stackoverflow.com/a/19870390
It is a good practice.

Lets say you use linux. If so, you can run your program following way:

./program >out 2>errout

'out' file will contain only STDOUT.
'errout' file will contain only STDERR

So if your output is hundreds of lines long, it is easier to look for few errors in 'errout' rather than look through tons of non-error lines combined with error lines.

### Error Handling in C programs


1. Global Variable errno


errno value       Error
1             /* Operation not permitted */
2             /* No such file or directory */
3             /* No such process */
4             /* Interrupted system call */
5             /* I/O error */
6             /* No such device or address */
7             /* Argument list too long */
8             /* Exec format error */
9             /* Bad file number */
10            /* No child processes */
11            /* Try again */
12            /* Out of memory */
13            /* Permission denied */

#include <stdio.h> 
#include <errno.h> 
#include <string.h> 
#include <stdlib.h>

printf("Value of errno: %d\n ", errno); 
printf("The error message is : %s\n", strerror(errno)); 
perror("Message from perror"); 

exit(EXIT_FAILURE); 
exit(EXIT_SUCCESS);




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#define DEBUG
#define ERRORs

#ifdef DEBUG
    #define D
#else
    #define D if(0)
#endif

#ifdef ERRORs
    //#define msg(format, ...) fprintf(stderr, "%s:%d:%s(): "format"\n", __FILE__, __LINE__, __func__, ##__VA_ARGS__)
    #define error(format, ...) fprintf(stderr, format, ##__VA_ARGS__); exit(EXIT_FAILURE)
#else
    #define error(format, ...) fprintf(stderr, "")
#endif


D printf("---------------\n");
error("Contact list is EMPTY!%c",'\0');
