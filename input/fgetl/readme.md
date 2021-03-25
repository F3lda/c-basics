# C programming - getting string from (user) input

I was wondering what is the best way to get string from (from user or file) input in C programming because default functions aren't very reliable. Therefore I decided to find it out. Let's start with:

> ### Why not to use functions of `scanf()` family and `%s` to read strings?
> 
> 1. buffer overflow - `scanf()` with just `%s` will try to put string of any length in the given variable
> 2. skip of whitespace chars - `scanf()` with `%s` will never read newline char `'\n'`
> 3. newline char and overflowed input stays in STDIN buffer - rest STDIN buffer content is then read by next input function, which is therefore 'skipped'
>
> Try this twice with inputs `12345` and `1234567890`:
>   ```c
>   char output[10], ctmp;
>   printf("Type string: ");
>   scanf("%9s", output); // reads max 9 chars
>   printf("<%s>\n", output);
>   output[0] = '\0'; // clear array
>   printf("Type the same string again: ");
>   scanf("%9s%c", output, &ctmp);
>   printf("<%s><%c> <-- newline char\n", output, ctmp);
>   ```
> First time was everythnig OK, but the second time the overflowed zero was automaticaly read by next `scanf()`. And a newline char `'\n'` was only read by `%c`.
> <br />
> Try one more example with newline char `'\n'`. Press just `ENTERs`:
>   ```c
>   char output[10];
>   printf("Press ENTER: ");
>   int res = scanf("%9[^\n]", output); // reads max 9 chars until newline char '\n'
>   printf("<%s><res:%d>\n", output, res);
>   output[0] = '\0'; // clear array
>   printf("Press ENTER again: ");
>   scanf("%9s%*c", output); // reads max 9 chars; %*c discards newline char '\n'
>   printf("<%s>\n", output);
>   ```
> After first `ENTER` `scanf()` resulted `0` and code continued. But next time `scanf()` stucked until input was more than just `ENTER`. You can have the same behaviour aslo in the first `scanf()` by adding space -> `scanf(" %9[^\n]", output);`
> <br /><br />
> Here is a very nice article about scanning strings (I recommend read this before continuing): http://www.sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html

So ...
## We want to read a string from input

Let's begin! On the Internet we can find something like this:
```c
char buffer[10];
printf("Type string: ");
if(scanf("%9[^\n]%*c", buffer) == 1){//reads max 9 chars or until newline char; "%*c" discards next char in STDIN
    printf("<%s>", buffer);
}
```
Does it work? Run and see... Yep, no overflow, nice! But if the input is longer than 9 chars, the rest will stay in STDIN stream...
```c
char buffer[10];
printf("Type string: ");
if(scanf("%9[^\n]%*c", buffer) == 1){//reads max 9 chars or until newline char; "%*c" discards next char in STDIN
    printf("<%s>", buffer);
}
// check if STDIN buffer is empty
char strTemp[255];
printf("Type string:");
fgets(strTemp, sizeof(strTemp), stdin);
printf("<%s>", strTemp);
```
Never use `fflush(stdin);` or similar functions to clear STDIN buffer -> the only way to clear unread input is by reading it!
OK, so let's see what's the char discarted by `"%*c"` sign...
```c
char buffer[10], ctemp;
printf("Type string: ");
if(scanf("%9[^\n]%c", buffer, &ctemp) == 2){
    printf("<%s><%c>", buffer, ctemp);
}
// check if STDIN buffer is empty
...
```
Hmm... It's next char in STDIN buffer -> newline char `'\n'` (STDIN is empty) or other next char in STDIN (STDIN isn't empty)
<br />
-> that's because scanning with `"%c"` doesn't skip any chars (including whitespace chars), it takes char by char from STDIN.
<br />
<br />
So when the next char in STDIN buffer isn't a newline char, then the buffer isn't empty. So we have to read all next chars one by one until we reach newline char `'\n'` -> then STDIN buffer is empty.
```c
char buffer[10], ctemp;
printf("Type string: ");
if(scanf("%9[^\n]%c", buffer, &ctemp) == 2){
    printf("<%s><%c>", buffer, ctemp);
    if(ctemp == '\n'){
        while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){}
        printf("clear STDIN buffer\n");
    }
}
// check if STDIN buffer is empty
...
```
And we can simplified it...
```c
char buffer[10], ctemp;
printf("Type string: ");
if(scanf("%9[^\n]", buffer) == 1){
    printf("<%s>\n", buffer);
    while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){}
    //printf("clear STDIN buffer\n");
}
// check if STDIN buffer is empty
...
```
YEP AWESOME!
<br /><br />
BUT!!! What if we press just `ENTER`:
<br />
`scanf()` results `0`, code inside `if-statement` is skipped and in STDIN buffer stays newline char `'\n'`!
<br />
So we have to change it a little bit (delete if statement and clear output array to prevent printing random chars):
```c
char buffer[10], ctemp;
printf("Type string: ");
strcpy(buffer, ""); //buffer[0] = '\0'; // initialize or clear array (prevents printing random chars)
scanf("%9[^\n]", buffer); // scan string
while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){} // clear STDIN buffer
printf("<%s><%c>\n", buffer, ctemp);
// check if STDIN buffer is empty
...
```
Hohoohoo IT WORKS!! NO OVERFLOW and STDIN buffer is EMPTY! NICE!!!
<br />
Now all we need to clear STDIN buffer is just this:
```c
// clear STDIN buffer by reading char by char
char ctemp;
while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){}

//NOTICE: But you have to be sure that in the buffer is at least one char, otherwise it will wait for user input! 
```
### Final getl() functions

