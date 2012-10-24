#include <assert.h>
#include <stdio.h>
#include "bclib.h"

int main (int argc, char **argv){
  int i,j;
  int k=0;
  int *bits;
  
  int barcode[BC_WIDTH][BC_NBITS]={0};
  for(i=1; i<argc; i++){
    for(j=0; argv[i][j]!=0; j++){
      bc_char2bits(argv[i][j],barcode[k]);
      k++;
    }
  k++;
  }
  bc_print(barcode);
  
  
return 0;
}

int bc_print(int** barcode){
  int m,l;  
  for(l=0;l<BC_NBITS;l++){
    for(m=0; m<BC_WIDTH; m++){
      if(barcode[m][l]==0){
	printf(' ');
      }
      else{
	printf('#');
      }
      printf('\n');
      }
    }
}