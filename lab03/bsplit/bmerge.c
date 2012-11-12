#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "xsum.h"
void newFile(char* newName,char* name, int fileCount);


int main(int argc, char** argv){

  int CHUNK_SIZE=1024;
  int CHECK_CHKSUM=0;
  int fileCount=0;
  int isFinished=1;
  unsigned int givenChecksum = 0,foundChecksum;
  char* prefix, output;
  int opt;
  
  while((opt = getopt(argc, argv,"-hx:o:"))!=-1){
    switch (opt) {
      case 1:
	output = prefix = optarg;
	break;
      case 'h':
	printf("OPTIONS\n\t-h  print a summary of options and exit\n\t-x  print the checksum as a hexadecimal rather than decimal number.\n");
	exit(0);
      case 'x':
	CHECK_CHKSUM=1;
	givenChecksum = atoi(optarg);
	output = prefix = argv[argc-1];
	break;
      case 'o':
	if(optarg!=0) output = optarg;
	prefix = argv[argc-1];
	break;  
      default:
	fprintf(stderr,"Usage: %s [-h] [-x CHECKSUM] [-0 OUTPUT] FILE\n",argv[0]);
	exit(1);
    }
  } 
    
  FILE *fp = fopen(output, "w+");
  
  unsigned char chunk[CHUNK_SIZE];
  memset(chunk,0,CHUNK_SIZE);
  unsigned char checksum = 0;
  int fileSize = 0;
  
 
  while (isFinished){
    
    char * newPrefix[strlen(prefix)+15];
    newPrefixName(newPrefix,prefix,fileCount);
    FILE *chunk = fopen(newPrefix, "r");

    if ((fileSize = fread(&chunk, 1, CHUNK_SIZE, fp))==0) break;
    unsigned int chunksum=0;
    char newFileName[strlen(fileName)+15];  
    fileCount++;
    newFile(newFileName,fileName,fileCount);
    FILE* file = fopen(newFileName,"w+");
    fwrite(&chunksum,sizeof(chunksum),1,file);
    fwrite(&chunk,fileSize,1,file);
    chunksum = chksum(file);
    fileChecksum^=chunksum;
    rewind(file);
    fwrite(&chunksum,sizeof(chunksum),1,file);
    memset(chunk,0,CHUNK_SIZE);
    if (fileSize<CHUNK_SIZE){
      isFinished=0;
      fclose(file);
    }
  }


  if (CALL_CHKSUM==1){
    if (fileChecksum !=0){
      printf("Checksum: 0x%X\n",fileChecksum);
    }
  }

return 0;
}

void newPrefixName(char* newName,char* name, int fileCount){
  char num[5] = {0};
  sprintf(num,"%d",fileCount);
  newName[0] = 0;
  strcat(newName,"parts/");
  strcat(newName,name);
  strcat(newName,".");
  if(fileCount<10) strcat(newName,"0");
  strcat(newName,num);
}