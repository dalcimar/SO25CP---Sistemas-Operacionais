#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define BUFFER_SIZE 5

pthread_mutex_t mutex; //the mutex lock
sem_t full, empty; //the semaphores

int buffer[BUFFER_SIZE]; //the buffer

int counter; //buffer counter 

pthread_t tid; //thread ID

void *producer(void *param); // the producer thread
void *consumer(void *param); // the consumer thread

int insert_item(int item){ // Add an item to the buffer   
	if(counter < BUFFER_SIZE){ // When the buffer is not full add the item and increment the counter*/
		buffer[counter] = item;
		counter++;
		return 0;
	}
	else{ // Error the buffer is full
		return 1;
	}
}

int remove_item(int *item){ // Remove an item from the buffer
	if(counter > 0){ // When the buffer is not empty remove the item and decrement the counter
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

void *producer(void *param){ // Producer Thread
	int item;

	while(1) {
		sleep(10);

		item = rand() / 10000000; // generate a random number
				  
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

void* consumer(void *param){ // Consumer Thread
	int item;

	while(1){
		sleep(1);

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
	int numProd = 100; // Number of producer threads
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
