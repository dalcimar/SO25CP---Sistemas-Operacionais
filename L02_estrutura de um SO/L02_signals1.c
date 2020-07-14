#include <sys/types.h>  
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

// send a signal using kill -SIGKILL L02_signals1

int main(){
	for(;;) {
		pid_t pid = getpid();
		printf("pid=%ld\n", (long)pid);
		sleep(1);
	}
}
