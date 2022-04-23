/*
 ============================================================================
 Name        : COMP3323-lab07.c
 Author      : 18070001027 - Melek Berna ŞERİT
 Description : Dining Philosophers in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5
#define TRUE 1
#define LEFT (ph_num + (N-1))%N
#define RIGHT (ph_num + 1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

sem_t mutex, s[N];
int state[N];
int phil_num[N]={0,1,2,3,4};

void *philosopher(void *num);
void take_forks(int ph_num);
void put_forks(int ph_num);
void test(int ph_num);

int main(){
	int i;

	sem_init(&mutex, 0, 1); //mutual exclusion
	for(i = 0; i<N; i++)
	{
		sem_init(&s[i], 0, i); //içinde ne olcak i or 0
	}

	pthread_t philosopher_t[N];
	for(i = 0; i<N ; i++)
	{
		pthread_create(&philosopher_t[i], NULL, philosopher, &phil_num[i]);
	}
	for(i = 0; i<N ; i++)
	{
		pthread_join(philosopher_t[i], NULL);
	}


	sem_destroy(&mutex);
	for(i = 0; i<N; i++)
	{
		sem_destroy(&s[i]);
	}
	return 0;
}

void *philosopher(void *num)
{
    while(TRUE) {
    	int *k = num;
        sleep(1);
        //printf("Philosopher %d is thinking\n", num + 1);
        take_forks(*k);
        sleep(0);
        //printf("%d . Philosopher: yum-yum spaghetti\n", num + 1);
        put_forks(*k);
    }
}

void take_forks(int ph_num){
	printf("Philosopher %d is thinking\n", ph_num + 1);
    sem_wait(&mutex);
    state[ph_num] = HUNGRY;

    printf("Philosopher %d is hungry\n", ph_num + 1);

    test(ph_num);
    sem_post(&mutex);
    sem_wait(&s[ph_num]);
}

void put_forks(int ph_num){
	printf("%d . Philosopher: yum-yum spaghetti\n", ph_num + 1);
    sem_wait(&mutex);

    state[ph_num] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", ph_num + 1, LEFT + 1, ph_num + 1);
    printf("Philosopher %d is thinking\n", ph_num + 1);

    test(LEFT);
    test(RIGHT);

    sem_post(&mutex);
}

void test(int ph_num){
    if (state[ph_num] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[ph_num] = EATING;
        sleep(2);
        printf("Philosopher %d takes fork %d and %d\n", ph_num+1, LEFT+1, ph_num+1);
        printf("Philosopher %d is Eating\n", ph_num+1);
        sem_post(&s[ph_num]);
    }
}
