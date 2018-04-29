#include <stdio.h>//agregar una llave.... para hacer un corrimiento si la lalve es 1, devolver a->B 32+1

int escritura(int c,int op){
  FILE *archi;
  if(op==1){
    archi=fopen("c.txt","a+");}
  if(op==2){
    archi=fopen("m.txt","a+");}//modificar para que borre
  fputc(c,archi);
  fclose(archi);}

int lectura(int op,int key,int alfa){
  int c;
  FILE *arch;
  if(op==1){
    arch=fopen("D:\\Users\\ana_n\\Documents\\IPN n.n\\6to Semestre\\Cryptography\\Affine cipher\\m.txt","r");}
  if(op==2){
    arch=fopen("D:\\Users\\ana_n\\Documents\\IPN n.n\\6to Semestre\\Cryptography\\Affine cipher\\c.txt","r");
  }
  if(arch == NULL) {
     perror("Error in opening file");
     return(-1);
  } do {
     c = fgetc(arch);
     if( feof(arch) ) {
        break ;
     }
     if(op==1){
       c=(((c-97)*alfa+key)%26)+65;}//alfa*m + beta mod26
     if(op==2){
       c=(((c-65+key)*alfa)%26)+97;}
     escritura(c,op);
  } while(1);
  fclose(arch);
}

int main(){
  int op,key,alfa,a,b;
  printf("1-Encrypt,2-Decrypt: ");
  scanf("%d",&op);
  printf("\nAlfa: ");
  scanf("%d",&alfa);
  printf("\nBeta: ");
  scanf("%d",&key);
  if(op==2){
    for(int i=1;i<26;i++){
      if(((alfa*i)%26)==1){
        a=i;
        printf("alfa-1: %d  ",a);}}
    for(int i=0;i<26;i++){
      if((key+i)%26==0){
        b=i;
        printf("-beta= %d  ",b);}
    }
    lectura(op,b,a);
    }
  else{
    lectura(op,key,alfa);}
  }
