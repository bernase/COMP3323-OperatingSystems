/*
 ============================================================================
 Name        : COMP3323-labExam.c
 Author      : 18070001027 - Melek Berna ŞERİT
 Description : Q1 Sleepy Dentist in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5			//number of chairs
#define K 6			//number of patients
#define TRUE 1

sem_t mutex, pat, dt;
int chair = N;
int dentist_chair = 0; //bunu state olarak kullandım, dentist busy or free
int patient_num[K]={0, 1, 2, 3, 4, 5};

void *dentist(void *num);
void *patient(void *num);

int main(){
	int i;

	sem_init(&mutex, 0, 1);	//mutual exclusion
	sem_init(&pat, 0, 0);	//patient
	sem_init(&dt, 0, 0);	//dentist

	pthread_t dentist_t, patient_t[K];
	pthread_create(&dentist_t, NULL, dentist, 0);
	for(i = 0; i<K ; i++)
	{
		pthread_create(&patient_t[i], NULL, patient, 0);
		//pthread_create(&patient_t[i], NULL, patient, &patient_num[i]);
	}

	pthread_join(dentist_t, NULL);
	for(i = 0; i<K ; i++)
	{
		pthread_join(patient_t[i], NULL);
	}


	sem_destroy(&mutex);
	sem_destroy(&pat);
	sem_destroy(&dt);
	return 0;
}

void *dentist(void *num)
{
    while(TRUE) {
    	dentist_chair++;
    	sleep(0);
    	printf("Dentist is sleeping while waiting for a patient.\n");
    	sem_wait(&pat);	//waits for a patient

    	printf("Dentist wake up!\n");
    	dentist_chair--;
    	sem_wait(&mutex);	//mutex to protect the number of free chairs

    	sleep(1);
    	printf("Dentist having the patient \n");
    	chair++; //oturan kalkıyor, yer açılıyor
    	dentist_chair++;

        sem_post(&dt);
        sem_post(&mutex);
    }
}

void *patient(void *num)
{
	//int *k = *num;
    while(TRUE) {
    	sleep(1);
    	sem_wait(&mutex);
        if(chair > 0){
        	sleep(1);
        	//printf("%d . Patient sits \n", k+1);
        	printf("Patient sits \n");
        	chair --;

        	sem_post(&pat);	//dişçi ben geldim uyan
        	sem_post(&mutex);
        	if(dentist_chair == 1){ //dişçi san
        		sleep(1);
        		printf("Patient waits in the waiting room.\n");//if dentist is busy
        	}
        	sem_wait(&dt);
//        	sleep(1);
//        	printf("Dentist having the patient \n");
        } else{
        	sleep(1);
        	printf("Patient goes home because there is no enough chair to wait.\n");
        	sem_wait(&mutex);
        }
    }
}

