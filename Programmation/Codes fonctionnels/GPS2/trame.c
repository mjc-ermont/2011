#include <string.h>

int get_checksum(char *trame){
	int check, i;
	int c; 
	
	for (i = 0 ; i < strlen(trame) ; i++){
		c = (unsigned char)trame[i];
		if (c != '$' && c!=) check ^= c;
	}
	
	return check;
}