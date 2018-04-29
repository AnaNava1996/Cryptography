#include <stdio.h>

int bitsxor(int bits){//hace xor entre todos los bits del numero, devuelve el resultado... es como de paridad de 1's
  unsigned int value = bits;
  unsigned int result = 0;
  while (value) {
    result ^= value & 1;
    value >>= 1;
    }
    return result;
}

int main(){
  //1 devuelve 1, 2 devuelve 1, 3 devuelve 0, 4 devuelve 1, 5 devuelve 0, 7 devuelve 1... y así
  printf("%d",bitsxor(3));
}
