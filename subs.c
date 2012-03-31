/*Date: March 31, 2012
Desc: Prints out all the substrings*/

#include <string.h>
#include <stdio.h>

int main() {
	
	int i, j, len;
	char string[100] = "jisuka";

	len = strlen(string);

	for (i = 1; i <= len; i++, printf("\n")) 
		for (j = 0; i + j <= len; j++)		
			printf("%.*s\t", i, string + j);

	return 0;
}
