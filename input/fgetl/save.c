#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getLine(char *output, int ARRAY_SIZE)
{
    if(ARRAY_SIZE > 0){
        char tempLine[5]; // buffer
        int lineEnd = 0;
        do {
            fgets(tempLine, sizeof(tempLine), stdin);

            int i = 0;
            while(tempLine[i] != '\n' && tempLine[i] != '\0'){i++;}
            if(lineEnd == 0) {
                if(tempLine[i] == '\n'){
                    lineEnd = 1;
                    sscanf(tempLine,"%4[^\n]%*c",tempLine);// tempLine size-1
                    if(tempLine[i] == '\n'){tempLine[i] = '\0';}
                    printf("<%s>END\n",tempLine);
                    if(!(strlen(output)+strlen(tempLine) < ARRAY_SIZE)){lineEnd = -1;}
                } else {
                    printf("<%s>|",tempLine);
                }
                if(strlen(output)+strlen(tempLine) < ARRAY_SIZE){
                    strcat(output,tempLine);
                } else {
                    if(lineEnd != -1){
                        lineEnd = -2;
                    }
                    int restMem = ARRAY_SIZE-strlen(output)-1;
                    printf("ERROR - NO MEMORY; rest: %d\n",restMem);
                    //add rest to output
                    int ii;
                    for(ii = 0; ii < restMem; ii++){
                        printf("[REST]");
                        output[ii+strlen(output)+1] = '\0';
                        output[ii+strlen(output)] = tempLine[ii];
                    }
                }
            } else if(tempLine[i] == '\n'){// && lineEnd == -2
                lineEnd = -1;
                printf("NOMEMLAST<%s>|",tempLine);
            }
        } while(lineEnd == 0 || lineEnd == -2);

        printf("----------------------------------------------------\n");
        printf("RESULT:<%s>:%d\n",output,lineEnd);

        return lineEnd;
    } else {
        return -3;
    }
}

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
        while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){} // clear STDIN buffer
        return 1; // overflow
    }
    return result;
}

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
    char strTemp[10];
    printf("Type string:");
    fgets(strTemp, sizeof(strTemp), stdin);
    printf("<%s>", strTemp);
