#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE]; // the buffer
int counter; // buffer counter

pthread_t tid;

void *producer(void *param); // the producer thread
void *consumer(void *param); // the consumer thread

int insert_item(int item){ // Add an item to the buffer
	if(counter < BUFFER_SIZE){ // When the buffer is not full add the item and increment the counter*/
		buffer[counter] = item;
		counter++;
		return 0;
	}
	else { // Error the buffer is full
		return 1;
	}
}

int remove_item(int *item){ // Remove an item from the buffer
	if(counter > 0) { // When the buffer is not empty remove the item and decrement the counter
		*item = buffer[(counter-1)];
		counter--;
		return 0;
	}
	else { // Error buffer empty
		return 1;
	}
}

void initializeData(){
   counter = 0; //init buffer
}

void* producer(void *param) { // Producer Thread
	int item;

	while(1){
		sleep(1); // sleep for a random period of time

		item = rand() / 10000000; // generate a random number

		if(!insert_item(item)) {
			printf("producer produced %d\n", item);
		}
		else {
			fprintf(stderr, " Producer report error condition\n");
		}
	}
}

void* consumer(void *param){ // Consumer Thread
	int item;
	
	while(1) {
		sleep(1); // sleep for a random period of time

		if(!remove_item(&item)){
			printf("consumer consumed %d\n", item);
		}
		else{
			fprintf(stderr, " Consumer report error condition\n");
		}
	}
}

int main(){
	srand((unsigned int)time(NULL));

	int mainSleepTime = 10; // Time in seconds for main to sleep
	int numProd = 2; // Number of producer threads
	int numCons = 5; // Number of consumer threads
	
	initializeData(); // Initialize the app

	for(int i=0; i<numProd; i++){ // Create the producer threads
		pthread_create(&tid,NULL,producer,NULL);
	}

	for(int i=0; i<numCons; i++){ // Create the consumer threads
		pthread_create(&tid,NULL,consumer,NULL);
	}

	sleep(mainSleepTime); // Sleep for the specified amount of time in milliseconds

	printf("Exit the program\n");
	exit(0);
}
