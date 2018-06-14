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

int bitsxor(int bits){//hace xor entre todos los bits del numero, devuelve el resultado... es como de paridad de 1's
  unsigned int value = bits;
  unsigned int result = 0;
  while (value) {
    result ^= value & 1;
    value >>= 1;
    }
    return result;
}

int funcion_sbox(int ascii){//según https://crypto.stackexchange.com/questions/10996/how-are-the-aes-s-boxes-calculated
  int LSB=0;
  int MSB=0;
  int bits,bits2;

  for(int i=1;i<=8;i++){
    printf("%x ",bitsxor(ascii&ror(31,i)));
    bits=bitsxor(ascii&ror(31,i));
    LSB+=(pow(2,8-i)*bits);//sumo el resultado del XOR multiplicado por 2 a la (8-i)potencia.
    MSB+=(pow(2,i-1)*bits);
  }
  /*for(int i=1;i<=4;i++){//rotacion de 1F en la que vamos... 0-1F 1-8F 2-C7 3-E3 4-F1 5-F8 6-7C 7-3E 8-1f
    //printf("\n%x",ascii&ror(31,i));//imprime el AND entre la rotación de 1F y el byte de la cadena a cifrar.
    //printf("\n%x",bitsxor(ascii&ror(31,i)));//imprime el resultado de aplicar xor en los bits del AND anterior
    bits=bitsxor(ascii&ror(31,i));
    LSB+=(pow(2,4-i)*bits);//sumo el resultado del XOR multiplicado por 2 a la (8-i)potencia.
    MSB+=(pow(2,i+3)*bits);
    bits2=bitsxor(ascii&ror(31,i+4));
    LSB+=(pow(2,8-i)*bits2);//sumo el resultado del XOR multiplicado por 2 a la (8-i)potencia.
    MSB+=(pow(2,i-1)*bits2);
    printf("\n%x %x",bits,bits2);
  }*/

  printf("\nLSB=%x y MSB=%x   ",LSB,MSB);//¿Cual debo usar?
  return MSB^99;
}

int main(){
  char mensaje[16]={'T','h','a','t','s',' ','m','y',' ','K','u','n','g',' ','F','u'};
  char cipherKey[16]={'T','w','o',' ','O','n','e',' ','N','i','n','e',' ','T','w','o'};

  //0  1f  e  54  3c  4e  8  59  6e  22  1b  b  47  74  31  1a
  //63  c0  ab  20  eb  2f  30  cb  9f  93  af  2b  a0  92  c7  a2
  printf("\n%x",funcion_sbox(53));

}


/*para ver el mensaje y llave en hexa
for(int i=0; i<15;i++){
  sprintf(mhex[i],"%x",mensaje[i]);
  sprintf(llhex[i],"%x",llave[i]);
  printf("%s",mhex[i]);
}*/



/*Este pedazo de codigo era para crear una cadena dinamica... y pasarla al ascii hexadecimal en un archivo
char c,*cad;//cadena dinamica
int i=0;
cad= (char *)malloc(sizeof(char));

FILE *arch;
arch=fopen("D:\\Users\\ana_n\\Documents\\IPN n.n\\6to Semestre\\Cryptography\\c2.txt","a+");

printf("Introduzca la cadena a cifrar: ");
while((c=getchar())!='\n'){
  realloc(cad,(sizeof(char)));
  cad[i++]=c;
  fprintf(arch,"%x ",c);
}
cad[i]='\0';





*/

/*
  FILE *arch;
  arch=fopen("D:\\Users\\ana_n\\Documents\\IPN n.n\\6to Semestre\\Cryptography\\m.txt","r");
  do {
     c = fgetc(arch);
     if( feof(arch) ) {
        break ;
     }
     if(op==1){
       c-=32;}
     if(op==2){
       c+=32;
     }
     escritura(c,op);
  } while(1);
  fclose(arch);
*/
