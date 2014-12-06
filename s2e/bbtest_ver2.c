/*
  	make menuconfig
	(enable shared library)
	make
	
	cd ~/busybox/0_lib
	cp libbbusybox.so.1.22.1 libbbusybox.so
	
	cd ~/testProgram
	gcc -o test test.c -L<path/to/0_lib> -lbusybox
	export LD_LIBRARY_PATH=/path/to/0_lib:$LD_LIBRARY_PATH

	./test

ld -r -o tmpecho.o echo.o process_escape_sequence.o perror_msg.o full_write.o
	ar -cvq libbbecho.a tmpecho.o
	
*/
//#include "echo.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

extern int printecho(int argc, char **argv);
extern int lbb_main(char**argv);

#define DEBUG 1

int main()
{
//    char* strarray[] = {"echo", "hello world!", " > output.txt"};
    
    char** strarray = malloc(2*sizeof(char*));
    strarray[0] = malloc(256*sizeof(char));
    strarray[1] = malloc(256*sizeof(char));

    strcpy(strarray[0], "echo");
    strcpy(strarray[1], "hello world!");

    //lbb_main(strarray);
	//printf("return value = %d", ret);
    printecho(2, strarray);

	//free(strarray[0]);
	//free(strarray[1]);

    return 0;
}


/*

 compile this file as follows:
	gcc -o test test.c libecho.a 

 compile echo files as follows to generate static library
	cd coreutils-8.23
	./configure
	make all
	cd src
	 gcc -std=gnu99 -I../lib -O2 -g -c -o echo.o echo.c
	ld -r -o tmpecho.o echo.o ../lib/libcoreutils.a libver.a 
	ar -cvq libecho.a tmpecho.o

*/

/*
#include "echo.h"

int main() {
	char* str[] = {"unused string", "it works!"};
	printecho(2, str);
	return 0;
}
*/

