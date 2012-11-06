#include <stdio.h>
#include <unistd.h>


int main(int argc, char** argv){
  
  int FLAG=0;
  char* fileName;
  
  char opt = getopt(argc, argv, "hx:") {
    switch (opt) {
      case 'h':
	printf("\nOPTIONS\n\t-h  print a summary of options and exit\n\t-x  print the checksum as a hexadecimal rather than decimal number.");
	exit(0);
      case 'x':
	FLAG=1;
        break;
      default:
	fprintf(stderr,"Usage: %s [-h] [-x] FILE\n",argv[0]);
	exit(EXIT_FAILURE);
    }
    char* fileName = optarg;
  }
  
  unsigned int word;
  unsigned int checksum;
  FILE fp = fopen(filename, "r");
  if(fp==NULL){
    printf("The file name provided is not valid");
    return 1;
  }
  fread(&checksum, sizeof(checksum), 1, fp);
  while (fread(&word, sizeof(word), 1, fp)){
    checksum^=word;
  }
  if (FLAG==1){
    
  
    
    
    
    
    
    
    
    
    
    
    
    	fileName = optarg;
	fileName = optarg;
fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                           argv[0]);
                   exit(EXIT_FAILURE);
fprintffprintffprintf