#include <stdio.h>
#include <stdlib.h>


void funcExmpl(int A, int B) {printf("FNC: %d %d\n", A, B);} // FUCNTION (it contains address [as value] {funcExmpl})

int main()
{
    char varChar = 0; // VARIABLE (it contains value {varChar} at address {&varChar})
    char *varCharPtr = &varChar; // POINTER (at address {&varCharPtr} it contains address [as value] {varCharPtr} to value {*varCharPtr})
    char varArrChar[3] = {"000"}; // ARRAY (it contains address [as value] {varArrChar} to value {*varArrChar})
    

    // VARIABLE
    varChar = 'A';

    // POINTER
    *varCharPtr = 'B';

    // ARRAY
    *varArrChar = 'A'; // == varArrChar[0]
    varArrChar[1] = 'B';
    *(varArrChar+2) = 'C';
    
    printf("<%c> - <%c> <%c> <%c>\n", varChar, *varArrChar, *(varArrChar+1), varArrChar[2]);

    
    // ARRAY STRING on HEAP OR STACK
    varCharPtr = "String1"; // ON HEAP - pointer to address to string
    char varCharArr[] = "String2"; // ON STACK - variable length array (VLA), its size is determined at runtime
    printf("<%s> <%s>\n", varCharPtr, varCharArr);

    // FUNCTION
    void (*funcPtr)(int, int) = funcExmpl; // save function address to function pointer
    funcPtr(1, 7);






    // POINTERS basics
    printf("\n\n\n");
    int a, *p_a;
    a = 56;
    p_a = &a; // Stores the address of variable a in p_a
    printf("The pointer p_a has the value %p and points to the value %d\n", p_a, *p_a);
    *p_a = 15; // Stores the value 15 at the address in p_a
    printf("The pointer p_a has the value %p and points to the value %d\n", p_a, *p_a);
    a = 20;
    printf("The pointer p_a has the value %p and points to the value %d\n", p_a, *p_a);

    printf("The pointer to pointer p_a has the value %p and points to the value %p. Pointer to a has the value %p\n\n", &p_a, *(&p_a), &a);



    p_a = (int *) malloc(sizeof(int) * 2);
    if (p_a == NULL) {printf("Not enough memory.\n"); return -1;}
    *p_a = 0;
    *(p_a+1) = 2;
    printf("First: %d; Second: %d\n\n",*p_a,*(p_a+1));



    int i, *p_i1, **p_i2;
    i = 1;
    printf("Pointer 'i': address = %p, value = %d\nPointer 'p_i1': address = NULL, value = NULL, address of address = NULL\nPointer 'p_i2': address = NULL, value = NULL, address of address = NULL\n\n", &i, i);
    p_i1 = &i;
    printf("Pointer 'i': address = %p, value = %d\nPointer 'p_i1': address = %p, value = %d, address of address = %p\nPointer 'p_i2': address = NULL, value = NULL, address of addresses = NULL\n\n", &i, i,p_i1,*p_i1,&p_i1);
    *p_i1 = 2;
    printf("Pointer 'i': address = %p, value = %d\nPointer 'p_i1': address = %p, value = %d, address of address = %p\nPointer 'p_i2': address = NULL, value = NULL, address of addresses = NULL\n\n", &i, i,p_i1,*p_i1,&p_i1);
    i = *p_i1+1;
    printf("Pointer 'i': address = %p, value = %d\nPointer 'p_i1': address = %p, value = %d, address of address = %p\nPointer 'p_i2': address = NULL, value = NULL, address of addresses = NULL\n\n", &i, i,p_i1,*p_i1,&p_i1);
    p_i2 = &p_i1;
    printf("Pointer 'i': address = %p, value = %d\nPointer 'p_i1': address = %p, value = %d, address of address = %p\nPointer 'p_i2': address = %p, value = %p , address of address = %p\n\n", &i, i,p_i1,*p_i1,&p_i1,p_i2,*p_i2,&p_i2);
    //printf("Pointer 'i': address = %p, value = %d\nPointer 'p_i1': address = %p, value = %d\nPointer 'p_i2': address = %p, value = %d\n\n", &i, i,p_i1,*p_i1,p_i2,*p_i2);



    free(p_a);

    return (EXIT_SUCCESS);
}