Let's make a function from it...
```c
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
```
Ooops this is horrible...
<br />
`scanf("%s");` is bad for this. Is here some other way?
<br />
Yes, we can read input string char by char or use `fgets()` function instead...
```c
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
```
Well yes, this is how might `fgets();` works! Because `fgets();` reads all chars in size of output variable and doesn't skip whitespace chars, it's like when we would read it char by char by for example `scanf("%c", &ctmp);`.
<br />
Now we can change our function to this:
```c
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
}
```
And usage (try with STDIN or FILE [< file.txt]):
```c
char output[10];
int result;
while((result = getl_v2(output, sizeof(output), stdin)) >= 0 && strcmp(output, "") != 0){
    if(result == 0){
        printf("OK - ");
    } else {
        printf("OVERFLOW - ");
    }
    printf("<%s>\n", output);
}
printf("Done! <res:%d>\n", result);
```
In the end we have nice working function for reading strings in C - empty STDIN & no OVERFLOW & no unexpected behavior

### Parsing string
After reading input you can parse it with `sscanf();` function:
```c
int day, year;
char month[20], stemp[100];

strcpy(stemp, "November 17 1989");
sscanf(stemp, "%s %d %d", month, &day, &year);

printf("%d %s %d\n", year, month, day);
```
### Parse number
```c
// scan double from string with error check
int sscand(const char *str, double *num)
{
    char temp_str[2];
    if(sscanf(str, "%lf%1s", num, temp_str) == 1){
        return 1; // only number or number with white-spaces
    }
    return 0; // 2 or 0 or EOF
}

int main(int argc, char **argv)
{
    const char * str = "   1 ,fd   ";
    double dbl = 0;

    if(sscand(str, &dbl)){
        printf("F: %.50f\n", dbl);
        printf("G: %g\n", dbl);
    } else { // 2 or 0 or EOF
        printf("ERROR reading - F: %f\n", dbl);
    }
}
```
### Read user input until RAM is over/full
You can also do this without limited size of buffer and read chars dynamically until newline char `'\n'` is reached and until RAM is full. (I think it's not a good practise but in some cases it can be useful.)
```c
char * readString(int temp_buffer_size, FILE *stream)
{
    if(temp_buffer_size < 2 || stream == NULL){
        return NULL;
    }

    char *str = malloc(sizeof(char) * temp_buffer_size), *temp_str = NULL;
    if(str != NULL){str[0] = '\0';}
    while(str != NULL && fgets(&str[strlen(str)], temp_buffer_size, stream) != NULL && str[strlen(str)-1] != '\n'){
        if((temp_str = realloc(str, sizeof(char) * (strlen(str)+1+temp_buffer_size))) == NULL){
            free(str);
        }
        str = temp_str;
    }

    if(str != NULL){
        if(strlen(str) > 0){str[strlen(str)-1] = '\0';}

        if((strlen(str)+1) % temp_buffer_size != 0){
    //printf("REALLOC: %d->%d\n", ((int)((strlen(str)+1) / temp_buffer_size)+1)*temp_buffer_size, strlen(str)+1);
            if((temp_str = realloc(str, sizeof(char) * (strlen(str)+1))) == NULL){
                free(str);
            }
            str = temp_str;
        }
    }

    return str;
}

int main()
{
    char *str = readString(8, stdin);
    if(str != NULL){
        printf("<%s><len:%d>\n", str, strlen(str));

        free(str);
        str = NULL;
    } else {
        printf("ERROR: NULL\n");
    }
}
```