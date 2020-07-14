#include <sys/types.h>  
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
main() {
	pid_t pid = fork();
	if (pid == 0) {
	  for (;;) {
		printf("pid=%ld\n",getpid());
		sleep(1); 
	  }
	}
	else {
	  sleep(5);
	  kill(pid,SIGKILL); exit(0); 
        }
}
