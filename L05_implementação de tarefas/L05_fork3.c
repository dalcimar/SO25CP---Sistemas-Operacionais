#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char *argv[]) {
    pid_t pid = 0; 
    int i, n;
    
    if (argc != 2){  /* check for valid number of command-line arguments */ 
        fprintf(stderr, "Usage: %s processes\n", argv[0]);
        return 1; 
    }    
     
    n = atoi(argv[1]);  
    for (i = 1; i < n; i++)
        if ((pid = fork()) > 0)  //only parent enter (parent return) > 0
            break; //parent break
    
    fprintf(stdout, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n", i, (long)getpid(), (long)getppid(), (long)pid);
    
    exit(0); 
}