/*
    printf("Type string:");
    fgets(strTemp, sizeof(strTemp), stdin);
    printf("<%s>", strTemp);*/
    // I was wondering how to get string input from user the best way in C programming because default functions aren't very reliable. For example:

    // why is bad using scanf() family of functions to read strings
    // - overflow
    // - skip of whitespace chars
    // - newline char and overflowed input stays in STDIN buffer -> it's read by next input function so it's skipped
    // here is very nice article about reading user input -> http://www.sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html

    // so let's start reading string input
    // on the internet I found something like this: TODO if(scanf("%9[^\n]%*c", buffer) == 1)

    // does't it work? run and see. yep, no overflow, nice.. but the rest of input still stays in STDIN stream..
    // never use fflush(stdin); or similar functions -> the only way to clear unread input is by reading it.

    // //scanf("%*[^\n]");
            //scanf("%*[^\n]%*c");
            // ok, this doesn't work

    // ok, so let's look what's the char discarted by '*' sign
    // TODO scanf("%9[^\n]%c", buffer, &ctmp);

    // hmm.. it's next char in STDIN buffer - newline '\n' char or other char -> that's because scanning with one-char type (%c) doesn't skip whitespace chars -> scan("%c");
    // so when there is not newline char let's read next until we reach newline char...

    // TODO VER 3

    // hohoohoo it WORKS!! no overflow and stdin buffer is empty! NICE
    // can we simplified it?

    // TODO VER 4

    // yep awesome...
    // let's make function from it...
    // oops it will be horrible..

    // TODO VER 4.1

    // ok scanf("%s"); is bad for this.
    // is here some other way?
    // yes, we can read string char by char instead...

    // TODO fgets2()

    // well, but this is how fgets(); works

    // TODO VER 5

    // and because fgets(); reads all chars and doesn't skip whitespace chars
    // we can check if the newline char is in read string; if not let's clear buffer like last time - by reading stdin until newline char

    // OK here we go, with some small changes we got nice function for reading string in C programming - empty STDIN and no overflow


    // after reading input you can parse it for example with sscanf();


    // you can also do this without limited size of buffer and read chars dynamically until newline char '\n' and until RAM is full .... (not good practise)

    //     TODO function getl with pointer (let's use fscanf(); because you can use different streams)



    // VER 1
    /*char output[10] = "";
    printf("----------------------------------------------------\n");
    getLine(output,10);
    printf("----------------------------------------------------\n");
    output[0] = '\0'; // clear array
    getLine(output,10);
    output[0] = '\0'; // clear array
    scanf("%9[^\n]%*c",output);
    printf("RES:<%s>\n",output);
    output[0] = '\0'; // clear array
    scanf("%9[^\n]%*c",output);
    printf("RES:<%s>\n",output);*/


    // VER 3
    /*printf("Function 'getl' VER 3:\n");

    char strtmp[10], ctmp;

    scanf("%9[^\n]%c",strtmp,&ctmp); //TODO set number dynamically
    printf("<%s><%c>\n",strtmp,ctmp);

    if(ctmp != '\n'){
        while(scanf("%c",&ctmp) == 1 && ctmp != '\n'){}
        printf("clear STDIN buffer\n");
    }

    printf("<%s>\n",strtmp);

    // check if STDIN buffer is empty
    printf("Type string:");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>",strtmp);*/




    // VER 4
    /*printf("Function 'getl' VER 4:\n");

    char strtmp[10], ctmp;

    scanf("%9[^\n]",strtmp); //TODO set number dynamically
    printf("<%s>\n",strtmp);

    while(scanf("%c",&ctmp) == 1 && ctmp != '\n'){}
    printf("clear STDIN buffer\n");

    printf("<%s>\n",strtmp);

    // check if STDIN buffer is empty
    printf("Type string:");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>",strtmp);*/



    // VER 5
    /*printf("Function 'getl' VER 5:\n");

    char strtmp[10], ctmp;
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s><%d>\n",strtmp,strlen(strtmp));

    if(strtmp[strlen(strtmp)-1] != '\n'){ // this index should never go -1 because of newline char, try fgets() just with enter and strlen()
        while(scanf("%c",&ctmp) == 1 && ctmp != '\n'){}
        printf("clear STDIN buffer\n");
        //return 1; //overflow
    } else {
        strtmp[strlen(strtmp)-1] = '\0';
        //return 0; //OK
    }

    printf("<%s>\n",strtmp);

    // check if STDIN buffer is empty
    printf("Type string:");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>",strtmp);*/



    // VER 6
    /*printf("Function 'getl' VER 6:\n");

    // TODO if ARRAY_SIZE is bigger than 1 and BUFFER is not null
    char strtmp[10], ctmp;
    fgets(strtmp, sizeof(strtmp), stdin); // != NULL
    printf("<%s><%d>\n",strtmp,strlen(strtmp));

    printf("<%d>\n",strcspn(strtmp, "\n"));

    int lastCharIndex = strlen(strtmp)-1; // and here comes limitation with INT_MAX size, but maybe it's same with char array max size or fgets() max buffer size... who knows... at least we don't use same command (expression) twice
    if(lastCharIndex >= 0){ // this index should never go -1; try fgets() just with enter and strlen()
        if(strtmp[lastCharIndex] != '\n'){
            //TODO check for EOF
            while(scanf("%c",&ctmp) == 1 && ctmp != '\n'){} // clears input buffer, but don't use when you are not sure if buffer is not empty, if yes then it will stuck waiting for enter
            //TODO clear buffer by fgets(array_size);
            //char strtmp2[10]; strtmp2[0] = '\0';// array_size
            //while(fgets(strtmp2, sizeof(strtmp2), stdin) != NULL && strchr(strtmp2, '\n') == NULL){}
            printf("clear STDIN buffer\n");
            //return 1; //overflow
        } else {
            strtmp[lastCharIndex] = '\0'; // replace \n with \0
            printf("set '\\n' to '\\0'\nOK\n");
            //return 0; OK
        }
    } else {
        //return 2; index error
    }

    printf("RESULT:<%s>\n",strtmp);
    // check if STDIN buffer is empty
    printf("Type string:");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>",strtmp);*/


    /*char output[10], ctmp;
    scanf("%9s",output);
    printf("<%s>\n",output);
    output[0] = '\0';
    scanf("%9s%c",output,&ctmp);
    printf("<%s><%c>\n",output,ctmp);
    scanf("%c",&ctmp);
    printf("<%c>\n",ctmp);*/




