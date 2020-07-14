#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5
#define RAND_DIVISOR 10000

// the buffer
int buffer[BUFFER_SIZE];

// buffer counter
int counter;

pthread_t tid;

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
}

// Producer Thread
void* producer(void *param) {
   int item;

   while(true) {
      // sleep for a random period of time */
      int rNum = rand() / RAND_DIVISOR;
      sleep(rNum);

      // generate a random number
      item = rand();

      if(!insert_item(item)) {
         printf("producer produced %d\n", item);
      }
      else {
         fprintf(stderr, " Producer report error condition\n");
      }
   }
}

// Consumer Thread
void* consumer(void *param) {
   int item;

   while(true) {
      // sleep for a random period of time
      int rNum = rand() / RAND_DIVISOR;
    	sleep(rNum);

      if(!remove_item(&item)) {
         printf("consumer consumed %d\n", item);
      }
      else {
         fprintf(stderr, " Consumer report error condition\n");
      }
   }
}

int main() {

	srand((unsigned int)time(NULL));

   int mainSleepTime = 2; // Time in seconds for main to sleep
   int numProd = 5; // Number of producer threads
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
