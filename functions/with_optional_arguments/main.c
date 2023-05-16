#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>// va_list, va_start, va_arg, va_end

int function_name(int arguments_count, ...)
{
    va_list ap; // create list of arguments: ap
    va_start(ap, arguments_count); // optional argumets start after var: arguments_count

    int i, tmp;
    for(i = 0; i < arguments_count; i++)
    {
        tmp = va_arg(ap, int); // data type of argument: int
        printf("%d=%d;\n", (i+1), tmp);
    }
    va_end(ap); // delete list
    return 0;
}

int main()
{
    function_name(3, 45, 75, 63);
    return 0;
}
