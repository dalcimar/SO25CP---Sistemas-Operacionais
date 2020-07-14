#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void) {
	pid_t pid;

	pid = fork();
	if(pid == -1) {
		perror("Failed to fork");
		exit(0);
	}
	
	if(pid == 0) 
		printf("I am child %ld, my parent is %ld\n",(long)  getpid(), (long)getppid());
	if(pid > 0)
		printf("I am parent %ld, my parent is %ld\n", (long) getpid(), (long)getppid());

	exit(0);
}
