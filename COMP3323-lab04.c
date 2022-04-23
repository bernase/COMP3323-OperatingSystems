/*
 ============================================================================
 Name        : COMP3323-lab04.c
 Author      : 18070001027 - Melek Berna SERIT
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

#define N 3

typedef struct PROCESS_s *PROCESS;
typedef struct PROCESS_s{
	int id;
	int bt;		//burst time
	int at;		//arrival time
	int ct;		//complation time
	int wt;		//waiting time
	int tat;	//turnaround time
} PROCESS_t[N];


PROCESS fillStruct(int id, int bt, int at);
void swap(int *x, int *y);
void bubbleSort(int arr[], int n);
PROCESS proccess(PROCESS pro[]);
void print();

int main(void) {
	PROCESS pro[N];
	int numOfPro;
	printf("Enter Number of Processes(int): ");
	scanf("%d", &numOfPro); //test etmesi daha kolay diye N atadım her seferinde bu değeri girmemek için
	printf("\n");

	pro[0] = fillStruct(1, 5 , 0);
	pro[1] = fillStruct(2, 9, 3);
	pro[2] = fillStruct(3, 6 , 6);
	for(int i = 0; i < N ; i++){
		pro[i] = fillStruct(i+1, i+1 , i+1); //scanf ile yaparken elemanı al, strcpy ile yapıştır assignla
		pro[i]->ct = pro[i]->bt + pro[i]->at;
		pro[i]->tat = pro[i]->ct - pro[i]->at;
		pro[i]->wt = pro[i]->tat - pro[i]->bt;
	}

	int avgtat;
	int temp = 0;
	for(int i = 0; i < N ; i++){
		temp = temp + pro[i]->tat;
	}
	avgtat = temp / N;

	int avgwt;
	int temp2 = 0;
	for(int i = 0; i < N ; i++){
		temp2 = temp2 + pro[i]->wt;
	}
	avgwt = temp2 / N;

	int arrAt[N];
	for(int i = 0; i < N; i++){
		arrAt[i] = pro[i]->at;
	}
	bubbleSort(arrAt, N);
	proccess(pro);
	print(pro);
}

PROCESS fillStruct(int id, int bt, int at){
	PROCESS_t pro;
//	PROCESS *ptr;
	pro = (*int)malloc(N * sizeof(PROCESS));
	pro->id = id;
	pro->bt = bt;
	pro->at = at;
	pro->ct = 0;		//as a default
	pro->wt = 0;		//as a default
	pro->tat = 0;		//as a default

	return pro;
}

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)

    // Last i elements are already in place
    for (j = 0; j < n-i-1; j++)
        if (arr[j] > arr[j+1])
            swap(&arr[j], &arr[j+1]);
}

PROCESS proccess(PROCESS pro[]){ //First come first serve

	pro[0]->ct=pro[0]->bt + pro[0]->at; // Initial Completion Time = Burst Time Of 1st

	for(int i = 0; i < N; i++){
		if(i != 0){
			if(pro[i-1]->ct < pro[i]->at){
				pro[i]->ct = pro[i]->at+pro[i]->bt;
			} else {
				pro[i]->ct = pro[i-1]->ct+pro[i]->bt;
			}
		}
	}
	return pro;
}

void print(PROCESS pro[]){
	for(int i = 0; i < N; i++){
		printf("Process Name: %d \n", i+1);
		printf("Burst Time[%d]: %d \n", i+1, pro[i]->bt);
		printf("\n");
	}

	for(int j = 0; j < N; j++){
		printf("Arrival Time[%d]: %d \n", j+1, pro[j]->at);
	}

	printf("---------------------------------------------\n");

	printf("---------------------------------------------\n");

}
