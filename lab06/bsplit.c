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
  unsigned int fileChecksum = 0;
  char* fileName;
  int opt;
 ********************************************************************************
 
*************************************************************************************
 // function to open a file
  FILE *fp = fopen(fileName, "r");
  if(fp==0){
    printf("The filename argument you provided is not valid\n");
    return 0;
  }
 *************************************************************************************** 
  unsigned char chunk[CHUNK_SIZE];
  memset(chunk,0,CHUNK_SIZE);
  unsigned char checksum = 0;
  int fileSize = 0;
 *****************************************************************************************
 //function to split the file
  while (isFinished){
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
*****************************************************************************************
//function to check the -x flag and print checksum in hexadecimal
  if (CALL_CHKSUM==1){
    if (fileChecksum !=0){
      printf("Checksum: %u\n",fileChecksum);
    }
  }

return 0;
}
****************************************************************************************
//function to create a new file
void newFile(char* newName,char* name, int fileCount){
  char num[5] = {0};
  sprintf(num,"%d",fileCount);
  newName[0] = 0;
  strcat(newName,"parts/");
  strcat(newName,name);
  strcat(newName,".");
  if(fileCount<10) strcat(newName,"0");
  strcat(newName,num);
}























 //function to read the args and parse them
  while((opt = getopt(argc, argv,"-hx:b:"))!=-1){
    switch (opt) {
      case 1:
	fileName = optarg;
	break;
      case 'h':
	printf("OPTIONS\n\t-h\t\tprint a summary of options and exit\n\t-b SIZE\t\tput at most SIZE bytes per output file\n\t-x\t\tprint the checksum as a hexadecimal rather than decimal number.\n");
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