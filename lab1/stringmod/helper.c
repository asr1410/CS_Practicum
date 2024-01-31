

#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "helper.h"
#include <stdio.h>

char* helper(char* instr) {

	int len;
	int extra;

	// output string
	char *outstr = NULL;
	// for length string
	char *lenstr = NULL;


	// get length
	len = strlen(instr);
	// for string representing the length
	extra = (int)(ceil(log10(len))+1);

	// space allocated to lenstr to store the len as char with +1 for '\0'
	lenstr = malloc(sizeof(char)*(extra+1));

	// lenstr now has the "5"
	sprintf(lenstr,"%d",len);

	// allocate space for instr and length string
	outstr = malloc(sizeof(char)*(len+extra+1));

	// now copy and concatnate
	strcpy(outstr,instr);
	strcat(outstr,lenstr);
	printf("DEBUG: outstr = %s\n",outstr);
	return(outstr);
}
