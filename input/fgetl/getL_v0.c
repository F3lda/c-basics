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

int main()
{
    printf("Function 'getLine()' VER 1:\n");
    
    char output[10] = "";
    printf("----------------------------------------------------\n");
    getLine(output,10);
    printf("----------------------------------------------------\n");
    output[0] = '\0'; // clear array
    getLine(output,10);
    
    // check if STDIN buffer is empty
    char strTemp[255];
    printf("Type string:");
    fgets(strTemp, sizeof(strTemp), stdin);
    printf("<%s>",strTemp);
    
    return 0;
}