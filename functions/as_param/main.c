#include <stdio.h> 
#include <stdlib.h> 

//https://stackoverflow.com/a/33870738

typedef int (procFunction)(int, void*);
typedef int (*procFunction2)(int, void*);

// pass address of a function as parameter to another function
int ProcessCreate1(int (processFunction)(int, void*), void *userData)
{
    processFunction(75, userData);
    return 0;
}

// pass function as parameter using function pointer
int ProcessCreate2(int (*processFunction)(int, void*), void *userData)
{
    processFunction(99, userData);
    return 0;
}


int ProcessCreate11(procFunction processFunction, void *userData)
{
    processFunction(752, userData);
    return 0;
}

int ProcessCreate22(procFunction2 processFunction, void *userData)
{
    processFunction(992, userData);
    return 0;
}



int func(int A, void *ptr)
{
    printf("FUNC: %d\n", A);
    return 0;
}

int main()
{
    ProcessCreate1(func, NULL);
    ProcessCreate2(func, NULL);
    ProcessCreate11(func, NULL);
    ProcessCreate22(func, NULL);
    //procFunction fn = func; // fn can't be initialized
    procFunction2 fn2 = func;
    ProcessCreate11(fn2, NULL);
    ProcessCreate22(fn2, NULL);

    printf("FUNCS: %d == %d\n", func, &func);

    return 0;
}
