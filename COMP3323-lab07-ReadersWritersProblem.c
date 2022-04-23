/*
 ============================================================================
 Name        : COMP3323-lab07.c
 Author      : 18070001027 - Melek Berna ŞERİT
 Description : Readers Writers Problem in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define K 10
sem_t in_line, db, mutex;
int readcount = 0;

void *writer(void *p);
void *reader(void *p);

int main(void) {
	sem_init(&in_line, 0, 1);
	sem_init(&db, 0, 1);
	sem_init(&mutex, 0, 1); //mutual exclusion

	pthread_t writer_t[K], reader_t[K];
	int i;
	for(i = 0; i<K ; i++)
	{
		pthread_create(&writer_t[i], NULL, writer, NULL);
		pthread_create(&reader_t[i], NULL, reader, NULL);
	}
	for(i = 0; i<K ; i++)
	{
		pthread_join(writer_t[i], NULL);
		pthread_join(reader_t[i], NULL);
	}

	sem_destroy(&in_line);
	sem_destroy(&db);
	sem_destroy(&mutex);
	return 0;
}


void *writer(void *p){
	printf("Writer wants to enter.\n");
	sem_wait(in_line);
	sem_wait(db);

	//Critical Section
	printf("Writer has entered.\n");

	sem_post(in_line);
	sem_post(db);
	printf("Writer leaving.\n");
}

void *reader(void *p){
	int count1, count2;
	printf("%d . Reader wants to enter.\n", readcount);
	sem_wait(in_line);
	sem_wait(mutex);
	count1 = readcount;
	readcount++;
	sem_post(mutex);

	if(count1 == 0){
		sem_wait(db);
	}

	sem_post(mutex);

	//Critical Section
	printf("%d . Reader is reading\n", readcount);
	sleep(3);

	sem_wait(mutex);
	readcount--;
	count2 = readcount;
	sem_post(mutex);
	if(count2 == 0){
		sem_post(db);
	}
	printf("%d . Reader leaving.\n", readcount);
}
