#include <stdio.h>
#include <stdlib.h>

int f(int a, int b)
{
    int c,d;
    printf("%d\t%d\n",c,d);
    printf("%d\t%d\t%d\n",d,c,c);
    printf("%d\t%d\t%d\n",c,d,d);
    printf("%d\t%d\t%d\n",d,c,d);

    c = a+b;
    d = b-a;
    return c*d;
}

int g(int a, int b)
{
    int c,d;
    //printf("%d\t%d\n",c,d);
    printf("%d\t%d\t%d\n",d,c,c);
    printf("%d\t%d\t%d\n",c,d,d);
    printf("%d\t%d\t%d\n",d,c,d);

    c = a;
    d = b;
    return c+d;
}

int main()
{
    printf("Res: %d\n",f(3,5));
    printf("Res: %d\n",f(3,5));
    printf("Res: %d\n",g(3,5));
    return 0;
}
