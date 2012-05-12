#include <string.h>
#include <stdlib.h>
 
char *get_checksum(char *trame){
	unsigned int check, i;
	int c;
        char buffer[17];
	
	for (i = 0 ; i < strlen(trame) ; i++){
		c = (unsigned char)trame[i];
		if (c != '$' && c!='#') check ^= c;
	}
	
	itoa(check, buffer, 10);
        return buffer;
}
