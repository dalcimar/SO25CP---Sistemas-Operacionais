// myshell.c
#include <stdio.h>
#include <unistd.h>
#define EVER ;;
int main(){
	int process;
	char line[81];
	for (EVER) {
		fprintf(stderr, "cmd: ");
		/* blank line input */
		if (gets (line) == (char *) NULL) 
            return 0;
		/* create a new process */
		process = fork ();
		if (process > 0){
            /* parent */
            wait ((int *) 0);
		}
		/* null pointer - return value not saved */
		else if (process == 0) { /* child */
            execlp (line, line, (char *) NULL);
            /* execute program */
            fprintf (stderr, "Can't execute %s\n", line);
            return 1;
		}
		else if ( process == -1) { /* can't create a new process */
            fprintf (stderr, "Can't fork!\n");
            return 2;
        }
    }
}

