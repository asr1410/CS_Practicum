
#include <stdio.h>
#include <stdlib.h>
#include "helper.h"

int main(int argc, char *argv[]) {

	char *outstr = NULL;

	if (argc != 2) {
		printf("This pgm appends a string with its length. Eg. \'hello\' outputs \'hello5\'\n");
		printf("Usage: stringmod string\n");
		exit(-1);
	}
	printf("Passed\n");

	outstr = helper(argv[1]);
	printf("Out: %s\n", outstr);

}
