#include <stdio.h>

int f(int a, int b){
  int c,d;
  c = a+b;
  d = a-b;
  printf("%d\t%d\n",c,d);
  return c+d;
}

int g(int a, int b){
  int c,d;
  printf("%d\t%d\t%d\t%d\n",a,b,c,d);
  c = a;
  d = b+b;
  return c+d;
}

int main(){
  printf("Res: %d\n",f(1,2));
  printf("Res: %d\n",g(3,4));
  return 0;
}
