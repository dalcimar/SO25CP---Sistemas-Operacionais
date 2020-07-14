#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define RAND_DIVISOR 10000

#define N 5
#define THINKING 0
#define HUNGRY 1
#define EATING 2
#define LEFT (ph_num+4)%N
#define RIGHT (ph_num+1)%N
 
sem_t mutex;
sem_t s[N];
 
 
void *philospher(void *num);
void take_fork(int);
void put_fork(int);
void test(int);
void think();
void eat();
 
 
int state[N];
int phil_num[N]={0,1,2,3,4};
 
int main(){
	int mainSleepTime = 30; /* Time in seconds for main to sleep */
	
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex,0,1);
 
 
    for(i=0;i<N;i++)
        sem_init(&s[i],0,0);
    
	for(i=0;i<N;i++){
        pthread_create(&thread_id[i],NULL,philospher,&phil_num[i]);
        printf("Philosopher %d is thinking\n",i+1);
    }
        
    sleep(mainSleepTime);

    /* Exit the program */
    printf("Exit the program\n");
    exit(0);    
}

/* think for a random period of time */
void think()
{
	int rNum = rand() / RAND_DIVISOR;
	sleep(rNum);
}

/* eat for a random period of time */
void eat()
{
	int rNum = rand() / RAND_DIVISOR;
	sleep(rNum);
}
 
void *philospher(void *num){
   int *i = (int *)num;
   
   while(1){
      think();
      take_fork(*i);
      eat();
      put_fork(*i);
   }
}


 
void take_fork(int ph_num){
   sem_wait(&mutex);
   state[ph_num] = HUNGRY;
   printf("Philosopher %d is Hungry\n",ph_num+1);
   test(ph_num);
   sem_post(&mutex);
   sem_wait(&s[ph_num]);
   //sleep(1);
}
 
 
void test(int ph_num){
   if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING){
      state[ph_num] = EATING;
      //sleep(2);
      printf("Philosopher %d takes fork %d and %d\n",ph_num+1,LEFT+1,ph_num+1);
      printf("Philosopher %d is Eating\n",ph_num+1);
      sem_post(&s[ph_num]);
   }
}
 
 
void put_fork(int ph_num){
   sem_wait(&mutex);
   state[ph_num] = THINKING;
   printf("Philosopher %d putting fork %d and %d down\n",ph_num+1,LEFT+1,ph_num+1);
   printf("Philosopher %d is thinking\n",ph_num+1);
   test(LEFT);
   test(RIGHT);
   sem_post(&mutex);
}
