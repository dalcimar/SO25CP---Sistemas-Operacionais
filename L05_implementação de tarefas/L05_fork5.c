#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[]){
	pid_t pid; 
	int i, n;

	if (argc != 2){  /* check for valid number of command-line arguments */ 
		fprintf(stderr, "Usage: %s processes\n", argv[0]);
		return 1; 
	}  

	n = atoi(argv[1]);  
	for (i = 1; i < n; i++)
		if ((pid = fork()) == -1)  // father and child enter
			break; //error break

	fprintf(stdout, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)pid);
	return 0; 
}
