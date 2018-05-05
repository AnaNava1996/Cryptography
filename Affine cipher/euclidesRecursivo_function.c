#include <stdio.h>

int euclides(int a, int b){
  if(a%b==0){
    return b;}
  else{
    return euclides(b,a%b);}
}

int main(){
  int a,b,c;
  printf("Introduce a:");
  scanf("%d",&a);
  printf("\nIntroduce b:");
  scanf("%d",&b);
  c=euclides(a,b);
  printf("\neuclides(%d,%d)=%d ",a,b,c);
}
