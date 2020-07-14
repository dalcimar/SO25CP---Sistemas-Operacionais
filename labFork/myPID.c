#include <stdio.h>
#include <unistd.h>
#include <sys/type.h>

int main(void) {
    pid_t childpid;
    pid_t mypid;
    
    mypid = getpid();
    childpid = fork();
    if (childpid == -1) {
        perror("Failed to fork");
        return 1;
    }
    if (childpid == 0) 
        printf("I am child %ld, ID = %ld\n",(long int)  getpid(), (long int) mypid);
    else
        printf("I am parent %ld, ID = %ld\n", (long int) getpid(), (long int) mypid);
    
    return 0;
}
