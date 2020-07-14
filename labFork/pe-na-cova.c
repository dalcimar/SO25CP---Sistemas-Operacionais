#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
   pid_t childpid = 0; 
   int i, n;
 
   
  
   for (;;)
	if ((childpid = fork()) <= 0) { 
		return 0;
	} else sleep (1);
 
   return 0; 
}
