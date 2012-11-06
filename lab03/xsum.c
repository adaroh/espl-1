#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv){
  
  int FLAG=0;
  char* fileName;
  int opt;
  if((opt = getopt(argc, argv,"-hx:"))!=-1){
    switch (opt) {
      case 1:
	fileName = optarg;
	break;
      case 'h':
	printf("OPTIONS\n\t-h  print a summary of options and exit\n\t-x  print the checksum as a hexadecimal rather than decimal number.\n");
	exit(0);
      case 'x':
	FLAG=1;
	fileName = optarg;
	break;
      default:
	fprintf(stderr,"Usage: %s [-h] [-x] FILE\n",argv[0]);
	exit(1);
    }
  } else {
    printf("Please provide a filename argument\n");
    return 0;
  }

  
  unsigned int word;
  unsigned int checksum;
  FILE *fp = fopen(fileName, "r");
  if(fp==0){
    printf("The filename argument you provided is not valid\n");
    return 0;
  }
  fread(&checksum, sizeof(checksum), 1, fp);
  while (fread(&word, sizeof(word), 1, fp)){
    checksum^=word;
  }
  if (FLAG==1){
    printf("0x%X\n",checksum);
  } else {
    printf("%d\n",checksum);
  }
  fclose(fp);
  
  return 0;
}