#include <stdio.h>

int main (){
  int x = 3;
  int z=0;
  z |= 1 << 3;
  printf("%d \n", z);
  
  return 0;
}
