#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s2e.h"

int main() {

	/* ------------------ COREUTILS ------------------ */
	char buf[128];
	char tok[10];
	int i;

	char** str = malloc(2*sizeof(char*));
    str[0] = malloc(2*sizeof(char));
    str[1] = malloc(2*sizeof(char));
    memset(str[0], 0, 2);
    memset(str[1], 0, 2);

    //strcpy(str[1], "ab");


	unsigned char x[3];
	s2e_make_symbolic(&x, 2, "x");
	memcpy(str[1], x, 2);

	s2e_enable_forking();
	char * out1 = printecho(2, str);
	char * out2 = printbbecho(2, str);
	//s2e_disable_forking();

//    s2e_get_example(str[1], 2);
//    printf("--> '%c %c' %02x %02x\n", str[1][0], str[1][1],
//         (unsigned char) str[1][0], (unsigned char) str[1][1]);

    s2e_assert(memcmp(out1, out2, 2)==0);
    //s2e_assert(out1[1] == out2[1]);
    
    s2e_kill_state(0, "Success");
	return 0;
}
