#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int chksum(FILE* fp){
  
  unsigned int word = 0,read=0;
  unsigned int checksum = 0;
  fseek(fp,sizeof(checksum),SEEK_SET);
  fread(&checksum, 1,sizeof(checksum), fp);
  while ((read = fread(&word, 1,sizeof(word), fp))!=0){
    checksum ^= word;
    word = 0;
  }
  return checksum;
}