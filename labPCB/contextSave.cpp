#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

main()
{
    jmp_buf env;
    int i;

    i = setjmp(env);
    printf("i = %d\n", i);

    if (i != 0) 
        exit(0);

    longjmp(env, 2);
    printf("Does this line get printed?\n");

}
