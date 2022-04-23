/*
 ============================================================================
 Name        : COMP3323-lab09.c
 Author      : 18070001027 - Melek Berna Serit
 Description : Lab09 in C
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#define N 5		//number of processes
int blockSize[]= {100, 200, 500, 400, 300};
int pro[]= {500, 100, 200, 300, 350};

void swap(int* a, int* b);
void bubble_sort(int arr[], int size);

int main(void) {
	int i, j;

	printf("Processes: \n");
	for(i=0 ; i<N ;i++){
		printf("%d . process' size is %d \n", i, pro[i]);
	}

	printf("\nBlock sizes before the sort algorithm: \n");
	for(i=0 ; i<N ;i++){
		printf("%d . block size is %d \n", i, blockSize[i]);
	}

	printf("\n----------\n");

	bubble_sort(blockSize, 5);

	printf("\nBlock sizes after the sort algorithm: \n");
		for(i=0 ; i<N ;i++){
			printf("%d . block size is %d \n", i, blockSize[i]);
		}
	printf("\n");

	for(i=0 ; i < N ; i++){//process
		for(j=0; j<N ; j++){//blocksize array
			if(pro[i] <= blockSize[j])
			{
				printf("%d . process located in %d . block \n", i, j);
				break;
			}
		}
	}

	return EXIT_SUCCESS;
}

void swap(int* a, int* b)
{
	int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[], int size){
	int i,j;

	for(i=0; i<size-1; i++){
		for(j=0; j<size-i-1; j++){
			if(arr[j] > arr[j+1]){
				swap(&arr[j], &arr[j+1]);
			}
		}
	}
}
