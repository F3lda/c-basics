#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#ifdef _WIN32
    #define delay(seconds) Sleep(seconds*1000)
#else
    #define delay(seconds) sleep(seconds)
#endif



int main()
{
    printf("Wait 3 seconds...");
    delay(3);
    printf("\nDone!\n");
    return 0;
}
