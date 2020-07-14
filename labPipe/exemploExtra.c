//#include “ourhdr.h”

#include <unistd.h>
#include <signal.h>
#include <sys/types.h>


int main(void)
{
	int MAXLINE=50;
	int n, fd[2];
	pid_t pid;
	char line[MAXLINE];
	if (pipe(fd) < 0) {
		error("pipe error");}
	if ((pid=fork()) < 0) {
		error("fork error");
	}
	else if (pid > 0) { 		/* processo pai */
		close(fd[0]); 
		write(fd[1], "hello world\n", 13);
		//error ("write error");
	}
	else {  /* processo filho */

		close(fd[1]);
                n = read(fd[0], line, 17);
		write(STDOUT_FILENO, line, n);

	}

	exit(0);
}

