#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
    pid_t childpid;
    childpid = fork();
    if(childpid == -1){
        perror("Failed to fork");
        return 1;
    }
    if(childpid == 0){ /* Child code */
        execl("/bin/ls","ls","-1", NULL);
        perror("Child falide to exec ls");
        return 1;
    }
    printf("I am the parent. I am Waiting for my child to complete...\n");
    if (childpid != wait (NULL)) {
        perror("Parent failed to wait due to signal or error");
        return 1;
    }
    printf("Child completed - I am now exiting.\n");
    return (0);
}
