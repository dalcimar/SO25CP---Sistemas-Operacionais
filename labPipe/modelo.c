#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int MAXLINE=50;
        int     n, fd[2];
        pid_t   pid;
        char    string[] = "";
        char    line[MAXLINE];

	if (pipe(fd) < 0) {
		error("pipe error");}

     
        if((pid = fork()) < 0)
        {
                error("fork error");
        }

        else if(pid> 0)
        {
                
                close(fd[0]);
                write(fd[1], "Hello, world-123\n", 16);
                exit(0);

        }
        else
        {
/* Parent process closes up output side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                n = read(fd[0], line, 17);
                printf("Received string: %s", line);



        }
        
        return(0);
}
