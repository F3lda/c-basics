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



/*** This code could be hidden within a class or library somewhere ***/
typedef void (*voidFuncPtr)(void); // Create a type to point to a funciton.
static voidFuncPtr _CallBackFuncitonPointer = NULL; // Create an instance of the empty function pointer

void BlinkIt(voidFuncPtr CallBackFuncitonPointer) {
    _CallBackFuncitonPointer = CallBackFuncitonPointer; // assign a function to the empty function pointer
}

void Blink(unsigned long delaySeconds) {
    if (_CallBackFuncitonPointer) {
        delay(delaySeconds);
        _CallBackFuncitonPointer(); // call the function we assigned to the once empty function pointer
    }
}
/***********************************************************************/
// include "MyLibrary.h" for example that contains the above code



void MySpecialBlinkFunction()
{
    printf("Callback function activated!\n");
}

int main()
{
    BlinkIt(MySpecialBlinkFunction); // Set my function into the above function pointer

    int counter = 0;
    while(counter++ < 3) {
        Blink(2);
    }
    return 0;
}
