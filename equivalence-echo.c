/*
* Compile me with gcc -I ~/s2e/s2e/guest/include/ -std=c99 -m32 -o equivalence-echo equivalence-echo.c
*		-m32 => forces 32 bit compilation
*		-I <arg> => includes the s2e.h library required for s2e_* calls
*/

#include <inttypes.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <s2e.h>

int main() {

  FILE* pipe;
  char command[70];
  char x[2]; // = "abcd";
  int len;

  //Make x symbolic
  s2e_make_symbolic(&x, sizeof(x), "x");

  len = snprintf(command, sizeof(command), "echo %s", x);

  if (len <= sizeof(command)) {
    s2e_enable_forking();
    pipe = popen(command, "r");
    s2e_disable_forking();
  } else
    printf("Error: snprintf failed.\n");

    char buf[100];
    fread(buf, 1, 1024, pipe);

    char result[10];
    len = snprintf(result, sizeof(result), "%.4s", buf);
    printf("Result: <%s>\n", result);

    if(pclose(pipe) < 0)
      printf("Error: Couldn't close pipe.\n");

      /*uint64_t f1 = factorial1(x, max);
      uint64_t f2 = factorial2(x, max);*/

      //Check the equivalence of the two functions for each path
      //s2e_assert(f1 == f2);

      //In case of success, terminate the state with the
      //appropriate message
      //s2e_kill_state(0, "Success");
      return 0;
    }
    
