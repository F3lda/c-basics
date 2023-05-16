/**
 * @file main.c
 * 
 * @brief Functions for strings in C
 * @date 2020-05-06
 * @author F3lda
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define STATIC_STRING_LENGHT 4000

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof((arr)[0]))



// String length
size_t Strlen(const char * str)
{
    size_t i = -1;
    while(str[++i]);
    return i;
}

// set string to uppercase
void strtoupper(char * str)
{
	while(*str) {*(str++) = toupper((unsigned char) *str);}
}

// set string to lowercase
void strtolower(char *str)
{
	while(*str) {*(str++) = tolower((unsigned char) *str);}
}

void trim(char * str)
{
    char * front = str-1;
    while (isspace(*++front));
    char * back = front+strlen(front);
    if (front[0] != 0) {
        while (isspace(*--back));
        *(++back) = '\0';
    }
    if (front != str) {memcpy(str, front, back-front+1);}
}

void trim_newline(char * str)
{
    char * front = str;
    while (*front != '\n' && *front != '\0') {front++;}
    *front = '\0';
}

int is_alphanumeric(char * str)
{
	int i;
	for (i = 0; i < strlen(str); i++){
		if (!(('0' <= str[i] && str[i] <= '9') || ('a' <= str[i] && str[i] <= 'z') || ('A' <= str[i] && str[i] <= 'Z'))) {
			return 0;
		}
	}
	return 1;
}



int strcount(char * str, char * substr)
{
    int count = 0;
    char *str_ptr = str;
    while ((str_ptr = strstr(str_ptr, substr)) != NULL) {
        str_ptr++;
        count++;
    }
    return count;
}

// string between substrings - returns pointer to the string and it's length
int strnsubstrs(char * str, char * substr1, char * substr2, char ** substr)
{
    char *start, *end;
    start = strstr(str, substr1);
    if (start != NULL) {
        start += strlen(substr1);
        end = strstr(start, substr2);
        if (end != NULL) {
            *substr = start; // substr pointer
            return end - start; // substr_length
        } else {
            return -2;
        }
    } else {
        return -1;
    }
}

// replace_string_with_index_in_string
int strplcsubstr(char * str, int str_max_length, char * substr_find, char * substr_replace, int substr_index)
{
    int count = 0;
    char *str_ptr = str;
    while ((str_ptr = strstr(str_ptr, substr_find)) != NULL) {
        if (count == substr_index) {
            // copy end of the string
            char * end_ptr = str_ptr+strlen(substr_find);
            int end_length = strlen(end_ptr);
            char end[end_length+1];
            strcpy(end, end_ptr);

            int substr_replace_length = strlen(substr_replace);
            if ((str_ptr-str)+substr_replace_length+end_length < str_max_length) {
                strcpy(str_ptr, substr_replace);
                strcpy((char *)(str_ptr+substr_replace_length), end);
                return substr_index;
            } else {
                return -1;
            }
        }
        str_ptr++;
        count++;
    }
    return count;
}



// scan double from string with error check
int sscand(const char *str, double *num)
{
    char temp_str[2];
	int result;
    if((result = sscanf(str, "%lf%1s", num, temp_str)) == 1){
        return 0; // OK - only number or number with white-spaces
    }
    return result; // ERROR - 2 or 0 or EOF
}


// scan int from string with error check
int sscani(const char *str, int *num)
{
    char temp_str[2];
	int result;
    if((result = sscanf(str, "%d%1s", num, temp_str)) == 1){
        return 0; // OK - only number or number with white-spaces
    }
    return result; // ERROR - 2 or 0 or EOF
}



int main()
{
    // strlen
    char str[] = {0};
    char str1[] = "123";
    char str2[] = "123\n\n\n"; //  in text mode, the native newline sequence is translated to '\n'
    int counter = 0;
    printf("Strlen: %d; %d;\n", Strlen(str1), Strlen(str2));


    // clear string
    char temp1[32] = "foobar";
    printf("String: <%s>\n", temp1);
    memset(temp1, '\0', 32);
    printf("cleared string: <%s>\n", temp1);


    // copy string
    memcpy(temp1, "Static String", strlen("Static String")); // check string max length!!!
    printf("memcpy: <%s>\n", temp1);

    strncpy(temp1, "random_string", strlen("random_string")); // check string max length!!!
    printf("strncpy: <%s>\n", temp1);

    snprintf(temp1, 32, "%s", "this is very long string"); // no need to check string max length -> saves (N-1) chars and last (N-th) char sets to '\0'
    printf("snprintf: <%s>\n", temp1);


	// strcat with length check - using memcpy
	char temp2[255] = "GET ";
	memcpy(&temp2[strlen(temp2)], "file_url", sizeof(temp2)-1-strlen(temp2));
	memcpy(&temp2[strlen(temp2)], " FSP/1.0\r\nHostname: ", sizeof(temp2)-1-strlen(temp2));
	memcpy(&temp2[strlen(temp2)], "file_server_name", sizeof(temp2)-1-strlen(temp2));
	memcpy(&temp2[strlen(temp2)], "\r\nAgent: name\r\n\r\n", sizeof(temp2)-1-strlen(temp2));
	printf("strcat - memcpy: <%s>\n", temp2);


	// strcat with length check - using snprintf
	char temp3[100] = {0};
	snprintf(temp3, 100, "%s%s", temp3, "this is");

	snprintf(temp3+strlen(temp3), sizeof(temp3)-strlen(temp3), "%s", " working");

    printf("strcat - snprintf: <%s>\n", temp3);


    // get number size in chars
    int x = 12345;
    int number_length = snprintf(NULL, 0, "%d", x); //-> returns max length of number value in chars
    printf("Number size in chars: number <%d> - size: %d\n", x, number_length);


    // trim_newline
    trim_newline(str2);
    printf("trim_newline: <%s>\n", str2);


    // Remove trailing newline
    char temp4[] = "string line cut in place of first new line char\n\n\n this is deleted\n";
    temp4[strcspn(temp4, "\n")] = '\0';
    printf("strcspn: <%s>\n", temp4);


    // trim
    char str3[] = "    \t \v abcd1234  \r\n\n\r";
    trim(str3);
    printf("Trim: <%s>\n", str3);


    // set string uppercase
    strtoupper(str3);
    printf("strtoupper: <%s>\n", str3);


    // set string lowercase
    strtolower(str3);
    printf("strtolower: <%s>\n", str3);


    // is alphanumeric
    printf("is_alphanumeric: <%d>\n", is_alphanumeric(str3));


    // number of substrings in string
    char str4[] = "    adfag21 2g5gaf\t \v <item>abcd1234</item>  \r\nfadgfg231a \n\raafg21ga 15 a516";
    printf("strcount: %d\n", strcount(str4, "g2"));


    // string between substrings in string
    char * between = NULL;
    int str_len = strnsubstrs(str4, "<item>", "</item>", &between);
    between[str_len] = '\0';
    printf("strnsubstrs: <%s> %d\n", between, str_len);


    // replace string
    char str5[128] = "    adfag21 2g5gaf <item>abcd1234</item> fadgfg231a aafg21ga 15 a516";
    printf("String: <%s> - length: %d\n", str5, strlen(str5));
    strplcsubstr(str5, 128, "abcd1234", "FOOBARFOOBAR", 0);
    printf("strplcsubstr (replace): <%s> - length: %d\n", str5, strlen(str5));

    char str6[] = "    adfag21 2g5gaf <item>abcd1234</item> fadgfg231a aafg21ga 15 a516";
    printf("String: <%s> - length: %d\n", str6, strlen(str6));
    strplcsubstr(str6, strlen(str6), "abcd1234", "FOOBARFOOBAR", 0); // new string is longer
    printf("strplcsubstr (replace): <%s> - length: %d\n", str6, strlen(str6));


    // Parse string
    int day, year;
    char month[20] = {0}, stemp[100];

    strcpy(stemp, "November 17 1989");
    sscanf(stemp, "%19s %d %d", month, &day, &year);

    printf("Parse string: %d %s %d\n", year, month, day);


    // Parse number
    const char * str7 = "   1 ,fd   ";
    double dbl = 0;

    printf("Parse number:\n");
    if (sscand(str7, &dbl)) {
        printf("F: %.50f\n", dbl);
        printf("G: %g\n", dbl);
    } else { // 2 or 0 or EOF
        printf("ERROR reading - F: %f\n", dbl);
    }


    // compare strings
    char temp5[] = "123456789";
    char temp6[] = "123";
    printf("Strings: <%s> <%s> -> ", temp5, temp6);
    if (strcmp(temp5, temp6) == 0) {
        // the strings are same
        printf("the strings are same\n");
    } else {
        // the strings are not same
        printf("the strings are not same\n");
    }


    // check if string starts with string
    if(strncmp(temp5, temp6, 3) == 0) {
        printf("String <%s> starts with <%s>\n", temp5, temp6);
    }

    if(strstr(temp5, temp6) == temp5 && temp5 != NULL) {
        printf("String <%s> starts with <%s>\n", temp5, temp6);
    }

    if(strstr(temp5, temp6) != NULL && strstr(temp5, temp6) == temp5) {
        printf("String <%s> starts with <%s>\n", temp5, temp6);
    }


    return 0;
}
