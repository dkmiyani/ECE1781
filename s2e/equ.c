/*
gcc -o equivalence-test equivalence-test.c libecho.a -L. -lbusybox
export LD_LIBRARY_PATH=.:$LD_LIBRARY_PATH
./equivalence-test.c
*/

//#include "echo.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "s2e.h"

int main() {

	/* ------------------ COREUTILS ------------------ */

	char buf_cu[128];

	freopen("coreutils.out", "w", stdout);
	// setbuf(stdout, buf);

	//char x[2];
	//s2e_make_symbolic(&x, sizeof(x), "x");
	//char* str[] = {"unused string", x};
	char* str[] = {"unused string", "success!"};

	//s2e_enable_forking();
	printecho(2, str);
	//s2e_disable_forking();

	freopen("cu.out", "w", stdout);

	static const char file_cu[] = "coreutils.out";
	FILE *cu_file = fopen (file_cu, "r");
	if (cu_file != NULL) {
		char line [ 128 ];
		while (fgets(line, sizeof line, cu_file) != NULL) {
			strcpy(buf_cu, line);
		}
		fclose (cu_file);
	}

	printf("buf_cu=<%s>, len=<%d>\n", buf_cu, strlen(buf_cu));

	/* ------------------ BUSYBOX ------------------ */

	char buf_bb[128];
	int j;
	for(j=0; j<128; j++)
		buf_bb[j] = '\0';

		freopen("busybox.out", "w", stdout);
		// setbuf(stdout, buf_bb);
		// NO REDIRECT because busybox echo does not use stdio and ends up corrupting the stdout stream

		char** strarray = malloc(2*sizeof(char*));
		strarray[0] = malloc(256*sizeof(char));
		strarray[1] = malloc(256*sizeof(char));

		strcpy(strarray[0], "echo");
		strcpy(strarray[1], "hello busy world!");
		printbbecho(2, strarray);

		freopen("bb.out", "w", stdout);

		static const char file_bb[] = "busybox.out";
		FILE *bb_file = fopen (file_bb, "r");
		if (bb_file != NULL) {
			char line [ 128 ];
			while (fgets(line, sizeof line, bb_file) != NULL) {
				strcpy(buf_bb, line);
			}
			fclose (bb_file);
		}

		printf("buf_bb=<%s>, len=<%d>\n", buf_bb, strlen(buf_bb));

		//printf("strcmp=%d\n", strcmp(tok, "success!\n"));*/

		//Check the equivalence of the two functions for each path
		//s2e_assert(f1 == f2);
		// s2e assert takes an integer as the first argument so we should be able to just use strcmp

		//In case of success, terminate the state with the
		//appropriate message
		//s2e_kill_state(0, "Success");

		return 0;
	}
	
