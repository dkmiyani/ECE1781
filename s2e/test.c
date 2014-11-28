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
	
*/

/*
extern int lbb_main(char **argv);

int main()
{
    char* strarray[] = {"echo", "hello world!", 0};
    lbb_main(strarray);

    return 0;
}

*/

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

#include "echo.h"

int main() {
	char* str[] = {"unused string", "it works!"};
	printecho(2, str);
	return 0;
}
