#include <stdlib.h>
#include <stdio.h>


void swap(int T[], int i, int j){
	int temp = T[i];
	T[i] = T[j];
	T[j] = temp;
}

void divide(int T[], int first, int end, int pivot_index){
	int key = T[pivot_index];
	swap(T, pivot_index, end);
	pivot_index = first;
	int i;
	for(i = first; i < end; i++){
		if(T[i] < key){
			swap(T, i, pivot_index);
			pivot_index+=1;	
		}
	}
	
	swap(T, pivot_index, end);
		
}


int main(int argc, char *argv[]){
	int T[7] = {7, 12, 25, 3, 6, 1, 9};
	divide(T, 0, 6, 0);
	int i;
	for(i= 0; i<7; i++){
		printf("%d ", T[i]);
	}	
	printf("\n");
	
	return 0;
}