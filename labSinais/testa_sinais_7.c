#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>

main() { 
    sigset_t mask; 
    sigemptyset(&mask); 
    sigaddset(&mask, SIGINT); 
    // mask = (sigset_t) (1<<SIGINT); // 1 in bit SIGINT, 0 elsewhere
    sigset_t oldmask; 
    int ret = sigprocmask(SIG_BLOCK, &mask, &oldmask);
	    // now SIGINT is blocked 
	    // (ignore control-C) 
        // now do something without interruption
    fprintf(stderr, "betcha can't control-C me!\n"); 
    sleep(20); 
    ret = sigprocmask(SIG_UNBLOCK, &mask, &oldmask); 
    // now control-C works again. 
} 