/*
char buffer[10], ctemp;
printf("Type string: ");
if(scanf("%9[^\n]", buffer) == 1){
    printf("<%s>\n", buffer);
    while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){}
    //printf("clear STDIN buffer\n");
}
*/





//And we can simplified it...

        //code

//Hohoohoo IT WORKS!! NO OVERFLOW and STDIN buffer is EMPTY! NICE!!!

//BUT!!! What if we press just ENTER:
//scanf() results 0, code inside if-statement is skipped and in STDIN buffer stays newline char '\n'!
//So we have to change it a little bit (delete if statement and clear output array to prevent printing random shit):

/*
char buffer[10], ctemp;
printf("Type string: ");
strcpy(buffer, ""); //buffer[0] = '\0'; // initialize or clear array
scanf("%9[^\n]", buffer); // scan string
while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){} // clear STDIN buffer
printf("<%s><%c>\n", buffer, ctemp); // TODO PRINTF and clean buffer ...
*/

//Well, that should be all. It's nice, short and it works.
//Let's make a function from it...


    // TODO function

//Well yes, this is how might fgets(); works! Because fgets(); reads all chars in size of output variable and doesn't skip whitespace chars, it's like when we would read it char by char by scanf("%c",&ctmp).
//Now we can change our function to this:


//


/*
char buffer[10], ctemp;
printf("Type string: ");
if(scanf("%9[^\n]", buffer) == 1){
    printf("<%s>\n", buffer);
    while(scanf("%c", &ctemp) == 1 && ctemp != '\n'){}
    //printf("clear STDIN buffer\n");
}*/


/*
if(scanf("%9[^\n]", buffer) == 1 || scanf("%c", &ctemp) == 1){
    printf("<%s><%c>\n", buffer, ctemp);
    if(ctemp != '\n'){
        while(scanf("%c",&ctemp) == 1 && ctemp != '\n'){}
        //printf("clear STDIN buffer\n");
    }
} else {
    printf("HOVNO\n");
}
*/

/*
// check if STDIN buffer is empty
char strTemp[255];
printf("Type string:");
fgets(strTemp, sizeof(strTemp), stdin);
printf("<%s>",strTemp);

*/

    // fgets() implementation
/*
    char strtmp[10];
    printf("Type string: ");
    printf("<%d>",fgets2(strtmp, sizeof(strtmp), stdin));
    printf("<%d>\n<%s>\n",strlen(strtmp),strtmp);

    printf("Type string: ");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>\n",strtmp);

    printf("Type string: ");
    fgets(strtmp, sizeof(strtmp), stdin);
    printf("<%s>\n",strtmp);
*/

    /*
        // get number of digits of array size number
        size_t buffer_size = array_size+1;
        int digit_count = 1;
        while (buffer_size > 9) {
            buffer_size /= 10;
            digit_count++;
        }
        char format[16+digit_count];
        // create buffer size +1 for length check
        buffer_size = array_size+1;
        char buffer[buffer_size];
        memset(output, '\0', buffer_size*sizeof(char));
        // create scanf format
        snprintf(format, sizeof(format), " %%%ds", buffer_size-1);//[^\n]

        printf("<%s> = %d; buffer_size=%d\n", format, sizeof(format),buffer_size);
*/


    return 0;
}
