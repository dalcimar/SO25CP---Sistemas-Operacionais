#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define RAND_DIVISOR 10000

pthread_mutex_t mutex; //the mutex lock
sem_t full, empty; //the semaphores

int buffer[BUFFER_SIZE]; //the buffer

int counter; //buffer counter 

pthread_t tid; //thread ID

void *producer(void *param); // the producer thread
void *consumer(void *param); // the consumer thread

// Add an item to the buffer
bool insert_item(int item) {
   // When the buffer is not full add the item and increment the counter*/
   if(counter < BUFFER_SIZE) {
      buffer[counter] = item;
      counter++;
      return 0;
   }
   else { // Error the buffer is full
      return 1;
   }
}

// Remove an item from the buffer
bool remove_item(int *item) {
   // When the buffer is not empty remove the item and decrement the counter
   if(counter > 0) {
      *item = buffer[(counter-1)];
      counter--;
      return 0;
   }
   else { // Error buffer empty
      return 1;
   }
}

void initializeData() {
   counter = 0; //init buffer
	
	pthread_mutex_init(&mutex, NULL); //create the mutex lock */
	sem_init(&full, 0, 0); 	//create the full semaphore and initialize to 0 */
	sem_init(&empty, 0, BUFFER_SIZE); //create the empty semaphore and initialize to BUFFER_SIZE */
}

// Producer Thread
void *producer(void *param) {
   int item;
   
   while(true) {
      // sleep for a random period of time */
      int rNum = rand() / RAND_DIVISOR;
      sleep(1);

      // generate a random number
      item = rand();
            
      sem_wait(&empty); //acquire the empty lock
      pthread_mutex_lock(&mutex); //acquire the mutex lock
      
      if(!insert_item(item)) {
         printf("producer produced %d\n", item);
      }
      else {
         fprintf(stderr, " Producer report error condition\n");
      }
      
      pthread_mutex_unlock(&mutex); //release the mutex lock
      sem_post(&full); //signal full
   }
}

// Consumer Thread
void* consumer(void *param) {
   int item;

   while(true) {
      // sleep for a random period of time
      int rNum = rand() / RAND_DIVISOR;
      sleep(3);
      
	   sem_wait(&full); //aquire the full lock
	   pthread_mutex_lock(&mutex); //aquire the mutex lock
	    
      if(!remove_item(&item)) {
         printf("consumer consumed %d\n", item);
      }
      else {
         fprintf(stderr, " Consumer report error condition\n");
      }
      
	   pthread_mutex_unlock(&mutex); //release the mutex lock
	   sem_post(&empty); //signal empty
   }
}

int main() {

	srand((unsigned int)time(NULL));

   int mainSleepTime = 20; // Time in seconds for main to sleep
   int numProd = 1; // Number of producer threads
   int numCons = 1; // Number of consumer threads

	// Initialize the app
	initializeData();

	// Create the producer threads
	for(int i = 0; i < numProd; i++) {
	    pthread_create(&tid,NULL,producer,NULL);
	}
	
	// Create the consumer threads
	for(int i = 0; i < numCons; i++) {
	    pthread_create(&tid,NULL,consumer,NULL);
	}
	
	// Sleep for the specified amount of time in milliseconds
	sleep(mainSleepTime);
	
	printf("Exit the program\n");
	exit(0);
}
