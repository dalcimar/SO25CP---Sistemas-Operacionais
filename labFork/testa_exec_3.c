#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t r_wait(int *status) {
    int retval;
    while (((retval = wait(status)) == -1) && (errno == EINTR));
    return retval;
}
int main(int argc, char *argv[]) {
    pid_t childpid;
    if (argc<2) {
        fprintf (stderr, "Usage: %s command arg1 arg2 ... \n", argv[0]);
        return 1;
    }
    childpid = fork();
    if (childpid == -1) {
        perror ("Failed to fork");
        return 1;
    }
    if (childpid == 0) {	/* Child code */
        execvp(argv[1], &argv[1]);
        perror ("Child failed to execvp the command");
        return 1;
    }
    if (childpid != r_wait(NULL)) {	/* Parent code */
        perror ("Parent failed to wait");
        return 1;
    }
    printf("Child completed -- parent now exiting.\n");
    return 0;
}

