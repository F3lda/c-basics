#include <stdio.h>

int main()
{
    printf("Hello world!\n");

    printf("Tell me your name: ");
    char name[255] = {0};
    scanf("%254[^\n]s", name);

    printf("Your name is: %s\n", name);

    scanf("%*c");

    printf("Press Enter to continue...");

    scanf("%*c");

    return 0;
}
