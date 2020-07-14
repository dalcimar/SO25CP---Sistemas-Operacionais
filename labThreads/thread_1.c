#include <stdio.h> 
#include <unistd.h>
#include <pthread.h>

int global;

void* thr_func(void *arg){
    global = 40;
    sleep(1);
    printf("Novo thread: %d\n", global);
    return NULL;
}

int main(void){
    pthread_t tid;
    global = 20;
    printf("Thread principal: %d\n", global);
    pthread_create(&tid, NULL, thr_func, NULL);
    pthread_join(tid, NULL);
    global++;
    printf("Thread principal: %d\n", global);
    return 0;
}

