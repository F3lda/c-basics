#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h>


bool fileCreate(const char * filename)
{
    FILE *file;
    if (file = fopen(filename, "a+")) {
        fclose(file);
        return true;
    }
    return false;
}

unsigned long long int fileSize(const char *filename)
{
    FILE *file = fopen(filename, "rb");
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        unsigned long long int size = ftell(file);
        fclose(file);
        return (size);
    }
    return 0;
}

bool fileExists(const char * filename)
{
    FILE *file;
    if (file = fopen(filename, "r")) {
        fclose(file);
        return true;
    }
    return false;
}

int main()
{
    // Get file size
    printf("%llu Bytes\n", fileSize("file.txt"));
    printf("%llu Bytes\n", fileSize("data.txt"));
    printf("%llu Bytes\n", fileSize("users.txt"));

    // Check if file exists
    if (fileExists("file.txt") == true) {
        printf("file.txt: The File exists\n");
    } else {
        printf("file.txt: The File doesn't exist\n");
    }
    
    if (fileExists("data.txt") == true) {
        printf("data.txt: The File exists\n");
    } else {
        printf("data.txt: The File doesn't exist\n");
    }

    if (fileExists("users.txt") == true) {
        printf("users.txt: The File exists\n");
    } else {
        printf("users.txt: The File doesn't exist\n");
    }

    // Rename files
    rename("data.txt", "data_old.txt");

    // Remove files
    remove("users.txt");



    // Read file line by line
    FILE* fp;
    fp = fopen("file.txt", "r");
    if (fp != NULL) {
        #define MAX_LEN 16
        char buffer[MAX_LEN];

        while (fgets(buffer, MAX_LEN, fp)) {
            // check newline char
            size_t eol = strcspn(buffer, "\n");
            if (buffer[eol] == '\0') {
                printf("%s", buffer);
            } else {
                buffer[eol] = '\0';
                printf("%s\n", buffer);
            }
        }

        fclose(fp);
    }



    // read structs with fseek function
    struct twoChars
    {
        char char1, char2;
    };

    struct twoChars chars;
    FILE *file;

    printf("\n");

   if ((file = fopen("file.txt","rb")) != NULL) {

        fseek(file, (long)(-sizeof(struct twoChars)), SEEK_END);
        fread(&chars, sizeof(struct twoChars), 1, file); 
        printf("char3: %d\tchar4: %d\n", chars.char1, chars.char2);

        fseek(file, (long)(-2*sizeof(struct twoChars)), SEEK_CUR);
        fread(&chars, sizeof(struct twoChars), 1, file); 
        printf("char1: %d\tchar2: %d\n", chars.char1, chars.char2);

        fclose(file); 
   }



    // Create files
    fileCreate("file.txt");
    fileCreate("users.txt");
    fileCreate("data.txt");

    return 0; 
} 
