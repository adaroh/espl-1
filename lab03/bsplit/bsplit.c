#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "xsum.h"
void newFile(char* newName,char* name, int fileCount);


int main(int argc, char** argv){

  int CALL_CHKSUM=0;
  int CHUNK_SIZE=1024;
  int fileCount=0;
  int isFinished=1;
  unsigned int fileChecksum = 0;
  char* fileName;
  int opt;
  
  while((opt = getopt(argc, argv,"-hx:b:"))!=-1){
    switch (opt) {
      case 1:
	fileName = optarg;
	break;
      case 'h':
	printf("OPTIONS\n\t-h  print a summary of options and exit\n\t-x  print the checksum as a hexadecimal rather than decimal number.\n");
	exit(0);
      case 'x':
	CALL_CHKSUM=1;
	fileName = argv[argc-1];
	break;
      case 'b':
	if(optarg!=0) CHUNK_SIZE = atoi(optarg);
	fileName = argv[argc-1];
	break;  
      default:
	fprintf(stderr,"Usage: %s [-h] [-x] [-b SIZE] FILE\n",argv[0]);
	exit(1);
    }
  } 
  printf("1\n");
  FILE *fp = fopen(fileName, "r");
  if(fp==0){
    printf("The filename argument you provided is not valid\n");
    return 0;
  }
  printf("2\n");//*****************************8
  unsigned char chunk[CHUNK_SIZE];
  memset(chunk,0,CHUNK_SIZE);
  unsigned char checksum = 0;
  int fileSize = 0;
  struct stat st = {0};
  if (stat("parts", &st) == -1) {
    mkdir("parts", 0700);
  }
   printf("3\n");//*****************************8
 
  while (isFinished){
    if ((fileSize = fread(&chunk, 1, CHUNK_SIZE, fp))==0) break;
    unsigned int chunksum=0;
    char newFileName[strlen(fileName)+15];  
       printf("4\n");//*****************************8

    newFile(newFileName,fileName,fileCount);
       printf("5\n");//*****************************8

    FILE* file = fopen(newFileName,"w");
    fwrite(&chunksum,sizeof(chunksum),1,file);
    fwrite(&chunk,fileSize,1,file);
    chunksum = chksum(file);
    fileChecksum ^= chunksum;
    rewind(file);
    fwrite(&chunksum,sizeof(chunksum),1,file);
    memset(chunk,0,CHUNK_SIZE);
    if (fileSize<CHUNK_SIZE){
      isFinished=0;
      fclose(file);
    }
  }


  if (CALL_CHKSUM==1){ //need to change here - calculate chksum during split
    if (checksum !=0){
      printf("Checksum: 0x%X\n",fileChecksum);
    }
  }

return 0;
}

void newFile(char* newName,char* name, int fileCount){
  fileCount++;
  char num[5] = {0};
  sprintf(num,"%d",fileCount);
  newName[0] = 0;
  strcat(newName,"parts/");
  strcat(newName,name);
  strcat(newName,".");
  if(fileCount<10) strcat(newName,"0");
  strcat(newName,num);
}