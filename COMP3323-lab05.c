#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#define N 10

void bakery();
void *consumer(void* n);
pthread_mutex_t lock;
int bread = 5;

int main(){
	pthread_t bakery_t, consumer_t;
	pthread_mutex_init(&lock, NULL);
	
	int i;
	for(i = 0; i<100 ; i++){
		pthread_create(&bakery_t, NULL, bakery, NULL);
		pthread_create(&consumer_t, NULL, consumer, NULL);
		
		pthread_join(bakery_t, NULL);
		pthread_join(consumer_t, NULL);
	}
	
	pthread_mutex_destroy(&lock);
}

void bakery(){
	pthread_mutex_lock(&lock);
	while(bread <= 10){
		printf("Baking bread: %d \n", bread);
		bread ++;
	}
	
	pthread_mutex_unlock(&lock);
}

void *consumer(void* n){
	pthread_mutex_lock(&lock);
	while(bread >= 4){
		printf("Baking bread: %d \n", bread);
		bread --;
	}
	
	pthread_mutex_unlock(&lock);
}
