#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int ror(int row2,int n){//función para el "circular right shift"   1F --> 00011111 --> 10001111
  while(n!=0){
    if(row2%2==0){
      row2=row2>>1;
      return ror(row2,n-1);
    }
    else{
      row2=row2>>1;
      row2+=128;
      return ror(row2,n-1);
    }
  }
  if(n==0){
    return(row2);
  }
}


int main(){//ror it's an important function tu make the sbox from scratch
  //31 ---> 00011111
  for(int i=0;i<=8;i++){
    //0-1F 1-8F 2-C7 3-E3 4-F1 5-F8 6-7C 7-3E 8-1f
    printf("%x  ",ror(31,i));
  }
}
