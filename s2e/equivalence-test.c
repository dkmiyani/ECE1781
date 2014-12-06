/* 
	gcc -o equivalence-test equivalence-test.c libecho.a -L<path/to/0_lib> -lbusybox
	export LD_LIBRARY_PATH=</path/to/0_lib>:$LD_LIBRARY_PATH
	./equivalence-test.c
*/

#include "echo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s2e.h"

int main() {

	/* ------------------ COREUTILS ------------------ */

	char buf[128];
	freopen("coreutils.out", "w", stdout);
	setbuf(stdout, buf);

	//char x[2];
	//s2e_make_symbolic(&x, sizeof(x), "x");
	//char* str[] = {"unused string", x};
	char* str[] = {"unused string", "success!"};

	//s2e_enable_forking();
	printecho(2, str);
	//s2e_disable_forking();

	freopen("cu.out", "w", stdout);

	// manual string copy because using any string library function on 
	// the buffer results in a seg fault for some reason...
	char tok[10];
	int i;
	for (i = 0; i <= strlen(buf); i++)
		if (buf[i] == '\0') {
			tok[i] = '\0';
			break;
		} else 
			tok[i] = buf[i];

	printf("buf=<%s>, len=<%d>\n", tok, strlen(buf));

	/* ------------------ BUSYBOX ------------------ */

	char buf_bb[128];
	freopen("busybox.out", "w", stdout);
	setbuf(stdout, buf_bb);

	char** strarray = malloc(2*sizeof(char*));
    strarray[0] = malloc(256*sizeof(char));
    strarray[1] = malloc(256*sizeof(char));

    strcpy(strarray[0], "echo");
    strcpy(strarray[1], "hello busy world!");
    printecho(2, strarray);

	freopen("bb.out", "w", stdout);

	// manual string copy because using any string library function on 
	// the buffer results in a seg fault for some reason...
	char tok_bb[10];

	for (i = 0; i <= strlen(buf_bb); i++)
		if (buf[i] == '\0') {
			tok[i] = '\0';
			break;
		} else 
			tok_bb[i] = buf_bb[i];

	printf("buf_bb=<%s>, len=<%d>\n", tok_bb, strlen(buf_bb));

	//printf("strcmp=%d\n", strcmp(tok, "success!\n"));

	//Check the equivalence of the two functions for each path
    //s2e_assert(f1 == f2); 
	// s2e assert takes an integer as the first argument so we should be able to just use strcmp

    //In case of success, terminate the state with the
    //appropriate message
    //s2e_kill_state(0, "Success");

	return 0;
}
