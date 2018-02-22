#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void subKey(unsigned char *state,unsigned char *key){
  for(int i=0;i<16;i++){
    state[i]=state[i]^key[i];}
}

void print_men(unsigned char *men){
  printf("\n");
  for(int i=0;i<16;i++){
    printf("%x  ",men[i]);}
}

int subBytes(int s,int *sbox){
  unsigned int fila,columna;
  fila=s/16;
  columna=s%16;
  return sbox[(fila*16)+columna];
}

void shift_rows(unsigned char *state){//fuerza bruta pero funciona
  int tmp,tmp2;
  //indices 0-4-8-12 forman la primera columna que no cambia
  tmp=state[1];//indices 1-5-9-13 forman una columna
  state[1]=state[5];
  state[5]=state[9];
  state[9]=state[13];
  state[13]=tmp;
  tmp=state[2];//indices 2-6-10-14 forman la tercera columna
  tmp2=state[6];
  state[2]=state[10];
  state[6]=state[14];
  state[10]=tmp;
  state[14]=tmp2;
  tmp=state[15];//indices 3-7-11-15 forman la ultima columna que rota 3 veces o una sola en sentido inverso.
  state[15]=state[11];
  state[11]=state[7];
  state[7]=state[3];
  state[3]=tmp;
}

void mix_column(unsigned char *r){//función modificada wikipedia https://en.wikipedia.org/wiki/Rijndael_MixColumns#Implementation_example
  unsigned char a[16];
  unsigned char b[16];
  unsigned char c;
  unsigned char h;

  for(c=0;c<16;c++){
    a[c]=r[c];
    h=(unsigned char)((signed char)r[c] >> 7);
    b[c] = r[c] << 1;
    b[c] ^= 0x1B & h;
  }
  for(int i=0;i<4;i++){
    r[0+(4*i)] = b[0+(4*i)] ^ a[3+(4*i)] ^ a[2+(4*i)] ^ b[1+(4*i)] ^ a[1+(4*i)]; /* 2 * a0 + a3 + a2 + 3 * a1 */
    r[1+(4*i)] = b[1+(4*i)] ^ a[0+(4*i)] ^ a[3+(4*i)] ^ b[2+(4*i)] ^ a[2+(4*i)]; /* 2 * a1 + a0 + a3 + 3 * a2 */
    r[2+(4*i)] = b[2+(4*i)] ^ a[1+(4*i)] ^ a[0+(4*i)] ^ b[3+(4*i)] ^ a[3+(4*i)]; /* 2 * a2 + a1 + a0 + 3 * a3 */
    r[3+(4*i)] = b[3+(4*i)] ^ a[2+(4*i)] ^ a[1+(4*i)] ^ b[0+(4*i)] ^ a[0+(4*i)]; /* 2 * a3 + a2 + a1 + 3 * a0 */
  }
}

void make_roundkey(unsigned char *rk,unsigned char *lk,int *sbox,int RCON){
  //ultima columna indices 12-13-14-15
  rk[0]=lk[13];//circular byte left shift
  rk[1]=lk[14];
  rk[2]=lk[15];
  rk[3]=lk[12];
  for(int i=0;i<4;i++){//byte substitution s-box
    rk[i]=subBytes(rk[i],sbox);}
  rk[0]=rk[0]^(RCON)^lk[0];
  for(int i=1;i<4;i++){
    rk[i]=rk[i]^lk[i];}
  for(int i=4;i<16;i++){
    rk[i]=rk[i-4]^lk[i];}
  printf("\n\nRoundkey: \n");
  for(int i=0;i<16;i++){
    printf("%x  ",rk[i]);}
}


int main(){
  int sbox[256] = {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

unsigned char cipherKey[16]={'T','h','a','t','s',' ','m','y',' ','K','u','n','g',' ','F','u'};//los primeros 4 bytes son una columnas
unsigned char mensaje[16]={'T','w','o',' ','O','n','e',' ','N','i','n','e',' ','T','w','o'};
//unsigned char mensaje[16]={0x32,0x43,0xf6,0xa8,0x88,0x5a,0x30,0x8d,0x31,0x31,0x98,0xa2,0xe0,0x37,0x07,0x34};//los primeros 4 bytes son una columna
//unsigned char cipherKey[16]={0x2b,0x7e,0x15,0x16,0x28,0xae,0xd2,0xa6,0xab,0xf7,0x15,0x88,0x09,0xcf,0x4f,0x3c};
//unsigned char subkey[16];
unsigned char roundkey1[16];
unsigned char roundkey2[16];
unsigned char roundkey3[16];
unsigned char roundkey4[16];
unsigned char roundkey5[16];
unsigned char roundkey6[16];
unsigned char roundkey7[16];
unsigned char roundkey8[16];
unsigned char roundkey9[16];
unsigned char roundkey10[16];

printf("Mensaje hex");
print_men(mensaje);

printf("\n\nSub key");
subKey(mensaje,cipherKey);//esto podría dar error después... no se esta igualando subkey[] al mensaje
print_men(mensaje);

printf("\n\nSub bytes\n");
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);
  printf("%x  ",mensaje[i]);
}

printf("\n\nShift Rows: ");
shift_rows(mensaje);
print_men(mensaje);

printf("\n\nMix columns: ");
mix_column(mensaje);
print_men(mensaje);

//add roundkey, round 1
make_roundkey(roundkey1,cipherKey,sbox,0x01);
subKey(mensaje,roundkey1);
print_men(mensaje);

//round 2
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey2,roundkey1,sbox,0x02);
subKey(mensaje,roundkey2);
print_men(mensaje);


//round 3
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey3,roundkey2,sbox,0x04);
subKey(mensaje,roundkey3);
print_men(mensaje);


//round 4
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey4,roundkey3,sbox,0x08);
subKey(mensaje,roundkey4);
print_men(mensaje);


//round 5
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey5,roundkey4,sbox,0x10);
subKey(mensaje,roundkey5);
print_men(mensaje);


//round 6
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey6,roundkey5,sbox,0x20);
subKey(mensaje,roundkey6);
print_men(mensaje);


//round 7
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey7,roundkey6,sbox,0x40);
subKey(mensaje,roundkey7);
print_men(mensaje);


//round 8
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey8,roundkey7,sbox,0x80);
subKey(mensaje,roundkey8);
print_men(mensaje);


//round 9
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
mix_column(mensaje);
make_roundkey(roundkey9,roundkey8,sbox,0x1b);
subKey(mensaje,roundkey9);
print_men(mensaje);


//round 10
for(int i=0;i<16;i++){
  mensaje[i]=subBytes(mensaje[i],sbox);}
shift_rows(mensaje);
make_roundkey(roundkey10,roundkey9,sbox,0x36);
subKey(mensaje,roundkey10);
printf("\n\nCIPHERTEXT:    ");
print_men(mensaje);


}


/*REFERNCIAS
https://kavaliro.com/wp-content/uploads/2014/03/AES.pdf
https://www.youtube.com/watch?v=EBTO9_imXSc&t=495s
https://en.wikipedia.org/wiki/Rijndael_S-box
https://crypto.stackexchange.com/questions/2418/how-to-use-rcon-in-key-expansion-of-128-bit-advanced-encryption-standard
*/
