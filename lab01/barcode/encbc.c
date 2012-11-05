#include <assert.h>
#include <stdio.h>
#include "bclib.h"

int main (int argc, char **argv){
  int i,j,k,m,l;
  
  int barcode[BC_WIDTH][BC_NBITS]={0};
  for(i=1; i<argc; i++){
      if(i>=2) {bc_char2bits(' ',barcode[k]);k++;}
      for(j=0; argv[i][j]!=0; j++){
	bc_char2bits(argv[i][j],barcode[k]);
	k++;
      }
    }
    for(l=0;l<BC_NBITS;l++){
	for(m=0; m<BC_WIDTH; m++){
	      if(barcode[m][l]==0){
		  printf("%c",' ');
	      } else printf("%c",'#');
	}
	printf("\n");
      }  
    return 0;
}

