#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STATIC_STRING_LENGHT 16

void strtoupper(char *str);

void strtolower(char *str);

int is_alphanumeric(char *str);

void trim(char * str);

int main()
{
    char tempString[STATIC_STRING_LENGHT] = {0};
    char tempString2[STATIC_STRING_LENGHT] = "Second string";
    
    // clear string
    memset(tempString, '\0', sizeof(char)*STATIC_STRING_LENGHT);
    
    // copy string
    memcpy(tempString, "Static String", sizeof(char)*(STATIC_STRING_LENGHT-1));

    // set string uppercase
    strtoupper(tempString2);
    
    // fill string
    snprintf(tempString, STATIC_STRING_LENGHT, "%d : %s", 123, tempString2); // saves (STATIC_STRING_LENGHT-1) chars and last (STATIC_STRING_LENGHT) char sets to '\0'
	
    // get number size in chars
    int number_length = snprintf(NULL, 0, "%d", x); //-> returns max length of number value in chars
    
    // compare strings
    if(strcmp(tempString, tempString2) == 0){
        // the strings are same
    } else {
        // the strings are not same
    }
    
    // check if string starts with string
    if(strstr(tempString, "123") != NULL && strstr(tempString, "123") == tempString){
    }
    
    // trim
	char temp[64] = "\r\n   Hello world!   \r\n";
	trim(temp);
	printf("<%s>\n",temp);
    
    // substr
	// str between substrs (NULL => from start/end)
    
    return 0;
}

void strsubstr(char str[], char substr1[], char substr2[], char *returnArray)
{	//TODO
    char *start, *end;
    start = strstr(str, substr1);
    if(start != NULL){
        start += strlen(substr1);
        end = strstr(start, substr2);
        if(end != NULL){
            char target[(end - start)+1];
            memcpy(target, start, end - start);
            target[end - start] = '\0';
            strcpy(returnArray,target);
        } else {
            strcpy(returnArray,"");
        }
    } else {
        strcpy(returnArray,"");
    }
}

void trim(char * str)
{
	char * front = str;
	while(isspace(*front)){front++;}
	char * back = front+strlen(front);
	while(isspace(*--back));
    *(back+1) = '\0';
	memcpy(str, front, back-front+2);
}

void strtoupper(char *str)
{
	while (*str) {
		*str = toupper((unsigned char) *str);
		str++;
	}
}

void strtolower(char *str)
{
	while (*str) {
		*str = tolower((unsigned char) *str);
		str++;
	}
}

int is_alphanumeric(char *str)
{
	int i;
	for(i = 0; i < strlen(str); i++){
		if(!(('0' <= str[i] && str[i] <= '9') || ('a' <= file_url[i] && file_url[i] <= 'z') || ('A' <= file_url[i] && file_url[i] <= 'Z'))){
			return 0;
		}
	}
	return 1;
}
