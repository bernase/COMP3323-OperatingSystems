#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 100 //Number of elements in Buffer. Then change to 10 and 100
#define TRUE 1
#define K 10
int Buffer[K];
int index = 0;
int eaten = 0;
sem_t mutex, empty, full;

void *producer() {
	int item, j;
	while (TRUE) {
		item = 1; //Generating data to be placed in the buffer.
		//Wait
		sem_wait(&empty); //Wait if the buffer is full, or reduce the number of empty spaces by 1.
		sem_wait(&mutex); //Get permission to enter the critical section.
		
		//Critical Section
		Buffer[index] = item; //Enter the data in Buffer (Critical Section).
		
		//printing and Signal
		printf("producer has produced the item number: %d \n", index);
		for(j=0 ; j<K ; j++){
		printf("%d-", Buffer[j]);
		}
		printf("\n");
		sleep(2);

		index = (index + 1) % K;
		sem_post(&mutex); //Indicate that it exits the Critical Section.
		sem_post(&full); //If there are any consumers waiting, wake up,
	}
}

void *consumer(){
	int item, j;
	while (TRUE) {
		//Wait
		sem_wait(&full); //Wait if the buffer is empty, or reduce the number of full places by 1
		sem_wait(&mutex); //Get permission to enter the critical section
		
		//Critical Section
		item = 0;
		Buffer[eaten] = item; //Get data from Buffer (Critical Part)
		
		//printing and Signal
		printf("consumer has used the item number: %d \n", eaten);
		for(j=0 ; j<K ; j++){
		printf("%d-", Buffer[j]);
		}
		printf("\n");
		sleep(2);
		eaten = (eaten + 1) % K;
		sem_post(&mutex); //Indicate that it exits the Critical Section
		sem_post(&empty); //If there is a manufacturer waiting, wake up
	}
}


int main(){
	sem_init(&mutex, 0, 1); //mutual exclusion of critical part
	sem_init(&empty, 0, K); //The number of empty space in the buffer
	sem_init(&full, 0, 0); //The number of filled places in Buffer
	pthread_t producer_t[K], consumer_t[K];
	
	int i;
	for(i = 0; i<K ; i++){
		pthread_create(&producer_t[i], NULL, producer, NULL);
	}
	for(i = 0; i<K ; i++)
	{
		pthread_create(&consumer_t[i], NULL, consumer, NULL);
	}
	for(i = 0; i<K ; i++)
	{
		pthread_join(producer_t[i], NULL);
	}
	for(i = 0; i<K ; i++)
	{
		pthread_join(consumer_t[i], NULL);
	}
	
	
	
	
	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);
	return 0;
}
