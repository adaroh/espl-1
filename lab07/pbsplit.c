#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "xsum.h"
void newFile(char* newName,char* name, int fileCount);
void makeChunk(FILE *fp, int CHUNK_SIZE, int fileCount, char *fileName);

int main(int argc, char** argv){

  int CHUNK_SIZE=1024;
  int maxProcess = 10;
  char* fileName;
  int opt;
  
  while((opt = getopt(argc, argv,"-hx:b:p:"))!=-1){
    switch (opt) {
      case 1:
	fileName = optarg;
	break;
      case 'h':
	printf("OPTIONS\n\t-h\t\tprint a summary of options and exit\n\t-b SIZE\t\tput at most SIZE bytes per output file\n\t-x\t\tprint the checksum as a hexadecimal rather than decimal number.\n");
	exit(0);
      case 'x':
	printf("This option has been disabled\n");
	exit(0);
      case 'b':
	if(optarg!=0) CHUNK_SIZE = atoi(optarg);
	fileName = argv[argc-1];
	break;
      case 'p':
      if(optarg!=0) maxProcess = atoi(optarg);
      fileName = argv[argc-1];
      break;  
      default:
	fprintf(stderr,"Usage: %s [-h] [-x] [-b SIZE] FILE\n",argv[0]);
	exit(1);
    }
  } 
  //make sure the file exists
  FILE *fp = fopen(fileName, "r");
  if(fp==0){
    printf("The filename argument you provided is not valid\n");
    return 0;
  }
  //create a parts dir for the files that will be created, if it does not already exist
  struct stat st = {0};
  if (stat("parts", &st) == -1) {
    mkdir("parts", 0700);
  }
  
  fseek(fp,0,SEEK_END);
  int numOfChunks=((ftell(fp) + CHUNK_SIZE-5)/CHUNK_SIZE);
  int fileCount = 1;
  rewind(fp);
  int i,j;
  
  while (numOfChunks>0){
    pid_t pids[maxProcess];
    for (i=0; i<maxProcess; i++){
      pid_t cpid = fork();
      if (cpid == -1) {
	perror("fork");    
	exit(EXIT_FAILURE); 
      }
      if (cpid == 0){
	makeChunk(fp, CHUNK_SIZE, fileCount, fileName);
	exit(0);
      }
      else{
	pids[i]=cpid;
	numOfChunks--;
	fileCount++;
      }
    }
    for(j=0;j<maxProcess;j++){
      waitpid(pids[j],NULL,1);
    }
  }
  fclose(fp);
return 0;
}

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

void makeChunk (FILE *fp, int CHUNK_SIZE, int fileCount, char *fileName){
  int offset = fileCount*CHUNK_SIZE;
  int read = 0;
  unsigned char chunk[CHUNK_SIZE];
  unsigned char checksum = 0;
  fseek(fp,offset,SEEK_SET);
  if ((read = fread(&chunk, 1, CHUNK_SIZE, fp))==0) return;
  unsigned int chunksum=0;
  char newFileName[strlen(fileName)+15];  
  newFile(newFileName,fileName,fileCount);
  FILE* file = fopen(newFileName,"w+");
  fwrite(&chunksum,sizeof(chunksum),1,file);
  fwrite(&chunk,read,1,file);
  chunksum = chksum(file);
  rewind(file);
  fwrite(&chunksum,sizeof(chunksum),1,file);
  fclose(file);
}