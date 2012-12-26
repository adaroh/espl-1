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
	printf("Usage: %s [-h] [-x] [-b SIZE] [-p PROCESSES] FILE\n\nOPTIONS\n\t-h\t\tprint a summary of options and exit\n\t-b SIZE\t\tput at most SIZE bytes per output file\n\t-x\t\tprint the checksum of the file.(DISABLED)\n\t-p\t\tmaximum number of child processes.\n",argv[0]);
	exit(0);
      case 'x':
	printf("The -x option has been disabled\n");
	exit(0);
      case 'b':
	if(optarg!=0) CHUNK_SIZE = atoi(optarg);
	fileName = argv[argc-1];
	break;
      case 'p':
      if(optarg!=0) maxProcess = atoi(optarg);
      if(maxProcess<=0){
	printf("Please provide a valid number of processes");
	exit(0);
      }
      fileName = argv[argc-1];
      break;  
      default:
	fprintf(stderr,"Usage: %s [-h] [-x DISABLED] [-b SIZE] [-p PROCESSES] FILE\n",argv[0]);
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
  int numOfChunks=((ftell(fp) + CHUNK_SIZE-1)/CHUNK_SIZE);
  rewind(fp);
  int fileCount = 1;
  int i,j;
  
  while (numOfChunks>0){
    int min = (maxProcess <= numOfChunks ? maxProcess : numOfChunks);
    pid_t pids[min];
    for (i=0; i<min; i++){
      pid_t cpid = fork();
      if (cpid == -1) {
	perror("fork");    
	exit(EXIT_FAILURE); 
      }
      else if (cpid == 0){
	makeChunk(fp, CHUNK_SIZE, fileCount, fileName);
      }
      else{
	pids[i]=cpid;
	numOfChunks--;
	fileCount++;
      }
    }
    for(j=0;j<min;j++){
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
  //freopen(fileName,"r",fp); //without this the data in the chunks is not correct
  int offset = ((fileCount-1)*CHUNK_SIZE);
  int read = 0;
  unsigned int chunksum=0;
  unsigned char chunk[CHUNK_SIZE];
  unsigned char checksum = 0;
  fseek(fp,offset,SEEK_SET);
  if ((read = fread(&chunk, 1, CHUNK_SIZE, fp))==0) return;
  char newFileName[strlen(fileName)+15];  
  newFile(newFileName,fileName,fileCount);
  FILE* file = fopen(newFileName,"w+");
  fwrite(&chunksum,sizeof(chunksum),1,file);
  fwrite(&chunk,read,1,file);
  chunksum = chksum(file);
  rewind(file);
  fwrite(&chunksum,sizeof(chunksum),1,file);
  fclose(file);
  exit(0);
}