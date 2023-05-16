#include <stdio.h> 
#include <stdlib.h> 

typedef void (*Tfunc)(void);

void effect1()
{
    printf("Effect 1\n");
}

void effect2()
{
    printf("Effect 2\n");
}

void effect3()
{
    printf("Effect 3\n");
}

int main()
{
    Tfunc funcions[] = {effect1, effect2, effect3};
    int counter = 0;
    while(counter < 9) 
    {
        funcions[counter % 3]();  
        counter++;
    }
    return 0;
}
