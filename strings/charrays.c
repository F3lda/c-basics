#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATIC_STRING_LENGHT 16

void strtoupper(char *str);

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
    
    // substr
    
    return 0;
}

void strtoupper(char *str)
{
	while (*str) {
		*str = toupper((unsigned char) *str);
		str++;
	}
}
