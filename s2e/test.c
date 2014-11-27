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
extern int lbb_main(char **argv);

int main()
{
    char* strarray[] = {"echo", "hello world!", 0};
    lbb_main(strarray);

    return 0;
}