#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "xsum.h"
void getNewPrefix(char* newName,char* name, int fileCount);


int main(int argc, char** argv){

  int CHUNK_SIZE=1024;
  int CHECK_CHKSUM=0;
  int fileCount=0;
  unsigned int givenChecksum = 0,foundChecksum=0;
  char *prefix,*output;
  int opt,outputChanged=0;
  
  while((opt = getopt(argc, argv,"-hx:o:"))!=-1){
    switch (opt) {
      case 1:
	prefix = optarg;
	break;
      case 'h':
	printf("OPTIONS\n\t-h\t\tprint summary of options and exit\n\t-o OUTPUT\twrite the output into OUTPUT instead of PREFIX\n\t-x CHECKSUM\tverify that the checksum of the produced file is CHECKSUM\n");
	exit(0);
      case 'x':
	CHECK_CHKSUM=1;
	givenChecksum = atoi(optarg);
	prefix = argv[argc-1];
	break;
      case 'o':
	if(optarg!=0) output = optarg;
	outputChanged = 1;
	prefix = argv[argc-1];
	break;  
      default:
	fprintf(stderr,"Usage: %s [-h] [-x CHECKSUM] [-0 OUTPUT] FILE\n",argv[0]);
	exit(1);
    }
  } 
  struct stat st = {0};
  if (stat("parts", &st) == -1) {
    printf("Could not find the \"parts\" folder created by bsplit\n");
    exit(0);
   }
  if(outputChanged==0) output = prefix;  
  FILE *fp = fopen(output, "a");
  char chunk[1];
  unsigned int chunksum=0, calcSum=0;
  int fileSize = 0;
  int firstChunk = 0; 
  int read;
  
  while (1){
    fileCount++;
    char newPrefix[strlen(prefix)+15];
    getNewPrefix(newPrefix,prefix,fileCount);
    FILE *chunkFile = fopen(newPrefix, "r");
    if(chunkFile==0){
      if(fileCount==1){
	printf("Could not find the file %s\n",newPrefix);
	exit(0);
      }
      else{
	fclose(fp);
	break;
      }
    }
    if(fread(&chunksum, sizeof(chunksum),1,chunkFile)==0) {
      printf("Could not read from the file %s\n",newPrefix);
      exit(0);
    }
    calcSum = chksum(chunkFile);
    fseek(chunkFile,sizeof(chunksum),SEEK_SET);
    if(calcSum!=chunksum){
      printf("The Checksum for %s is not identical to the stored value\n",newPrefix);
      exit(0);
    }
    while ((fread(chunk, 1, 1, chunkFile))!=0){
      fwrite(&chunk,1,1,fp);
    }
    if(firstChunk==0){
      foundChecksum = chunksum;
      firstChunk = 1;
    } else {
      foundChecksum^=chunksum;
    }
    chunksum = calcSum = 0;
    fclose(chunkFile);
  }

  if (CHECK_CHKSUM==1){
    if (givenChecksum != foundChecksum){
      printf("The given Checksum is not identical to the calculated Checksum - something went wrong :-(\n");
    }
    else{
      printf("The Checksums are identical!\n");
    }
  }

return 0;
}

void getNewPrefix(char* newName,char* name, int fileCount){
  char num[5] = {0};
  sprintf(num,"%d",fileCount);
  newName[0] = 0;
  strcat(newName,"parts/");
  strcat(newName,name);
  strcat(newName,".");
  if(fileCount<10) strcat(newName,"0");
  strcat(newName,num);
}