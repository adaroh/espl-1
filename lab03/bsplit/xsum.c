#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int chksum(FILE* file){
  
  unsigned int word = 0;
  unsigned int checksum = 0;
  fseek(file,sizeof(checksum),SEEK_SET);
  fread(&checksum, 1,sizeof(checksum), file);
  while (fread(&word, 1,sizeof(word), file)){
    checksum^=word;
    word = 0;
  }
  return checksum;
}