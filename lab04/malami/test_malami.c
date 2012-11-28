#include <stdlib.h>
#include <stdio.h>

extern int malami();

int main(int argc, char **argv) {
  int num = malami(argv[argc-1]);
  printf("the number you entered is: %d\n",num);
	return 0;
}
