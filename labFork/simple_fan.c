#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]) {
    pid_t childpid = 0; 
    int i, n;
    
    /* check for valid number of command-line arguments */ 
    
    n = atoi(argv[1]);  
    for (i = 1; i < n; i++)
        if ((childpid = fork()) <= 0)  //only the child (or error) enters
            break; //child break
    
    fprintf(stderr, "i:%d  process ID:%ld  parent ID:%ld  child ID:%ld\n",
        i, (long)getpid(), (long)getppid(), (long)childpid);
    return 0; 
}
